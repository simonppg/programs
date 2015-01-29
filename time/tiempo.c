#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*void get_time_string(struct tm *info)
{
	time_t rawtime;
	//struct tm *info;
	char buffer[80];

	time( &rawtime );

	info = localtime( &rawtime );
	printf("Current local time and date: %s", asctime(info));
}*/

char* get_time_string()
{
	struct tm *tm;
	time_t t;
	char *str_time = (char *) malloc(100*sizeof(char));
	t = time(NULL);
	tm = localtime(&t);
	//YYYY-MM-DD HH:MM:SS
	strftime(str_time, 100, "%G-%m-%d %H:%M:%S", tm);
	return str_time;
}

void print_time(){
	time_t rawtime;
	struct tm *info;
	char buffer[80];

	time( &rawtime );

	info = localtime( &rawtime );
	printf("Current local time and date: %s", asctime(info));
}


void main ()
{
	print_time();

	char* vector;
	vector = get_time_string();
	printf("\n%s",vector);

	printf("\n");

}