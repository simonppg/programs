#ifndef _FIFO_H_
#define _FIFO_H_

struct Node_s
{
	char *name;
};
typedef struct Node_s Node;

struct Fifo_s {
	Node *in, *out;
	int size;
};
//struct Fifo_s;
typedef struct Fifo_s Fifo;

Node * node_create();
void node_destroy(Node *node);
Fifo * fifo_create();
Node * fifo_insert(Fifo *fifo, Node *node);

#endif
