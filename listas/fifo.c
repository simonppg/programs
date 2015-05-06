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
int move_now();
int enqueue();
int dequeue();

Fifo fifo = {NULL, NULL};

int main(int argc, char const *argv[])
{
	moveToPoint(new_point(5,10));
	moveToPoint(new_point(7,15));
	moveToPoint(new_point(15,80));
	moveToPoint(new_point(4,60));
	moveToPoint(new_point(9,10));

	//Aqui debe haber dos tareas (productor, consumidor)
	//productor: envia una serie de puntos para que el brazo se mueva y debe asegurarse de que se hayan recibido todos los puntos
	//consumidor: mueve los motores repetando los tiempos que le toma a motor procesar la señal

	printf("\n");
	return 0;
}

int moveToPoint(Point * p)
{
	if(is_Fifo_Empty(fifo)) {
		move_now(p);
	}
	else {
		if(enqueue() == 0) {
			//calcular tiempo restante
			return remaining_time;
		}
		else {
			return -1;
		}
	}
}

int move_now(Point * p) {
	if(getMoving() == Waiting){
		setMoving(Moving);
		sleep(5); //Espera a que puede mandar otra posicion al servo
		//TODO calcular el tiempo que debe esperar tomando en cuenta:
		//el tiempo que le toma al servo en moverse
		//el tiempo de planificacion de esta tarea
		//considerar tambien el posible retraso que se genere al escribir en los archivos de Linux
		setMoving(Waiting);
		return 0;
	}
	return -1;
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

