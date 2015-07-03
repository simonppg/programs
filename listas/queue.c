#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int x, y;
} Point;

typedef struct node_{
	Point *point;
	struct node_ *next;
} Queue;

Queue * enqueue(Queue *queue, Point * point) {
	Queue *new_node, *p;
	new_node = malloc(sizeof(Queue));
	new_node->point = point;
	new_node->next = NULL;
	p = queue;
	while(p->next != NULL) {
		p = p->next;
	}
	p->next = new_node;
	p = new_node;
	return (queue);
}
Queue * dequeue(Queue *queue) {
	Queue *p;
	p = queue;

	if(p->next->point != NULL p->next->next) {
		p->next = p->next->next;
		p->point = p->next->point;
	}

	return (queue);
}

int show_point(Point *p)
{
	if(p != NULL)
		printf("(%d,%d) -> ", p->x, p->y);
	return 0;
}

void display(Queue *queue)
{
	Queue *temp;
	for(temp=queue->next;temp!=NULL;temp=temp->next) {
		show_point(temp->point);
	}
	printf("null \n");
}

Point * new_point(int x, int y)
{
	Point *p;
	if((p = malloc(sizeof *p)) != NULL)
	{
		p->x = x;
		p->y = y;
	}
	return p;
}

int main(void){

	Queue *queue;
	queue = malloc(sizeof(Queue));
	queue->next = NULL;
	queue = enqueue(queue, new_point(5,10));
	queue = enqueue(queue, new_point(7,15));
	queue = enqueue(queue, new_point(15,80));
	queue = enqueue(queue, new_point(4,60));
	queue = enqueue(queue, new_point(9,10));
	display(queue);
	queue = dequeue(queue);
	display(queue);
	queue = dequeue(queue);
	display(queue);
	queue = dequeue(queue);
	display(queue);
	queue = dequeue(queue);
	display(queue);
	queue = dequeue(queue);
	display(queue);
	queue = dequeue(queue);
	display(queue);
}