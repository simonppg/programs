#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

#define MAXTHREADS 4
//gcc -Wall -o carros2 carros2.c -lpthread

struct datos_thread
{
	int n1;
	int n2;
	int id;
};

struct datos_thread datos_thread_array[MAXTHREADS];
/*
*unica funcion encargada de controlar los hilos creados, esta funcion recibe una estructura y dependiendo su ID
*la funcion le asigna un trabajo determinado, en este caso, las 4 operaciones basicas.
*cuando cada hilo termina su ejecucion intenta pintar en la pantalla y normalmente no muestran los resultados
*de manera ordenada, este es un claro ejemplo de como pueden acelerarse las operaciones, 
*porque ningun hilo espera a otro para escribir en la pantalla.
*/

void *operacion(void *threadarg)
{
	struct datos_thread *my_data;
	my_data = (struct datos_thread *) threadarg;
	sleep(1);
	switch (my_data->id)
	{
		case 0:
			{
				printf("Proceso #0 suma\n");
				printf("%d + %d = %d \n", my_data->n1, my_data->n2,(my_data->n1+my_data->n2));
				break;
			}
		case 1:
			{
				printf("Proceso #1 resta\n");
				printf("%d - %d = %d \n", my_data->n1, my_data->n2,(my_data->n1-my_data->n2));
				break;
			}
		case 2:
			{
				printf("Proceso #2 multiplicacion\n");
				printf("%d * %d = %d \n", my_data->n1, my_data->n2,(my_data->n1*my_data->n2));
				break;
			}
		case 3:
			{
				printf("Proceso #3 divicion\n");
				printf("%d / %d = %d \n", my_data->n1, my_data->n2,(my_data->n1/my_data->n2));
				break;
			}
	}
	pthread_exit(NULL);
}
/*
*Funcion principal que se encarga de controlar el tiempo de ejecucion del programa (preguntando si desea continuar)
*y crea 4 hilos los cuales reciben una estructura, definida en el tope del codigo.
*/
int main(int argc, int argv)
{
	char tactual[128];
	time_t tiempo;
	char c;
	printf("\nDesea correr el programa S/N: ");
  	while(1)
  	{
		c=getchar();
		if (c=='S'||c=='s')
	    	{   
			pthread_t threads[MAXTHREADS];
			int rc,t,n1=8,n2=4;
			int letra;
			srand(time(NULL));
			for (t=0; t<MAXTHREADS; t++)
			{
				printf("Creando thread #%d\n",t);
				datos_thread_array[t].n1=rand()%100+0;
		       		datos_thread_array[t].n2=rand()%100+0;
				datos_thread_array[t].id=t;
				rc= pthread_create(&threads[t],NULL,operacion,(void *)(datos_thread_array + t));
				if (rc)
				{
					printf("Error; return code from pthread_create() is %d\n",rc);
				}
			}
			sleep(2);
			printf("Precione \"c\" para continuar");
			c='\0';
		printf("\nDesea correr el programa S/N: ");
		}
		else if (c=='N'||c=='n') 
		{ 
        		break;
    		}
	}
	/*time_t*/ 
    	tiempo=time(NULL);
    	struct tm *tlocal=localtime(&tiempo);
	strftime(tactual,128,"Fecha: %d/%m/%y Hora: %H:%M:%S", tlocal);
	printf("%s\n",tactual);
	pthread_exit(NULL);
    	return 0;
}
























