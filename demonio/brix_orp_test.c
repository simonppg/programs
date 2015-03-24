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

#include "planificacion.h"
#include "bd.h"
#include "sensor.h"
#include "UserInterface.h"



//modbuslib
#include <math.h>
#include <string.h>
#include <errno.h>
#include "modbus.h"
#include "modbus-rtu.h"


RT_TASK sensor_task, control_task, brix_task, modbus_task, UserInterface_task;


/* Prioridades de tareas: 
                     	sensor_task = 99
			control_task = 95
			brix_task = 30 
			modbus_task= 40
			UserInterface_task = 20 */
#define sensor_task_prio 99
#define control_task_prio 95
#define brix_task_prio 30
#define modbus_task_prio 40
#define UserInterface_task_prio 20

#define PRU_NUM_PWM 1
#define PRU_NUM_ADC 0
//#define MIN_DIF	2
float MIN_DIF = 0.01;

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
int pwm0 = 100, pwm1 = 200, pwm2 = 300, pwm3 = 400, pwm4 = 500;
int pwm0_ant = 60, pwm1_ant = 100, pwm2_ant = 100, pwm3_ant = 100, pwm4_ant = 100;
int pwm0_dif = 0, pwm1_dif = 0, pwm2_dif = 0, pwm3_dif = 0, pwm4_dif = 0;
int enablePWM = 0;
int NANO_SECONDS_PER_CYCLE = 240;//160 antes de los enable bits

static void *pruDataMem; 
static unsigned int *pruDataMem1; //AM33XX_DATA 8KB RAM1
static void *sharedMem;
static unsigned int *sharedMem_int;

//variables para el modbus
#define TEMP_REG 2410-1
#define PMC1_REG 2090-1

modbus_t *ctx = NULL;
float valor;
int i;
int slave = -1;
int rc, addr, nb;
uint16_t dest[64], and, or;


/******************************************************************************
* Functions declarations                                                      * 
******************************************************************************/
static unsigned int ProcessingADC1(unsigned int value);
float getFloat(uint16_t h, uint16_t l);
char* get_time_string();
void ph_control();


int enable_cont = 0;
int enable_time = 50;


 
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
	char *vector;
	/*Variables base de datos*/
	int onoff = 0;

    struct stat st;
    FILE *fichero_pid;
    FILE *fichero_prueba;
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
 
    /* Bucle principal que se ejecuta hasta que se reciba un SIGTERM (ejecución del comando kill) */
    while ( estado == 0 )
    {
    	if(onoff == 0)
			onoff = 1;
		else
			onoff = 0;
		asprintf(&vector, "UPDATE bioreactor SET encendido = %d",onoff);
		Update(vector);

        /* Escribimos la cadena, nos aseguramos que se vuelque al disco y esperamos un segundo */
        fprintf( fichero_prueba, "prueba\n" );
        fflush( fichero_prueba );
        sleep( 1 );
    }
 
    fprintf( fichero_prueba, "me voy\n" );
    /* Cerramos el fichero de prueba */
    fclose( fichero_prueba );
    /* Borramos el fichero PID */
        unlink( FICHERO_PID );
    /* Cerramos el log */
    closelog();
}

int main3(int argc, char* argv[])
{
	/*Variables base de datos*/
	char *vector;
	/*Variables base de datos*/
	/*struct timeval tval_before, tval_after, tval_result;
	gettimeofday(&tval_before, NULL);
	long int microseconds;
	long int milliseconds;*/
	int onff = 0;



	//FILE *fp= NULL;
	pid_t process_id = 0;
	pid_t sid = 0;
	// Create child process
	process_id = fork();
	// Indication of fork() failure
	if (process_id < 0)
	{
	printf("fork failed!\n");
	// Return failure in exit status
	exit(1);
	}
	// PARENT PROCESS. Need to kill it.
	if (process_id > 0)
	{
	printf("process_id of child process %d \n", process_id);
	// return success in exit status
	exit(0);
	}
	//unmask the file mode
	umask(0);
	//set new session
	sid = setsid();
	if(sid < 0)
	{
	// Return failure
	exit(1);
	}
	// Change the current working directory to root.
	chdir("/");
	// Close stdin. stdout and stderr
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	// Open a log file in write mode.
	//fp = fopen ("Log.txt", "w+");
	while (1)
	{
		/*gettimeofday(&tval_after, NULL);

		microseconds = (tval_after.tv_sec - tval_before.tv_sec) * 1000000 + ((int)tval_after.tv_usec - (int)tval_before.tv_usec);
		milliseconds = microseconds/1000;
		tval_result.tv_sec = microseconds/1000000;
		tval_result.tv_usec = microseconds%1000000;*/
		if(onff == 0)
			onff = 1;
		else
			onff = 0;
		asprintf(&vector, "UPDATE bioreactor SET encendido = %d)",onff);
		Update(vector);
		
		//Dont block context switches, let the process sleep for some time
		sleep(1);
		//fprintf(fp, "Logging info...%ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
		//fflush(fp);
		// Implement and call some function that does core work for this daemon.
	}
	//fclose(fp);
	return (0);
}

int main2(int argc, char* argv[])
{
	printf("main\n");
	/* Avoids memory swapping for this program */
	mlockall(MCL_CURRENT|MCL_FUTURE);
	/*
	 * Arguments: &task,
	 *            name,
	 *            stack size (0=default),
	 *            priority,
	 *	      Joinable
	 *	      task function
	 *            mode (FPU, start suspended, ...)
	 */
	//pru_pwm{
	/*unsigned int ret;
	tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;
	printf("\nINFO: Starting %s example.\r\n", "PWM Demo with PRU");
	// Initialize the PRU 
	prussdrv_init();
	// Open PRU Interrupt 
	ret = prussdrv_open(PRU_EVTOUT_1);
	if (ret)
	{
		printf("\tERROR: prussdrv_open open failed\n");
		printf("\tINFO: falta habilitar los firmware\r\n");
		return (ret);
	}
	ret = prussdrv_open(PRU_EVTOUT_0);
    if (ret){
        printf("\tERROR: prussdrv_open open failed\n");
        printf("\tINFO: falta habilitar los firmware\r\n");
        return (ret);
    }
	// Get the interrupt initialized
	prussdrv_pruintc_init(&pruss_intc_initdata);
	prussdrv_map_prumem(PRUSS0_PRU1_DATARAM, &pruDataMem);
	//assign the the data RAM address to two pointers	
    pruDataMem1 = (unsigned int*)pruDataMem; //AM33XX_DATA 8KB RAM1,Glocal Memory Address
	printf("\tINFO: Executing example.\r\n");
	prussdrv_exec_program(PRU_NUM_PWM, "./pwm.bin");*/
	//pru_pwm}
	//pru_adc{
    /*printf("\tINFO: Initializing.\r\n");
    prussdrv_map_prumem(PRUSS0_SHARED_DATARAM, &sharedMem);
    sharedMem_int = (unsigned int*) sharedMem;
	/* Executing PRU. * /
    printf("\tINFO: Collecting");
    prussdrv_exec_program (PRU_NUM_ADC, "./ADCCollector.bin");*/
	//pru_adc}
	//modbus{
    /*printf("\tINFO: Lectura de PH y orp\n");
	//ctx = modbus_new_rtu("/dev/ttyUSB0", 19200, 'N', 8, 2);
	//if(ctx == NULL)
	if(modbus_new_rtu("/dev/ttyUSB0", 19200, 'N', 8, 2) == NULL)
	{
		printf("Error al abrir el dispositivo\n");
		printf("\tINFO: Conecta los sensores por modbus al puerto usb.\r\n");
		//return -1;
	}
	//modbus_set_debug(ctx, TRUE);
    if (modbus_connect(ctx) == -1) {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        //return -1;
    }*/
    //modbus}
    printf("creando hilos\n");

	rt_task_create(&sensor_task, "ADC", 0, sensor_task_prio, 0);
	rt_task_create(&UserInterface_task, "USUARIO", 0, UserInterface_task_prio, 0);

	/*#if CONTROL
	rt_task_create(&control_task, "PWM", 0, control_task_prio, 0);
	#endif
	#if BRIX
	//rt_task_create(&brix_task, "SERIAL", 0, brix_task_prio, 0);
	#endif
	#if MODBUS
	rt_task_create(&modbus_task, "MODBUSSERIAL", 0, modbus_task_prio, 0);
	#endif*/
	/*
	 * Arguments: &task,
	 *            task function,
	 *            function argument
	 */
	printf("iniciando hilos\n");

	rt_task_start(&sensor_task, &sensor, NULL);
	rt_task_start(&UserInterface_task, &UserInterface, NULL);

	/*#if CONTROL
	rt_task_start(&control_task, &control, NULL);
	#endif
	#if BRIX
	//rt_task_start(&brix_task, &brix, NULL);
	#endif
	#if MODBUS
	rt_task_start(&modbus_task, &modbus, NULL);
	#endif*/

	pause();

	rt_task_delete(&sensor_task);
	rt_task_delete(&UserInterface_task);

	/*#if CONTROL
	rt_task_delete(&control_task);
	#endif
	#if BRIX
	//rt_task_delete(&brix_task);
	#endif
	#if MODBUS
	rt_task_delete(&modbus_task);
	#endif*/
	
	//pru_pwm{
	/*printf("\tINFO: PRU completed transfer.\r\n");
    prussdrv_pru_clear_event (PRU_EVTOUT_0, PRU0_ARM_INTERRUPT);

	// Disable PRU and close memory mapping
	prussdrv_pru_disable(PRU_NUM_PWM);
    prussdrv_pru_disable(PRU_NUM_ADC);
    prussdrv_exit();*/
	//pru_adc}

	printf("saliendo\n");

	return 0;
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

float getFloat(uint16_t h, uint16_t l)
{
	float valor;
	uint32_t tempEnC, s, e, m;
	tempEnC = s = e = m = 0;
	tempEnC = h;
	tempEnC = tempEnC << 16;
	tempEnC = tempEnC + l;
	s = (tempEnC & 0x80000000) >> 31;
	e = (tempEnC & 0x7F800000) >> 23;
	m = (tempEnC & 0x007FFFFF);
	valor = pow(-1,s)*(1.0+m/pow(2,23))*pow(2,(e-127));
	return valor;
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
