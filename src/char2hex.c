#include <char2hex.h>
#include <stdlib.h>

char *char2hex(char *buf , char c){
	if(!buf)
		return NULL;

	char *p = buf + (sizeof(c) * 8) + 1;
	int i = 0;
	*p = '\0';
	do{
		*(--p) = (c >> i) & 15;
		*p += (*p < 10) ? '0' : ('A' - 10);
	}while((i+=4) < (sizeof(c)*8));
	return p;
}
