#include "brix_orp_test.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h>

#include <native/task.h>
#include <native/timer.h>

/*#include "prussdrv.h"
#include <pruss_intc_mapping.h>*/

//usrlib
/*
#include "movil.h"
*/
//modbuslib
#include <math.h>
#include <string.h>
#include <errno.h>
#include "modbus.h"
#include "modbus-rtu.h"

#include "planificacion.h"
#include "bd.h"
#include "serial.h"
#include "brix.h"
#include "modbus_sensor.h"
#include "UserInterface.h"
#include "pru.h"


RT_TASK sensor_task, control_task, brix_task, modbus_task, UserInterface_task, modbus_sensor_task, pru_task;


/* Prioridades de tareas: 
                     	sensor_task = 99
			control_task = 95
			brix_task = 30 
			modbus_task= 40
			UserInterface_task = 20 */
#define sensor_task_prio 99
#define control_task_prio 95
#define brix_task_prio 30
#define modbus_sensor_task_prio 40
#define modbus_task_prio 40
#define UserInterface_task_prio 20

#define PRU_NUM_PWM 1
#define PRU_NUM_ADC 0
//#define MIN_DIF	2
//float MIN_DIF = 0.01;

#define OFFSET_SHAREDRAM 2048		//equivalent with 0x00002000
#define PRUSS0_SHARED_DATARAM    4  //ya esta definido en prussdrv.h
#define SAMPLING_RATE 16000 //16khz
#define BUFF_LENGTH SAMPLING_RATE
#define PRU_SHARED_BUFF_SIZE 500
#define CNT_ONE_SEC SAMPLING_RATE / PRU_SHARED_BUFF_SIZE

/* Declaración de variables globales:
			static int rpm1 -> motor1
			static int rpm2 -> motor2
			static int rpm3 -> motor3
			static int rpm4 -> motor4
			static int rpm5 -> motor5 
			static float pH+, pH-, biomasa, brix, Temp, ORP, torque */
//static int rpm1, rpm2, rpm3, rpm4, rpm5;
float referencia = 14;
float phmas = 0, phmenos = 0, biomasa, gbrix, Temp, ORP, torque;  // no sé si float ???
/*int pwm0 = 100, pwm1 = 200, pwm2 = 300, pwm3 = 400, pwm4 = 500;
int pwm0_ant = 60, pwm1_ant = 100, pwm2_ant = 100, pwm3_ant = 100, pwm4_ant = 100;
int pwm0_dif = 0, pwm1_dif = 0, pwm2_dif = 0, pwm3_dif = 0, pwm4_dif = 0;*/
int enablePWM = 0;
//int NANO_SECONDS_PER_CYCLE = 240;//160 antes de los enable bits

static void *pruDataMem; 
static unsigned int *pruDataMem1; //AM33XX_DATA 8KB RAM1
static void *sharedMem;
static unsigned int *sharedMem_int;

//variables para el modbus
//modbus_t *ctx = NULL;


/******************************************************************************
* Functions declarations                                                      * 
******************************************************************************/
static unsigned int ProcessingADC1(unsigned int value);
float getFloat(uint16_t h, uint16_t l);
char* get_time_string();
void ph_control();


/*int enable_cont = 0;
int enable_time = 50;*/


 
#define FICHERO_PID "/var/run/indessy.pid"
 
volatile char estado = 0;
 
/* Función llamada cuando se recibe una señal SIGTERM */
void adios( int signum )
{
    estado = 1;
}
 
int main( void )
{
	/*Variables base de datos*/
	//solo son de prueba para ver que el sistema corriendo
	char *vector;
	/*Variables base de datos*/
	int onoff = 0;

    struct stat st;
    FILE *fichero_pid;
    //FILE *fichero_prueba; //redefinido en planificacion.h
    pid_t pid;
    pid_t sid;
 
    /* Activamos el manejo de mensajes al demonio de syslogd */
    openlog( "indessy", LOG_CONS | LOG_PID, LOG_DAEMON );
 
    /* Comprobamos si existe le fichero PID */
    if( stat( FICHERO_PID, &st ) == 0 )
    {
        syslog( LOG_ERR, "Ya existe un proceso similar cargado" );
        exit( EXIT_FAILURE );
    }
 
    /* Creamos el fichero PID */
    fichero_pid = fopen( FICHERO_PID, "w" );
    if( fichero_pid == NULL )
    {
        syslog( LOG_ERR, "No se pudo crear el fichero PID" );
        exit( EXIT_FAILURE );
    }
 
    /* Creamos un hilo de ejecucion */
    pid = fork();
    
    /* Si no se pudo crear el hilo */
    if( pid < 0 )
    {
        syslog( LOG_ERR, "No se pudo crear el proceso hijo" );
        fclose( fichero_pid );
        exit( EXIT_FAILURE );
    }
    /* Si se pudo crear el hilo */
    else if( pid > 0 )
    {
        /* Escribimos en el fichero PID el identificador del proceso */
        fprintf( fichero_pid , "%d\n", pid );
        fclose( fichero_pid );
        exit( EXIT_SUCCESS );
    }
    
    /* Se evita el heredar la máscara de ficheros */
    umask( 0 );
 
    /* Convertimos el proceso hijo a demonio */
    sid = setsid();
 
    /* Si no se pudo convertir en demonio */
    if( sid < 0 )
    {
        syslog( LOG_ERR, "No se pudo crear el demonio" );
        unlink( FICHERO_PID );
        exit( EXIT_FAILURE );
    }
 
    /* Cambiamos al directorio raiz */
    if( chdir( "/" ) < 0 )
    {
        syslog( LOG_ERR, "No se pudo cambiar el directorio" );
        unlink( FICHERO_PID );
        exit( EXIT_FAILURE );
    }
 
    /* Cerramos los descriptores de archivo que no usaremos */
    close( STDIN_FILENO );
    close( STDOUT_FILENO );
    close( STDERR_FILENO );
 
    /* Abrimos el fichero de prueba */
    fichero_prueba = fopen( "/tmp/indessy.txt", "w" );
    if( fichero_prueba == NULL )
    {
        syslog( LOG_ERR, "No se pudo crear el fichero de prueba" );
        unlink( FICHERO_PID );
        exit( EXIT_FAILURE );
    }
 
    /* Registramos la función que recibe la señal SIGTERM */
    signal( SIGTERM, adios );

    /*Proceso de inicialización del sistema*/
    /* Avoids memory swapping for this program */
	mlockall(MCL_CURRENT|MCL_FUTURE);	//xenomai
    /*Abrir puertos para lectura de snsores*/
    //brix_uart{
    //UartInit(); //verificar si se pudo abrir el uart, para no iniciar el hilo si no esta listo
    //brix_uart}
    //modbus{
    //printf("\tINFO: Lectura de PH y orp\n");
	/*ctx = modbus_new_rtu("/dev/ttyUSB0", 19200, 'N', 8, 2);
	if(ctx == NULL)
	{
        fprintf( fichero_prueba, "Error al abrir el dispositivo\n");
        fflush( fichero_prueba );
		//printf("Error al abrir el dispositivo\n");
		//printf("\tINFO: Conecta los sensores por modbus al puerto usb.\r\n");
		//return -1; //no salir solo no iniciar el hilo y notificar que problema ocurrio
	}
	//modbus_set_debug(ctx, TRUE);
    else {
        if (modbus_connect(ctx) == -1) {
            fprintf( fichero_prueba, "Connection failed: %s\n", modbus_strerror(errno));
            fflush( fichero_prueba );
            modbus_free(ctx);
        }
        else{
            rt_task_create(&modbus_sensor_task, "MODBUS", 0, modbus_sensor_task_prio, 0);
            rt_task_start(&modbus_sensor_task, &modbus_sensor, NULL);
        }
    }*/
    
    //modbus}

    /*Hilos de xenomai*/
    //TODO validar user interface se cierra por el inf    
    //rt_task_create(&brix_task, "UART", 0, brix_task_prio, 0);
    //rt_task_create(&modbus_sensor_task, "MODBUS", 0, modbus_sensor_task_prio, 0);
	//rt_task_create(&UserInterface_task, "USUARIO", 0, UserInterface_task_prio, 0);
    rt_task_create(&pru_task, "PRU", 0, pru_task_prio, 0);

	//rt_task_start(&brix_task, &brix, NULL);
    //rt_task_start(&modbus_sensor_task, &modbus_sensor, NULL);
	//rt_task_start(&UserInterface_task, &UserInterface, NULL);
    rt_task_start(&pru_task, &pru, NULL);

    /* Bucle principal que se ejecuta hasta que se reciba un SIGTERM (ejecución del comando kill) */
    while ( estado == 0 )
    {
        sleep( 1 );
    }

    //el pause dio problemas
    //pause(); //No ha necesitado el pause porque hay un ciclo infinito en el hijo

	//rt_task_delete(&sensor_task);
	//rt_task_delete(&brix_task);
	//rt_task_delete(&modbus_sensor_task);
	//rt_task_delete(&UserInterface_task);
    rt_task_delete(&pru_task);

	//UartClose();	//cerrar uart al salir

	fprintf( fichero_prueba, "me voy\n" );
	/* Cerramos el fichero de prueba */
	fclose( fichero_prueba );
	/* Borramos el fichero PID */
	unlink( FICHERO_PID );
	/* Cerramos el log */
	closelog();
}

/* 
 * FIFO0DATA register includes both ADC and channelID
 * so we need to remove the channelID
 */
static unsigned int ProcessingADC1(unsigned int value)
{
	unsigned int result = 0;
	result = value << 20;
	result = result >> 20;
	return result;
}

void getChar(uint16_t h, uint16_t l, char* valor)
{
	uint32_t tempEnC, s, e, m;
	tempEnC = s = e = m = 0;
	tempEnC = h;
	tempEnC = tempEnC << 16;
	tempEnC = tempEnC + l;
	s = (tempEnC & 0x80000000) >> 31;
	e = (tempEnC & 0x7F800000) >> 23;
	m = (tempEnC & 0x007FFFFF);
	printf("\ns: %d",s);
	printf("\ne: %d",e);
	printf("\nm: %d",m);
	//valor = pow(-1,s)*(1.0+m/pow(2,23))*pow(2,(e-127));
	//return valor;
}

char* get_time_string()
{
	struct tm *tm;
	time_t t;
	char *str_time = (char *) malloc(100*sizeof(char));
	t = time(NULL);
	tm = localtime(&t);
	//YYYY-MM-DD HH:MM:SS
	strftime(str_time, 100, "%G-%m-%d %H:%M:%S", tm);
	return str_time;
}


void ph_control(){
    float error = referencia - ph_modbus;
    int k1 = 250;
    int k2 = 100;
    int k3 = 90;
    int k4 = 80;
    int k5 = 70;
    float err = error;

    if (error > 0.15 && error < 0.3) {
        phmas=error*k1;
        phmenos=0;
    }
    else if (error < -0.15 && error > -0.3) {
        phmas=0;
        phmenos=error*-k1;
    }
    else if (error >= 0.3 && error < 0.5) {
        phmas=error*k2;
        phmenos=0;
    } 
    else if (error <= -0.3 && error > -0.5) {
        phmas=0;
        phmenos=error*-k2;
    }
    else if (error >= 0.5 && error < 1) {
        phmas=error*k3;
        phmenos=0;
    }
    else if (error <= -0.5 && error > -1) {
        phmas=0;
        phmenos=error*-k3;
    }
    else if (error >= 1 && error < 2) {
        phmas=error*k4;
        phmenos=0;
    }
    else if (error <= -1 && error > -2) {
        phmas=0;
        phmenos=error*-k4;
    }
    else if (error >= 2 && error < 14) {
        phmas=error*k5;
        phmenos=0;
    }
    else if (error <= -2 && error > -14) {
        phmas=0;
        phmenos=error*-k5;
    }
    else{
        phmas=0;
        phmenos=0;
    }
}
