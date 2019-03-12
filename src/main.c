#include <stdio.h>
#include <stdlib.h>
#include <char2hex.h>
#include <hwriter.h>
#include <logger.h>
#include <string.h>

int main(int argc , char **argv){
	if(argc < 2){
		printf("Usage: %s [INPUT FILEPATH] [OPTIONS]\n" , *argv);
		printf("\nOPTIONS: \n");
		printf("\t-o,--output          set path to output file.\n");
		printf("\t-v,--variable-name   variable name to assign data.\n");
		printf("\t-g,--header-guard    name for header guard.\n");
		return -1;
	}

	char *var_name = NULL,
             *head_guard = NULL,
	     *output = NULL,
             *input = strdup(*(++argv));
        	
	while(*(++argv)){
		if(!strcmp(*argv , "-o") ||
		   !strcmp(*argv , "--output")){
			if(!(output = strdup(*(++argv)))){
				printl(fatal , "expected an output file.");
				goto exit;
			}
		}else
		if(!strcmp(*argv , "-v") ||
		   !strcmp(*argv , "--variable-name")){
			if(!(var_name = strdup(*(++argv)))){
				printl(fatal , "expected a variable name.");
				goto exit;
			}
		}else 
		if(!strcmp(*argv , "-g") ||
		   !strcmp(*argv , "--header-guard")){
			if(!(head_guard = strdup(*(++argv)))){
				printl(fatal , "expected a header guard.");
				goto exit;
			}
		}else{
			printl(fatal , "unknown argument %s." , *argv);
			goto exit;
		}
	}
	
	FILE *fp = NULL;
	char *buffer = calloc((sizeof(char)*8) + 2 , sizeof(char));
	hwriter_t *writer = hwriter_create(/*ouput file = */ output,
			                   /* variable name = */ var_name,
					   /* header guard name = */ head_guard);
	if(!writer){
		printl(fatal , "cannot construct header writer.");
		goto exit;
	}
	if(!(fp = fopen(input , "rb"))){
		printl(fatal , "cannot open %s file for reading." , argv[1]);
		goto exit;
	}
	printl(info , "started writing , please wait...");
	while(!feof(fp)){
		hwriter_write_hex(writer , char2hex(buffer , getc(fp)));
	}
	fclose(fp);
	printl(info , "write finished successfully!");

        exit:
		if(output)
			free(output);
		if(input)
			free(input);
		if(var_name)
			free(var_name);
		if(head_guard)
			free(head_guard);
		hwriter_destroy(writer);
	
	return 0;
}

