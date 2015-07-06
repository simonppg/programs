/* Very simple queue
 * These are FIFO queues which discard the new data when full.
 *
 * Queue is empty when in == out.
 * If in != out, then 
 *  - items are placed into in before incrementing in
 *  - items are removed from out before incrementing out
 * Queue is full when in == (out-1 + QUEUE_SIZE) % QUEUE_SIZE;
 *
 * The queue will hold QUEUE_ELEMENTS number of items before the
 * calls to QueuePut fail.
 */
 #include <stdlib.h>
 #include <stdio.h>

typedef struct {
	int x, y;
} Point;

/* Queue structure */
#define QUEUE_ELEMENTS 20
#define QUEUE_SIZE (QUEUE_ELEMENTS + 1)
Point *Queue[QUEUE_SIZE];
int QueueIn, QueueOut;

void QueueInit(void)
{
    QueueIn = QueueOut = 0;
}

int QueuePut(Point *new)
{
    if(QueueIn == (( QueueOut - 1 + QUEUE_SIZE) % QUEUE_SIZE))
    {
        return -1; /* Queue Full*/
    }

    Queue[QueueIn] = new;

    QueueIn = (QueueIn + 1) % QUEUE_SIZE;

    return 0; // No errors
}

int QueueGet(Point **old)
{
    if(QueueIn == QueueOut)
    {
        return -1; /* Queue Empty - nothing to get*/
    }

    *old = Queue[QueueOut];

    QueueOut = (QueueOut + 1) % QUEUE_SIZE;

    return 0; // No errors
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

int show_point(Point *p)
{
	if(p != NULL)
		printf("(%d,%d) -> ", p->x, p->y);
	return 0;
}

int main(int argc, char const *argv[])
{
	Point *a;
	if(QueuePut(new_point(0,10)) == -1)
		printf("\nFull fifo");
	if(QueuePut(new_point(1,9)) == -1)
		printf("\nFull fifo");
	if(QueuePut(new_point(2,9)) == -1)
		printf("\nFull fifo");
	if(QueuePut(new_point(3,9)) == -1)
		printf("\nFull fifo");
	if(QueuePut(new_point(4,9)) == -1)
		printf("\nFull fifo");
	if(QueuePut(new_point(5,9)) == -1)
		printf("\nFull fifo");
	if(QueuePut(new_point(6,9)) == -1)
		printf("\nFull fifo");
	if(QueuePut(new_point(7,9)) == -1)
		printf("\nFull fifo");
	if(QueuePut(new_point(8,9)) == -1)
		printf("\nFull fifo");
	if(QueuePut(new_point(9,9)) == -1)
		printf("\nFull fifo");
	if(QueuePut(new_point(10,9)) == -1)
		printf("\nFull fifo");
	if(QueuePut(new_point(11,9)) == -1)
		printf("\nFull fifo");
	if(QueuePut(new_point(12,9)) == -1)
		printf("\nFull fifo");

	if(QueueGet(&a) == -1)
		printf("\nEmpty fifo");
	else
		show_point(a);
	if(QueueGet(&a) == -1)
		printf("\nEmpty fifo");
	else
		show_point(a);
	if(QueueGet(&a) == -1)
		printf("\nEmpty fifo");
	else
		show_point(a);
	if(QueueGet(&a) == -1)
		printf("\nEmpty fifo");
	else
		show_point(a);
	if(QueueGet(&a) == -1)
		printf("\nEmpty fifo");
	else
		show_point(a);
	if(QueueGet(&a) == -1)
		printf("\nEmpty fifo");
	else
		show_point(a);
	if(QueueGet(&a) == -1)
		printf("\nEmpty fifo");
	else
		show_point(a);
	if(QueueGet(&a) == -1)
		printf("\nEmpty fifo");
	else
		show_point(a);
	if(QueueGet(&a) == -1)
		printf("\nEmpty fifo");
	else
		show_point(a);
	if(QueueGet(&a) == -1)
		printf("\nEmpty fifo");
	else
		show_point(a);
	if(QueueGet(&a) == -1)
		printf("\nEmpty fifo");
	else
		show_point(a);
	if(QueueGet(&a) == -1)
		printf("\nEmpty fifo");
	else
		show_point(a);

	printf("\n");
	return 0;
}