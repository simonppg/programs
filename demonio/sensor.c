#include <stdlib.h>

#include <native/task.h>
#include <native/timer.h>

#include "planificacion.h"
#include "sensor.h"

void sensor(void *arg)
{
	// Declaración de variables locales a las tareas
	int target_buff = 1;
	int i = 0;

	/*
	 * Arguments: &task (NULL=self), the current task
	 *            start time, delay before release, TM_NOW = none
	 *            period (here: 1 s) 
	 */
	rt_task_set_periodic(NULL, TM_NOW, sensor_task_period);
	while (1) {
		rt_task_wait_period(NULL);
		
		// Código aqui
		while(1){
			printf("hilo sensor\n");
			sleep(1);
		}
	}
}