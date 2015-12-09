#include <stdlib.h>

#include <native/task.h>
#include <native/timer.h>

#include "planificacion.h"
#include "serial.h"
#include "brix.h"
#include "brix_orp_test.h"

void brix(void *arg)
{
	fprintf( fichero_prueba, "iniciando brix\n" );
	fflush( fichero_prueba );

	// Declaración de variables locales a las tareas
	int x;
	unsigned char caracter;
	unsigned char trama[32];
	int b1,b2,b3,b4;	//variables para tomar las decenas, unidades, desimas y centésimas
	

	if(UartInit()==0){
		fprintf( fichero_prueba, "brix uart abierto\n");
    	fflush( fichero_prueba );
    }else{
    	fprintf( fichero_prueba, "brix error uartOpen\n");
    	fflush( fichero_prueba );
    }

	/*
	 * Arguments: &task (NULL=self), the current task
	 *            start time, delay before release, TM_NOW = none
	 *            period (here: 1 s) 
	 */
	rt_task_set_periodic(NULL, TM_NOW, brix_task_period);
	while (1) {
		rt_task_wait_period(NULL);

		caracter=ReceiveByte();
		if (caracter==0x54)
		{
			trama[0] = caracter;
			for(x=1;x<31;x++)
			{
				caracter=ReceiveByte();
				trama[x] = caracter;
			}
			trama[x+1] = '\0';
			//printf("\nTrama: ");
			/*for(i=0;i<32;i++)
			{
				printf("%c ",trama[i]);
			}*/
			//brix_uart1 = 0.0;//no volver a cero para mantener el ultimo valor valido
			b1 = b2 = b3 = b4 = 0;
			b1 = trama[17];
			b2 = trama[18];
			b3 = trama[20];
			b4 = trama[21];

			/*printf("\norig: ");
			printf("\t%02x ",b1);
			printf("\t%02x ",b2);
			printf("\t%02x ",b3);
			printf("\t%02x ",b4);
			
			printf("\nbrix: ");*/
			b1 = b1-0x30;
			b2 = b2-0x30;
			b3 = b3-0x30;
			b4 = b4-0x30;
			if(b1>9 || b2>9 || b3>9 || b4>9){
				//Nada
			}
			else{
				brix_uart1 = (b1*10.0)+(b2*1.0)+(b3/10.0)+(b4/100.0);

				/*printf("\t%d\t%d\t%d\t%d ",b1*1000,b2*100,b3*10,b4);
				printf("\t\t\t\t\t\t%d ",brix);*/
				fprintf( fichero_prueba, "brix_uart1 %f\n", brix_uart1 );
	        	fflush( fichero_prueba );
	        	fprintf( fichero_prueba, "brix_uart1 b1:%d b2:%d b3:%d b4:%d \n", b1,b2,b3,b4 );
	        	fflush( fichero_prueba );
        	}

        	flush();

        	//limpia trama
        	for(x=0;x<32;x++)
			{
				trama[x]=0;
			}
		}
	}
	UartClose();
}