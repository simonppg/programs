#include <stdlib.h>

#include <native/task.h>
#include <native/timer.h>

#include "planificacion.h"
#include "UserInterface.h"
#include "bd.h"
#include "brix_orp_test.h"

void UserInterface(void *arg)
{
	fprintf( fichero_prueba, "iniciando UserInterface\n" );
	fflush( fichero_prueba );
	
	// Declaración de variables locales a las tareas
	int i = 0;
	char **muestrasMovil = malloc(8);
	for( i = 0; i < 8; i++){
    	muestrasMovil[i] = malloc(1024 * sizeof(char));
    	muestrasMovil[i][0] = '\0';
	}
	enum Estados {ENCENDIDO, APAGADO, APAGADO_SYS};
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
		fprintf( fichero_prueba, "UserInterface\n" );
        fflush( fichero_prueba );


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
					fprintf( fichero_prueba, "UserInterface Preon\n" );
        			fflush( fichero_prueba );
					Consulta("SELECT nombre FROM pruebas WHERE id_prueba = (SELECT MAX(id_prueba) FROM pruebas)");
					fprintf( fichero_prueba, "UserInterface Prueba: %s\n", Datos);
        			fflush( fichero_prueba );
					Consulta("SELECT id_prueba FROM pruebas WHERE id_prueba = (SELECT MAX(id_prueba) FROM pruebas)");
					if(Datos[0] == '1') {
						fprintf( fichero_prueba, "UserInterface Error\n");
        				fflush( fichero_prueba );
						id_prueba = get_time_string();
    					fprintf( fichero_prueba, "UserInterface %s\n", id_prueba);
        				fflush( fichero_prueba );
						asprintf(&vector, "INSERT INTO pruebas (id_prueba, nombre) VALUES ('%s', 'prueba1')",id_prueba);
						Update(vector);

						/*Consulta("SELECT nombre FROM pruebas WHERE id_prueba = (SELECT MAX(id_prueba) FROM pruebas)");
						printf("\nPrueba: %s", Datos);
						Consulta("SELECT id_prueba FROM pruebas WHERE id_prueba = (SELECT MAX(id_prueba) FROM pruebas)");
						printf("\nhora: %s", Datos);*/
					}
					else {
						fprintf( fichero_prueba, "UserInterface Inicia: %s\n", Datos);
        				fflush( fichero_prueba );
						asprintf(&id_prueba, "%s", Datos);
					}
					asprintf(&vector, "UPDATE bioreactor SET encendido = 1");
					Update(vector);
				}
				pre = 0;
				fprintf( fichero_prueba, "UserInterface Encendido\n" );
        		fflush( fichero_prueba );
				
				//TODO validar ph antes de guardar
				muestra++;

				char str[30];
				if(sprintf(str, "%.4f", orp_modbus)==-1)
				{
					//str = "-1";
				}
				//sprintf(str, "%.4f", orp_modbus); //TODO validar conversion erronea, modbus regresa inf cuando no encuentra un dato
        		fprintf( fichero_prueba, "UserInterface %s\n",str);
        		fflush( fichero_prueba );
				asprintf(&vector, "INSERT INTO orp VALUES (null,'%s', '%d', %s)",id_prueba,
																			muestra,
																			str);
				Update(vector);
				
				if(sprintf(str, "%.4f", ph_modbus)==-1)
				{
					//str = "-1";
				}
				//sprintf(str, "%.4f", ph_modbus);
        		fprintf( fichero_prueba, "UserInterface %s\n",str);
        		fflush( fichero_prueba );
				asprintf(&vector, "INSERT INTO ph VALUES (null,'%s', '%d', %s)",id_prueba,
																			muestra,
																			str);
				Update(vector);

				if(sprintf(str, "%.4f", brix_uart1)==-1)
				{
					//str = "-1";
				}
				//sprintf(str, "%.4f", ph_modbus);
        		fprintf( fichero_prueba, "UserInterface %s\n",str);
        		fflush( fichero_prueba );
				asprintf(&vector, "INSERT INTO brix VALUES (null,'%s', '%d', %s)",id_prueba,
																			muestra,
																			str);
				Update(vector);
		    	
		    	/*fprintf( fichero_prueba, "UserInterface INFO: No hay sensor de ph o esta deshabilitado\r\n");
        		fflush( fichero_prueba );*/
				break;
			case APAGADO:
				if(pre == 1){
					fprintf( fichero_prueba, "UserInterface preoff\n" );
        			fflush( fichero_prueba );
        			asprintf(&vector, "UPDATE bioreactor SET encendido = 0");
					Update(vector);

					//Borrando todas las muestras
					asprintf(&vector, "DELETE FROM orp");
					Update(vector);
					asprintf(&vector, "DELETE FROM ph");
					Update(vector);
					asprintf(&vector, "DELETE FROM brix");
					Update(vector);

					muestra = 0;
				}
				pre = 0;
				fprintf( fichero_prueba, "UserInterface Apagado\n" );
        		fflush( fichero_prueba );
				break;
			case APAGADO_SYS:
				fprintf( fichero_prueba, "UserInterface Apagando sistema\n" );
        		fflush( fichero_prueba );
        		asprintf(&vector, "UPDATE movil SET encendido = 0");
				Update(vector);
				asprintf(&vector, "UPDATE bioreactor SET encendido = 0");
				Update(vector);
        		system("poweroff");
				break;
		}
		Consulta("SELECT encendido FROM movil");
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
			case 2:
				estado = APAGADO_SYS;
				break;
		}
    }
}


//TODO dejar de guardar datos despues de que fueron borrados
//TODO reiniciar cuenta de las muestras