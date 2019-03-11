#include <stdio.h>
#include <char2hex.h>
#include <hwriter.h>
#include <logger.h>

const char *prog = "-\\|//";

int main(int argc , char **argv){
	if(argc < 2){
		printf("Usage: %s [FILE NAME] [OUTPUT FILE NAME]\n" , *argv);
		return -1;
	}

	printl(info , "using '%s' as the data file." , argv[1]);
	printl(info , "will be writing to '%s' with respect to the given data file." , argv[2]);
	hwriter_t *writer = hwriter_create(argv[2]);

	char buffer[100]; 
	int pc = 0;
	FILE *fp = NULL;
	if(!(fp = fopen(argv[1] , "rb"))){
		printl(fatal , "cannot open %s file for reading." , argv[1]);
		return -2;
	}
	while(!feof(fp)){
		hwriter_write_hex(writer , char2hex(buffer , getc(fp)));
		fflush(stdout);
		printf("progress [%c]: %d bytes written.\r" , prog[pc] , writer->bytes_received);
		pc = (pc + 1) % 4;
	}
	fclose(fp);
	hwriter_destroy(writer);
	printl(info , "write finished , you can now use '%s'." , argv[2]);
	return 0;
}

