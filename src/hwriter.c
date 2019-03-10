#include <hwriter.h>
#include <logger.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

static char *get_include_guard(const char *filename){
	size_t len = strlen(filename);
	char *s = calloc(len + 1 , sizeof(char));
	char *p = s;
	if(!s)
		return NULL;
	if(!filename){
		free(s);
		return NULL;
	}

	while(*filename){
		if(*filename >= 'a' && *filename <= 'z'){
			*s++ = *filename - 32;
		}else if(*filename >= 'A' && *filename <= 'Z'){
			*s++ = *filename;
		}else if(*filename == '.'){
			break;	
		}else{
			*s++ = '_';
		}
		++filename;
	}
	return p;	
}

hwriter_t *hwriter_create(const char *filename){
	
	if(!filename){
		printl(warning , "invalid file name given for construction of header writer.");
		printl(fatal , "header writer construction aborted.");
		return NULL;
	}

	/* check file if the file exists and 
	 * also check its permission to write and read. */
	if(!access(filename , F_OK)){ /* 0 means it exists. */
		printl(fatal , "%s exists in the filesystem , not instructed to overwrite." , filename);
		return NULL;
	}

	printl(info , "started writing packed header file.");
	hwriter_t *d = calloc(1 , sizeof(hwriter_t));
	time_t current_time;
	struct tm * time_info;
	char time_string[9];
	time(&current_time);
	time_info = localtime(&current_time);
	strftime(time_string, sizeof(time_string), "%H:%M:%S", time_info);
	
	char *include_guard = NULL;
	if(!d){
		printl(fatal , "not enough memory to allocate header writer.");
		return NULL;
	}

	/* open header file. */
	printl(info , "opening %s for writing." , filename);
	if(!(d->fp = fopen(filename , "w"))){
		printl(fatal , "cannot open %s for writing." , filename);
		free(d);
		return NULL;
	}

	/* write boilerplate code with respect to the 
	 * given filename.*/
	if(!(include_guard = get_include_guard(filename))){
		fclose(d->fp);
		free(d);
		return NULL;
	}
	printl(info , "using %s as the include guard and variable name." , include_guard);
	
	fprintf(d->fp , "/*\n");
#ifdef GIT_VERSION_STR	
	fprintf(d->fp , " * Generated by hpack-%s.\n" , GIT_VERSION_STR);
#else 
	fprintf(d->fp , " * Generated by hpack.\n");
#endif
	fprintf(d->fp , " * Created on %s.\n" , time_string);
	fprintf(d->fp , "*/\n");
	fprintf(d->fp , "#ifndef %s_H_INCLUDED\n" , include_guard);
	fprintf(d->fp , "#define %s_H_INCLUDED\n" , include_guard);
	fprintf(d->fp , "const char %s[] =\n" , include_guard);
	fprintf(d->fp , "           { ");
	free(include_guard);
	printl(info , "finished writing boilerplate code.");
	return d;
}

void hwriter_destroy(hwriter_t *writer){
	if(!writer)
		return;

	printl(info , "finalizing writing the header file.");	
	fprintf(writer->fp , " 0x0 };\n");
	fprintf(writer->fp , "#define FILESIZE %d\n" , writer->bytes_received);	
	fprintf(writer->fp , "#endif\n");
	fclose(writer->fp);
	free(writer);
}

int hwriter_write_hex(hwriter_t *writer , const char *hex){
	if(!writer || !hex)
		return -1;
	fprintf(writer->fp , " %s ," , hex);
	if(!(writer->bytes_received % 8)){
		fprintf(writer->fp , "\n            ");
	}
	++(writer->bytes_received);
	return 0;
}
