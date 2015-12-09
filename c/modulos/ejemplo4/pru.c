#include <stdlib.h>

#include <native/task.h>
#include <native/timer.h>

#include "prussdrv.h"
#include <pruss_intc_mapping.h>

#include "planificacion.h"
#include "pru.h"

#define PRU_NUM_PWM 1
#define PRU_NUM_ADC 0

//#define MIN_DIF	2
float MIN_DIF = 0.01;

static void *pruDataMem; 
static unsigned int *pruDataMem1; //AM33XX_DATA 8KB RAM1

int pwm0 = 100, pwm1 = 200, pwm2 = 300, pwm3 = 400, pwm4 = 500;
int pwm0_ant = 60, pwm1_ant = 100, pwm2_ant = 100, pwm3_ant = 100, pwm4_ant = 100;
int pwm0_dif = 0, pwm1_dif = 0, pwm2_dif = 0, pwm3_dif = 0, pwm4_dif = 0;
int NANO_SECONDS_PER_CYCLE = 240;//160 antes de los enable bits

int enable_cont = 0;
int enable_time = 50;

void pru(void *arg)
{
	fprintf( fichero_prueba, "iniciando pwm_pru\n" );
	fflush( fichero_prueba );
	
	// Declaración de variables locales a las tareas


	//pru_pwm{
	unsigned int ret;
	tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;
	fprintf( fichero_prueba, "\nINFO: Starting %s example.\r\n", "PWM Demo with PRU");
	fflush( fichero_prueba );
	// Initialize the PRU 
	prussdrv_init();
	// Open PRU Interrupt 
	ret = prussdrv_open(PRU_EVTOUT_1);
	if (ret)
	{
		fprintf( fichero_prueba, "\tERROR: prussdrv_open open failed\n" );
		fflush( fichero_prueba );
		fprintf( fichero_prueba, "\tINFO: falta habilitar los firmware\r\n" );
		fflush( fichero_prueba );
		//return (ret);
	}
	ret = prussdrv_open(PRU_EVTOUT_0);
    if (ret){
        fprintf( fichero_prueba, "\tERROR: prussdrv_open open failed\n" );
		fflush( fichero_prueba );
		fprintf( fichero_prueba, "\tINFO: falta habilitar los firmware\r\n" );
		fflush( fichero_prueba );
        //return (ret);
    }
	// Get the interrupt initialized
	prussdrv_pruintc_init(&pruss_intc_initdata);
	prussdrv_map_prumem(PRUSS0_PRU1_DATARAM, &pruDataMem);
	//assign the the data RAM address to two pointers	
    pruDataMem1 = (unsigned int*)pruDataMem; //AM33XX_DATA 8KB RAM1,Glocal Memory Address
	fprintf( fichero_prueba, "\tINFO: Executing example.\r\n" );
	fflush( fichero_prueba );
	prussdrv_exec_program(PRU_NUM_PWM, "./pwm.bin");
	//pru_pwm}



	/*
	 * Arguments: &task (NULL=self), the current task
	 *            start time, delay before release, TM_NOW = none
	 *            period (here: 1 s) 
	 */
	rt_task_set_periodic(NULL, TM_NOW, pru_task_period);
	while (1) {
		rt_task_wait_period(NULL);
        //ph_control();
		//pwm0 = (phmenos > 0) ? phmenos : pwm0_ant;
		//pwm1 = (phmas > 0) ? phmas : pwm1_ant;
		pwm0_dif = (pwm0 > pwm0_ant) ? pwm0 - pwm0_ant : pwm0_ant - pwm0;
		pwm1_dif = (pwm1 > pwm1_ant) ? pwm1 - pwm1_ant : pwm1_ant - pwm1;
		pwm2_dif = (pwm2 > pwm2_ant) ? pwm2 - pwm2_ant : pwm2_ant - pwm2;
		pwm3_dif = (pwm3 > pwm3_ant) ? pwm3 - pwm3_ant : pwm3_ant - pwm3;
		pwm4_dif = (pwm4 > pwm4_ant) ? pwm4 - pwm4_ant : pwm4_ant - pwm4;
		//printf("\ndif: %f,%f,%f,%f,%f\n",pwm0_dif,pwm1_dif,pwm2_dif,pwm3_dif,pwm4_dif);

		if(pwm0_dif >= MIN_DIF){
			pruDataMem1[0]= 1000000000 / (NANO_SECONDS_PER_CYCLE*pwm0);
			usleep(2000);
			pwm0_ant = pwm0;//printf("pwm0: %d\n",pwm0);
			fprintf( fichero_prueba, "pwm0: %d\n",pwm0);
			fflush( fichero_prueba );
		}
		if(pwm1_dif >= MIN_DIF){
			pruDataMem1[1]= 1000000000 / (NANO_SECONDS_PER_CYCLE*pwm1);
			usleep(2000);
			pwm1_ant = pwm1;//printf("pwm1: %d\n",pwm1);
		}
		if(pwm2_dif >= MIN_DIF){
			pruDataMem1[2]= 1000000000 / (NANO_SECONDS_PER_CYCLE*pwm2);
			usleep(2000);
			pwm2_ant = pwm2;//printf("pwm2: %d\n",pwm2);
		}
		if(pwm3_dif >= MIN_DIF){
		    pruDataMem1[3]= 1000000000 / (NANO_SECONDS_PER_CYCLE*pwm3);
			usleep(2000);
			pwm3_ant = pwm3;//printf("pwm3: %d\n",pwm3);
		}
		if(pwm4_dif >= MIN_DIF){
			pruDataMem1[4]= 1000000000 / (NANO_SECONDS_PER_CYCLE*pwm4);
			usleep(2000);
			pwm4_ant = pwm4;//printf("pwm4: %d\n",pwm4);
		}
		if(enable_cont <= enable_time/2){
            pruDataMem1[5] = 0xFFFFFFFF; //5 bits en alto
            //printf("\nEnable 1 cont: %d, registro: %x\n",enable_cont, pruDataMem1[5]);
		}
        else
        {
        	pruDataMem1[5] = 0; //todos los bits en bajo
        	//printf("\nEnable 0 cont: %d, registro: %x\n",enable_cont, pruDataMem1[5]);
        	if(enable_cont == enable_time)
        		enable_cont = 0;
        }
        enable_cont ++;
        if(pwm0<1000)
			pwm0 += 100;
		else
			pwm0 = 100;
    }

    //pru_pwm{
	fprintf( fichero_prueba, "\tINFO: PRU completed transfer.\r\n" );
	fflush( fichero_prueba );
    prussdrv_pru_clear_event (PRU_EVTOUT_0, PRU0_ARM_INTERRUPT);

	// Disable PRU and close memory mapping
	prussdrv_pru_disable(PRU_NUM_PWM);
    prussdrv_pru_disable(PRU_NUM_ADC);
    prussdrv_exit();
	//pru_pwm}
}


//TODO dejar de guardar datos despues de que fueron borrados
//TODO reiniciar cuenta de las muestras