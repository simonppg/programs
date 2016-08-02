#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define MAXTHREADS 4

struct datos_thread
{
	int n1;
	int n2;
	int id;
};

struct datos_thread datos_thread_array[MAXTHREADS];

void *suma1(void *threadarg){
	int suma,multi,resta,divicion;
	struct datos_thread *my_data;	
	my_data= (struct datos_thread *)threadarg;
	suma=my_data->n1+my_data->n2;

	printf("%d + %d = ",my_data->n1,my_data->n2);
	pthread_exit((void *)suma);
}
void *resta1(void *threadarg){
	int resta;
	struct datos_thread *my_data;	
	my_data= (struct datos_thread *)threadarg;
	resta=my_data->n1-my_data->n2;
	printf("%d - %d = ",my_data->n1,my_data->n2);
	pthread_exit((void *)resta);
}
void *multi1(void *threadarg){
	int multi;
	struct datos_thread *my_data;	
	my_data= (struct datos_thread *)threadarg;
	multi=my_data->n1*my_data->n2;
	printf("%d * %d = ",my_data->n1,my_data->n2);
	pthread_exit((void *)multi);
}
void *divicion1(void *threadarg){
	int divicion;
	struct datos_thread *my_data;	
	my_data= (struct datos_thread *)threadarg;
	divicion=my_data->n1/my_data->n2;
	printf("%d / %d = ",my_data->n1,my_data->n2);
	pthread_exit((void *)divicion);
}




int main(int argc, char *argv[])
{
	int t=0;
	int suma,resta,multi,divicion;
	int rc;
srand(time(NULL));
		datos_thread_array[t].n1=rand()%100+0;
		datos_thread_array[t].n2=rand()%100+0;
		pthread_t tid;
		rc = pthread_create(&tid, NULL, suma1, (void *)(datos_thread_array + t));
		pthread_join(tid, (void **)&suma);
		printf(" %d	",suma);
		rc = pthread_create(&tid, NULL, resta1, (void *)(datos_thread_array + t));
		pthread_join(tid, (void **)&resta);
		printf(" %d	",resta);
		rc = pthread_create(&tid, NULL, multi1, (void *)(datos_thread_array + t));
		pthread_join(tid, (void **)&multi);
		printf(" %d	",multi);
		rc = pthread_create(&tid, NULL, divicion1, (void *)(datos_thread_array + t));	
		pthread_join(tid, (void **)&divicion);
		printf(" %d	",divicion);




		if(rc){
			printf("ERROR: return code from pthread_create() is %d \n",rc);
			exit(-1);
		}
pthread_exit(NULL);
}











