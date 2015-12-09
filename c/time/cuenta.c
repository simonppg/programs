#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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

void main ()
{
	printf("\n");

    struct timeval tval_before, tval_after, tval_result;
	gettimeofday(&tval_before, NULL);
	long long microseconds;
	long long milliseconds;
	double ultimo = 0;

	while(1) {
		usleep(500000);
		tval_before = tval_after;
		gettimeofday(&tval_after, NULL);

		microseconds = (tval_after.tv_sec - tval_before.tv_sec) * 1000000 + ((int)tval_after.tv_usec - (int)tval_before.tv_usec);
		milliseconds = microseconds/1000;
		tval_result.tv_sec = microseconds/1000000;
		tval_result.tv_usec = microseconds%1000000;
		//printf("tval_result: %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
		//ultimo = ultimo + (microseconds/1000000) + ((microseconds%1000000) / 1000000) ;
		ultimo = ((microseconds%1000000) / 1000000);
		printf("time: %lld.%lld\n", microseconds/1000000, microseconds%1000000);
		printf("ultimo: %lf\n", ultimo);

	}
	printf("\n");
}