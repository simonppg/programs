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
	printf("\n");

    struct timeval tval_before, tval_after, tval_result;
	gettimeofday(&tval_before, NULL);
	long int microseconds;
	long int milliseconds;

	while(1) {
		usleep(500000);
		gettimeofday(&tval_after, NULL);

		microseconds = (tval_after.tv_sec - tval_before.tv_sec) * 1000000 + ((int)tval_after.tv_usec - (int)tval_before.tv_usec);
		milliseconds = microseconds/1000;
		tval_result.tv_sec = microseconds/1000000;
		tval_result.tv_usec = microseconds%1000000;
		printf("tval_result: %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);

	}
	printf("\n");
}