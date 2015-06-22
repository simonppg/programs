#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>

#include <native/task.h>
#include <native/timer.h>

#include "sistema.h"
#include "test/test.h"


void test(void *arg)
{
	/*
	 * Arguments: &task (NULL=self), the current task
	 *            start time, delay before release, TM_NOW = none
	 *            period (here: 1 s) 
	 */
	rt_task_set_periodic(NULL, TM_NOW, test_task_period);
	while (1) {
		rt_task_wait_period(NULL);
		printf("tarea periodica\n");
    }
}