#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#include "bd.h"

int main(int argc, char* argv[])
{
	/*Variables base de datos*/
	char *vector;
	/*Variables base de datos*/
	/*struct timeval tval_before, tval_after, tval_result;
	gettimeofday(&tval_before, NULL);
	long int microseconds;
	long int milliseconds;*/
	int onoff = 0;



	//FILE *fp= NULL;
	pid_t process_id = 0;
	pid_t sid = 0;
	// Create child process
	process_id = fork();
	// Indication of fork() failure
	if (process_id < 0)
	{
	printf("fork failed!\n");
	// Return failure in exit status
	exit(1);
	}
	// PARENT PROCESS. Need to kill it.
	if (process_id > 0)
	{
	printf("process_id of child process %d \n", process_id);
	// return success in exit status
	exit(0);
	}
	//unmask the file mode
	umask(0);
	//set new session
	sid = setsid();
	if(sid < 0)
	{
	// Return failure
	exit(1);
	}
	// Change the current working directory to root.
	chdir("/");
	// Close stdin. stdout and stderr
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	// Open a log file in write mode.
	//fp = fopen ("Log.txt", "w+");
	while (1)
	{
		/*gettimeofday(&tval_after, NULL);

		microseconds = (tval_after.tv_sec - tval_before.tv_sec) * 1000000 + ((int)tval_after.tv_usec - (int)tval_before.tv_usec);
		milliseconds = microseconds/1000;
		tval_result.tv_sec = microseconds/1000000;
		tval_result.tv_usec = microseconds%1000000;*/
		if(onoff == 0)
			onoff = 1;
		else
			onoff = 0;
		asprintf(&vector, "UPDATE bioreactor SET encendido = %d",onoff);
		Update(vector);
		
		//Dont block context switches, let the process sleep for some time
		sleep(1);
		//fprintf(fp, "Logging info...%ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
		//fflush(fp);
		// Implement and call some function that does core work for this daemon.
	}
	//fclose(fp);
	return (0);
}