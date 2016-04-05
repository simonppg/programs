#include <stdlib.h>

#include "fifo.h"

struct Fifo_s {
	Node *in, *out;
};

Node * node_create()
{
	Node * node = malloc( sizeof(Node) );

	if (!node)
		return NULL;
	
	node->name = malloc( sizeof(char) * 50 );
	node->name = "new node\0";

	return node;
}

/*Fifo * fifo_create()
{
	Fifo * fifo;
	fifo->in = fifo->out = NULL;
	return fifo;
}*/

void node_destroy(Node *node)
{
	if (node == NULL)
		return;

	free(node);
}

