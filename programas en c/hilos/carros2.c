
/* para compilar: gcc -Wall -o carros2 carros2.c -lpthread */
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
/**************************************/
#define IZQ	0
#define DER	1

#define A1	1
#define A2	2
#define A3	3

#define EX_IZ	0
#define MED_IZ	10
#define MED_DE	21
#define EX_DE	31

//Semaforos
sem_t s1,s2,s3;

//variables de posicionamiento para saber si es Derecha o izquierda
int x1=0,x2=0,x3=0;


//posición autos
int a1=0;
int a2=0;
int a3=0;

//direccion autos
int A1d=0;
int A2d=0;
int A3d=0;



//          0         10         21        31
char c1[]= "*---------            ---------- ";
char c2[]= "          \\          / ";
char c3[]= "+------------------------------- ";
char c4[]= "          /          \\ ";
char c5[]= "|---------            ---------- ";
char tactual[128];
time_t tiempo;

/**************************************/
/*
*Funcion que se usa para pintar la pista de los carros y el tiempo del sistema.
*/
void dibujar()
{
	system("clear");
	printf("\n");
	printf(c1);	printf("\n");
	printf(c2);	printf("\n");
	printf(c3);	printf("\n");
	printf(c4);	printf("\n");
	printf(c5);	printf("\n");
	tiempo=time(NULL);
    	struct tm *tlocal=localtime(&tiempo);
	strftime(tactual,128,"Fecha: %d/%m/%y Hora: %H:%M:%S", tlocal);
	printf("%s\n",tactual);
}

//Funcion para dar velocidad a los autos.
void ms_delay(int sleep_ms)
{
  struct timespec tv;
  if (sleep_ms != 0)
  {tv.tv_sec = sleep_ms/1000;
  tv.tv_nsec = (sleep_ms%1000) * 1000000;
  nanosleep(&tv, NULL);
}
}

/*
*Funcion que regresa la posicion de los carros.
*/
int get_carro_pos(int carro)
{
	if (carro == A1)
		return a1;
	else if (carro == A2)
		return a2;
	else if(carro == A3)
		return a3;
	else return -1;
}
/*
*Funcion para saber si el carro esta en puntos claves de la pista o fuera de los limites.
*/
int final(int carro)
{
	carro= get_carro_pos(carro);
	if (carro == EX_IZ)//al extremo de la izquierda
		return 1;
	else if (carro == EX_DE)//al extremo de la derecha
		return 2;//al extremo de la izquierda
	else if (carro < EX_DE && carro > EX_IZ)//10+1+10+1+10
		return 0;
	else return -1;//error fuera de límites
}
/*
*Asigna caracter en que posicion sera dibujado.
*/
void printvar(char c, int x, int y)
{
	switch(y){
	case 0:	c1[x]=c;break;
	case 1:	c2[x]=c;break;
	case 2:	c3[x]=c;break;
	case 3:	c4[x]=c;break;
	case 4:	c5[x]=c;
	}
	dibujar();
}
/*
*Calcula en donde esta el carro.
*/
void calcular(int *y_act, int *y_ant, char c, char *r, int act, int ant,
		int y_max, int y_med, int y_min, char c_iz, char c_de){
	*y_ant=y_max; *y_act=y_max;
	if (act==MED_IZ){//union de la izquierda
		if(ant>act){*y_act= y_med; *y_ant= y_min;}//hacia la izquierda
		if(ant<act){*y_act= y_med; *y_ant= y_max;}//hacia la derecha
	}
	else if (act==MED_DE){//union de la derecha
		if(ant>act){*y_act= y_med; *y_ant= y_max;}//hacia la izquierda
		if(ant<act){*y_act= y_med; *y_ant= y_min;}//hacia la derecha
	}
	else if(act>MED_IZ && act<MED_DE){//todo el centro
		*y_ant= y_min; *y_act= y_min;
	}
	else if(act>=EX_IZ && act<MED_IZ)//a la izquierda
		*y_act= y_max;
	else if(act>MED_DE && act<EX_DE)  //a la derecha
		*y_act= y_max;

	if(ant==MED_IZ){*r= c_iz; *y_ant= y_med;}//repintar union izquierda
	else if(ant==MED_DE){*r= c_de; *y_ant= y_med;}//repintar union derecha
}
//Mueve el auto.
void mover(int carro, int ant, int act){
	int y_ant=0, y_act=0;
	char c, r='-';
	switch(carro) {
	case A1:
		c='*';
		calcular(&y_act, &y_ant, c, &r, act, ant, 0, 1, 2, '\\', '/');
		break;
	case A2:
		c= '+';
		y_act= 2; y_ant= 2;
		break;
	case A3:
		c='|';
		calcular(&y_act, &y_ant, c, &r, act, ant, 4, 3, 2, '/', '\\');
	}
	printvar(r,ant,y_ant);//limpia posición anterior
	printvar(c,act,y_act);
}
/*
*Mueve el auto verificando que no se salga de los limites.
*/
int mover_auto(int carro, int direccion){
	int ant= 0, act= 0;
	if(final(carro)!=-1){
		switch(carro){	//aumenta y decrementa contadores
		case A1:	//dependiendo de la dirección, verifica rangos
			ant= a1;
			if(direccion){
			if(final(carro)!=2) a1++;}
			else if(final(carro)!=1) a1--;
			act= a1;
			break;
		case A2:
			ant= a2;
			if(direccion){
			if(final(carro)!=2) a2++;}
			else if(final(carro)!=1) a2--;
			act= a2;
			break;
		case A3:
			ant= a3;
			if(direccion){
			if(final(carro)!=2) a3++;}
			else if(final(carro)!=1) a3--;
			act= a3;
		}
		mover(carro, ant, act);
	}
	//printf("%i%i%i%i ",final(carro), ant, act, direccion);
	return(final(carro));
}
/**************************************/
/*
*Funcion que implementa los metodos y se nota claramente que debe realizar cada hilo.
*/
void *automovil1(void *a){ //implementar

for(;;) // ciclo infinito para que los autos estes en movimiento constante
{
	if(get_carro_pos(A1)==EX_DE)
	{
		A1d=IZQ;
	}
	if(get_carro_pos(A1)==EX_IZ)
	{
		A1d=DER;
	}
	if(A1d==IZQ)
	{
		mover_auto(A1,IZQ);
	}
	if(A1d==DER)
	{
		mover_auto(A1,DER);
	}
	if(get_carro_pos(A1)==MED_IZ && A1d==DER)
	{
        	sem_wait(&s1);
	}
	if(get_carro_pos(A1)==MED_DE && A1d==IZQ)
	{
        	sem_wait(&s1);
	}
        if(get_carro_pos(A1)==MED_DE && A1d==DER)
	{
		sem_post(&s1);
        }
	if(get_carro_pos(A1)==MED_IZ && A1d==IZQ)
	{
		sem_post(&s1);
        }


	
  ms_delay(500);  // la velocidad del automovil es variante a el tiempo de espera en el cual el hilo tiene un retado en milisegundos
}//fin de ciclo infinito 
}//fin de la funcion 


//// se implentas las mismas reglas de A1  pero cambiando los valores para el A2 y cambio de velocidad
void *automovil2(void *b){//implementar
for(;;)
{
	if(get_carro_pos(A2)==EX_DE)
	{
		A2d=IZQ;
	}
	if(get_carro_pos(A2)==EX_IZ)
	{
		A2d=DER;
	}
	if(A2d==IZQ)
	{
		mover_auto(A2,IZQ);
	}
	if(A2d==DER)
	{
		mover_auto(A2,DER);
	}
	if(get_carro_pos(A2)==MED_IZ && A2d==DER)
	{
        	sem_wait(&s1);
	}
	if(get_carro_pos(A2)==MED_DE && A2d==IZQ)
	{
        	sem_wait(&s1);
	}
        if(get_carro_pos(A2)==MED_DE && A2d==DER)
	{
		sem_post(&s1);
        }
	if(get_carro_pos(A2)==MED_IZ && A2d==IZQ)
	{
		sem_post(&s1);
        }
      
	
  ms_delay(200);  // la velocidad del automovil es variante a el tiempo de espera en el cual el hilo tiene un retado en milisegundos
}//fin de ciclo infinito 
}//fin de la funcion 

//// se implentas las mismas reglas de A1  pero cambiando los valores para el A3 y cambio de velocidad
void *automovil3(void *c){//implementar
for(;;)
{
	if(get_carro_pos(A3)==EX_DE)
	{
		A3d=IZQ;
	}
	if(get_carro_pos(A3)==EX_IZ)
	{
		A3d=DER;
	}
	if(A3d==IZQ)
	{
		mover_auto(A3,IZQ);
	}
	if(A3d==DER)
	{
		mover_auto(A3,DER);
	}
	if(get_carro_pos(A3)==MED_IZ && A3d==DER)
	{
        	sem_wait(&s1);
	}
	if(get_carro_pos(A3)==MED_DE && A3d==IZQ)
	{
        	sem_wait(&s1);
	}
        if(get_carro_pos(A3)==MED_DE && A3d==DER)
	{
		sem_post(&s1);
        }
	if(get_carro_pos(A3)==MED_IZ && A3d==IZQ)
	{
		sem_post(&s1);
        }


ms_delay(400);  //velocidad de automovil3
}
}

/************************************/
/* Programa principal */
int main (int argc, char **argv){

dibujar();//pone en pantalla las rutas iniciales

pthread_t h1,h2,h3; // nombres de los hilos para las funciones de los carros

//codigo de programa 

sem_init(&s1,0,1); /*Inicializa del semaforo a 0*/
sem_init(&s2,0,0); /*Inicializa  del semaforoa 0*/
sem_init(&s3,0,0); /*Inicializa del semaforoa 0*/

pthread_create(&h1,NULL,automovil1,NULL);
pthread_create(&h2,NULL,automovil2,NULL);
pthread_create(&h3,NULL,automovil3,NULL);

pthread_join(h1,NULL);
pthread_join(h2,NULL);
pthread_join(h3,NULL);

	return(0);
}
