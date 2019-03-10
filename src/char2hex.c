#include <char2hex.h>
#include <stdlib.h>

char *char2hex(char *buf , char c){
	if(!buf)
		return NULL;

	char *p = buf + (sizeof(c) * 8) + 1;
	int i = 0,
	    mask = 15,
	    mode = 4;
	*p = '\0';
	do{
		*(--p) = (c >> i) & mask;
		*p += (*p < 10) ? '0' : ('A' - 10);
	}while((i+=mode) < (sizeof(c)*8));
	*(--p) = 'x';
	*(--p) = '0';
	return p;
}
