#ifndef H_WRITER_H_INCLUDED
#define H_WRITER_H_INCLUDED
#include <stdio.h>

typedef struct {
	FILE *fp;
	int bytes_received;
} hwriter_t;

hwriter_t *hwriter_create(const char*,const char*,const char*);
void hwriter_destroy(hwriter_t * , const char*);

int hwriter_write_hex(hwriter_t * , const char *);

#endif /*H_WRITER_H_INCLUDED*/
