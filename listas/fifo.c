#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int x, y;
	struct Point *next;
} Point;

typedef struct {
    Point *input; 		//set Points
    Point *output; 		//move to Point with delay
} Fifo;

Point * new_point(int x, int y);
int show_point(Point *p);
int moveToPoint(Point * p);

Fifo fifo = {NULL, NULL};

int main(int argc, char const *argv[])
{
	moveToPoint(new_point(5,10));
	moveToPoint(new_point(7,15));
	moveToPoint(new_point(15,80));
	moveToPoint(new_point(4,60));
	moveToPoint(new_point(9,10));

	printf("\n");
	return 0;
}

int moveToPoint(Point * p)
{

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
		printf("(%d,%d)", p->x, p->y);
}

