#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>

//xenomai
#include <native/task.h>
#include <native/timer.h>

#include "sistema.h"
#include "test.h"

int estado = 0;

int main(int argc, char const *argv[])
{
	/*Hilos de xenomai*/
	rt_task_create(&test_task, "TEST", 0, test_task_prio, 0);

	rt_task_start(&test_task, &test, NULL);

	printf("Init\n");
	
	pause();

	rt_task_delete(&test_task);
	return 0;
}