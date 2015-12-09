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

	/*char* vector;
	vector = get_time_string();
	printf("\n%s",vector);
	sleep(1);
	vector = get_time_string();
	printf("\n%s",vector);*/



	/*struct tm *tm, *tm2;
	time_t t, t2;
	char *str_time = (char *) malloc(100*sizeof(char));
	t = time(NULL);
	tm = localtime(&t);
	sleep(2);
	t = time(NULL);
	tm2 = localtime(&t);

	printf("\n");
	//YYYY-MM-DD HH:MM:SS
	strftime(str_time, 100, "%G-%m-%d %H:%M:%S", tm);
	printf("\n%s",str_time);
	strftime(str_time, 100, "%G-%m-%d %H:%M:%S", tm2);
	printf("\n%s",str_time);*/

	printf("\n");

	/*time_t now;
    struct tm *tm;

    now = time(0);
    if ((tm = localtime (&now)) == NULL) {
        printf ("Error extracting time stuff\n");
    }

    printf ("%04d-%02d-%02d %02d:%02d:%02d\n",
        tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
        tm->tm_hour, tm->tm_min, tm->tm_sec);

    printf ("%02d\n", tm->tm_sec);

    printf("\n");*/




    /*time_t t1,t2;
	t1 = time(NULL);
	printf("Hours since January 1, 1970 = %ld\n", t1);
	sleep(5);
	t2 = time(NULL);
	printf("Hours since January 1, 1970 = %ld\n", t2);
	printf("diff: %ld\n", t2-t1);

 	printf("\n");*/





 	/*time_t start_t, end_t;
   double diff_t;

   printf("Starting of the program...\n");
   time(&start_t);

   printf("Sleeping for 5 seconds...\n");
   usleep(2500000);

   time(&end_t);
   diff_t = difftime(end_t, start_t);

   printf("Execution time = %f\n", diff_t);
   printf("Exiting of the program...\n");
   printf("\n");*/

   /*
   //funciona!
   struct timespec tstart={0,0}, tend={0,0};
    clock_gettime(CLOCK_MONOTONIC, &tstart);
   usleep(2500000);
    clock_gettime(CLOCK_MONOTONIC, &tend);
    printf("some_long_computation took about %.5f seconds\n",
           ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - 
           ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));
     printf("\n");*/


     struct timeval tval_before, tval_after, tval_result;

gettimeofday(&tval_before, NULL);

// Some code you want to time, for example:
usleep(2500000);

gettimeofday(&tval_after, NULL);


printf("Time elapsed: %ld.%06ld\n", (long int)tval_before.tv_sec, (long int)tval_before.tv_usec);
printf("Time elapsed: %ld.%06ld\n", (long int)tval_after.tv_sec, (long int)tval_after.tv_usec);

printf("Time elapsed: %ld.%06ld\n", (long int)tval_after.tv_sec - (long int)tval_before.tv_sec, (long int)tval_after.tv_usec - (long int)tval_before.tv_usec);
printf("\n");
}