#if !defined (_SISTEMA_H_)
#define _SISTEMA_H_

#include <native/task.h>
#include <native/timer.h>

RT_TASK test_task;

#define test_task_period 			 120000000 	//(120ms)

#define test_task_prio 	40

#endif