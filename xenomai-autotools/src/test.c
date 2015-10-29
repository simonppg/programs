#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>

#include <native/task.h>
#include <native/timer.h>

#include "sistema.h"
#include "test.h"


void test(void *arg)
{
	RTIME now, previous;
	/*
	 * Arguments: &task (NULL=self), the current task
	 *            start time, delay before release, TM_NOW = none
	 *            period (here: 1 s) 
	 */
	rt_task_set_periodic(NULL, TM_NOW, test_task_period);
	previous = rt_timer_read();
	while (1) {
		rt_task_wait_period(NULL);
		now = rt_timer_read();
		printf("Time since last turn: %ld.%06ld ms\n",
                       (long)(now - previous) / 1000000,
                       (long)(now - previous) % 1000000);
                       previous = now;
    }
}