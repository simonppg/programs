#include <stdlib.h>

#include "fifo.h"

struct Fifo_s {
	char *name;
};

Fifo * fifo_create()
{
	Fifo * fifo = malloc( sizeof(Fifo) );

	if (!fifo)
		return NULL;

	return fifo;
}

void fifo_destroy(Fifo *fifo)
{
	if (fifo == NULL)
		return;

	free(fifo);
}

