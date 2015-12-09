#include <stdlib.h>

#include <native/task.h>
#include <native/timer.h>

#include "planificacion.h"
#include "UserInterface.h"
#include "bd.h"
#include "brix_orp_test.h"

void UserInterface(void *arg)
{
	// Declaración de variables locales a las tareas
	int i = 0;
	char **muestrasMovil = malloc(8);
	for( i = 0; i < 8; i++){
    	muestrasMovil[i] = malloc(1024 * sizeof(char));
    	muestrasMovil[i][0] = '\0';
	}
	enum Estados {ENCENDIDO, APAGADO};
	enum Estados estado = APAGADO;
	char *vector;
	int pre = 0,tiempo=-1;
	char *id_prueba;
	unsigned int muestra = 0;
	/*
	 * Arguments: &task (NULL=self), the current task
	 *            start time, delay before release, TM_NOW = none
	 *            period (here: 1 s) 
	 */
	rt_task_set_periodic(NULL, TM_NOW, UserInterface_task_period);
	while (1) {
		rt_task_wait_period(NULL);
		// Código aqui
		/*if(lecturaDeControl(0,muestrasMovil) != -1)
    	{
    		printf("hora: %s\n", muestrasMovil[0]);
    		printf("agitador_vel: %s\n", muestrasMovil[1]);
    		printf("ph_mas: %s\n", muestrasMovil[2]);
    		printf("ph_menos: %s\n", muestrasMovil[3]);
    		printf("sustrato0_mas: %s\n", muestrasMovil[4]);
    		printf("sustrato0_menos: %s\n", muestrasMovil[5]);
    		printf("sustrato1_mas: %s\n", muestrasMovil[6]);
    		printf("sustrato1_menos: %s\n", muestrasMovil[7]);
    		pwm4 = atoi(muestrasMovil[0]);
      		//enviarBioreactor(cantidadDeMuestras,muestrasMovil);
    	}*/
    	switch (estado){
			case ENCENDIDO:
				if(pre == 1) {
					printf("\nPreon");
					Consulta("SELECT nombre FROM pruebas WHERE id_prueba = (SELECT MAX(id_prueba) FROM pruebas)");
					printf("\nPrueba: %s", Datos);
					Consulta("SELECT id_prueba FROM pruebas WHERE id_prueba = (SELECT MAX(id_prueba) FROM pruebas)");
					if(Datos[0] == '1') {
						printf("\nError");
						id_prueba = get_time_string();
    					printf("\n%s\n", id_prueba);
						asprintf(&vector, "INSERT INTO pruebas (id_prueba, nombre) VALUES ('%s', 'prueba1')",id_prueba);
						Update(vector);

						/*Consulta("SELECT nombre FROM pruebas WHERE id_prueba = (SELECT MAX(id_prueba) FROM pruebas)");
						printf("\nPrueba: %s", Datos);
						Consulta("SELECT id_prueba FROM pruebas WHERE id_prueba = (SELECT MAX(id_prueba) FROM pruebas)");
						printf("\nhora: %s", Datos);*/
					}
					else {
						printf("\nInicia: %s", Datos);
						asprintf(&id_prueba, "%s", Datos);
					}
				}
				pre = 0;
				printf("\nEncendido");
				#if SENSOR_PH
				//TODO validar ph antes de guardar
				muestra++;

				char str[30];
				sprintf(str, "%.4f", ph_modbus);
        		printf("\n%s",str);
				//asprintf(&vector, "INSERT INTO ph VALUES (null,'%s', '%s', %s)",id_prueba, hora, str);
				asprintf(&vector, "INSERT INTO ph VALUES (null,'%s', '%d', %s)",id_prueba,
																			muestra,
																			str);

				//TODO obtener tiempo en segundos
				/*sprintf(str, "%.4f", ph_modbus);
        		printf("\n%s",str);
        		sprintf(str, "%.4f", ph_modbus);
        		printf("\n%s",str);*/




				Update(vector);
		    	#else
		    	printf("\nINFO: No hay sensor de ph o esta deshabilitado\r\n");
		    	#endif
				break;
			case APAGADO:
				if(pre == 1)
					printf("\nPreoff");
				pre = 0;
				printf("\nApagado");
				break;
		}
		Consulta("SELECT encendido FROM bioreactor");
		asprintf(&vector, "%s", Datos);

		switch (atoi(vector)){
			case 1:
				if(estado == APAGADO)
					pre = 1;
				estado = ENCENDIDO;
				break;
			case 0:
				if(estado == ENCENDIDO)
					pre = 1;
				estado = APAGADO;
				break;
		}
    }
}