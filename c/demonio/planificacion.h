#if !defined (_PLANIFICACION_H_)
#define _PLANIFICACION_H_

/* Periodos de tareas:
            sensor_task = 120000000  (120ms)
			control_task = 1000000000 (1 s)
			brix_task =  Es aperiodica, controlada por lectura del serial
			modbus_task= 120000000	(120ms)
			UserInterface_task = 5000000000 (5s) Quizás puede ser de 5 s ??? */
#define sensor_task_period 120000000
#define control_task_period 1000000000
#define modbus_task_period 120000000
#define UserInterface_task_period 5000000000

#endif