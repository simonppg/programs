#include <stdlib.h>

#include "fifo.h"

Node * node_create()
{
	Node * node = malloc( sizeof(Node) );

	if (!node)
		return NULL;

	node->name = malloc( sizeof(char) * 50 );
	node->name = "new node\0";

	return node;
}

Fifo * fifo_create()
{
	Fifo * fifo = malloc( sizeof(Fifo) );

	if(!fifo)
		return NULL;

	fifo->in = fifo->out = NULL;
	fifo->size = 0;

	return fifo;
}

void node_destroy(Node *node)
{
	if (node == NULL)
		return;

	free(node);
}

