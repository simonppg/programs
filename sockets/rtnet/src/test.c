//xenomai
#include <native/task.h>
#include <native/timer.h>

#include "rtnet.h"

RT_TASK rtnet_task;

const char *STATUS_STRING[] = {
    "RUNNING", "CREATED", "FINISHED", "INIT", "WAITING", "ERROR", "REINIT"
};

int main()
{
	rt_task_create(&rtnet_task, "rtnet", 0, rtnet_task_prio, 0);
	rt_task_start(&rtnet_task, &rtnet, NULL);
	pause();
	rt_task_delete(&rtnet_task);
}