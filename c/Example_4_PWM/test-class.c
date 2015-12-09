#include <stdio.h>
#include <signal.h>

#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <dirent.h>
#include <regex.h>
#include <string.h>

typedef struct {
	char name[5];
	char path[50];
	FILE *duty,*period,*run;
	int activo;
} Pwm_s;
#define PERIODO 2000*10000 //50Hz o 20ms

static Pwm_s p8_13 = { .name = {"\0"}, .path = {"\0"}, .duty = NULL, .period = NULL, .run = NULL, .activo = -1 };
/*static Pwm_s p8_19 = { .name = {"\0"}, .path = {"\0"}, .duty = NULL, .period = NULL, .run = NULL, .activo = -1 };
static Pwm_s p9_14 = { .name = {"\0"}, .path = {"\0"}, .duty = NULL, .period = NULL, .run = NULL, .activo = -1 };
static Pwm_s p9_16 = { .name = {"\0"}, .path = {"\0"}, .duty = NULL, .period = NULL, .run = NULL, .activo = -1 };
static Pwm_s p9_29 = { .name = {"\0"}, .path = {"\0"}, .duty = NULL, .period = NULL, .run = NULL, .activo = -1 };
static Pwm_s p9_31 = { .name = {"\0"}, .path = {"\0"}, .duty = NULL, .period = NULL, .run = NULL, .activo = -1 };*/

static int hilo_init();
//static int hilo_run();
//static int hilo_finish();
static int ehrpwm_setPwm_period(Pwm_s *pwm);
//static int ehrpwm_setPwm_duty(Pwm_s *pwm, int ms);
//static int ehrpwm_setPwm_run(Pwm_s *pwm, int run);
static int get_pwm_dir(char* path, const char* pwm);
static int open_files(Pwm_s *pwm);
//static int close_files(Pwm_s *pwm);

enum PWM_ENUM {
    P8_13, P8_19, P9_14, P9_16, P9_29, P9_31
};

static const char *PWM_STRING[] = {
    "P8_13", "P8_19", "P9_14", "P9_16", "P9_29", "P9_31"
};



static int keepRunning = 1;

void intHandler(int dummy) {
    keepRunning = 0;
    printf("saliendo\n");
}

int main()
{
	FILE *pwm,*duty,*period,*run;
	int periodo = 2000*10000;
	int pulso = 1760*10000;

	pwm = fopen("/sys/class/pwm/export", "w");
	fseek(pwm,0,SEEK_SET);
	fprintf(pwm,"0");
	fflush(pwm);

	fseek(pwm,0,SEEK_SET);
	fprintf(pwm,"3");
	fflush(pwm);

	fseek(pwm,0,SEEK_SET);
	fprintf(pwm,"5");
	fflush(pwm);


	char buf[0x100];
	snprintf(buf, sizeof(buf), "/sys/devices/ocp.3/pwm_test_P8_13.%d/period",11);
	//period = fopen(buf,"w");
	//duty = fopen("/sys/devices/ocp.3/pwm_test_P8_13.11/duty", "w");
	//run = fopen("/sys/devices/ocp.3/pwm_test_P8_13.11/run", "w");

	int dir = 0;
	pulso = 1760;
	hilo_init();
	/*min 1760, max 1950*/

	signal(SIGINT, intHandler);
	do{
		//sleep(1);
		usleep(200*1000);
		/*printf("pulso: \n");
		scanf("%d",&pulso);

		pulso *=10000;*/
		printf("pulso: %d, dir: %d\n", pulso, dir);
		if(pulso <= 1950 && dir == 0){
			pulso += 10;
			if(pulso >= 1950)
				dir = 1;
		}
		if(pulso >= 1760 && dir == 1){
			pulso -= 10;
			if(pulso <= 1760)
				dir = 0;
		}

		fseek(p8_13.period,0,SEEK_SET);
		fprintf(p8_13.period,"%d",periodo);
		fflush(p8_13.period);
		
		fseek(p8_13.duty,0,SEEK_SET);
		fprintf(p8_13.duty,"%d",pulso*10000);
		fflush(p8_13.duty);

		fseek(p8_13.run,0,SEEK_SET);
		fprintf(p8_13.run,"%d",0);
		fflush(p8_13.run);

		fseek(p8_13.run,0,SEEK_SET);
		fprintf(p8_13.run,"%d",1);
		fflush(p8_13.run);
	}while(keepRunning);
	
	//while(1);

	fclose(pwm);
	fclose(p8_13.duty);
	fclose(p8_13.period);
	fclose(p8_13.run);
	printf("Fin\n");
	return 0;
}



static int hilo_init()
{
	//No se puede cambiar la frecuencia si se estan usando los dos :-( fuente: https://randomlinuxhacks.wordpress.com/2014/09/16/changing-pwm-period-on-beaglebone-black/
	//ehrpwm_setPwm_period(&p9_31);
	//ehrpwm_setPwm_period(&p9_14);
	//ehrpwm_setPwm_period(&p8_19);
	ehrpwm_setPwm_period(&p8_13);

	strcat(p8_13.name, "5");
	/*strcat(p8_19.name, PWM_STRING[P8_19]);
	strcat(p9_14.name, PWM_STRING[P9_14]);
	strcat(p9_16.name, PWM_STRING[P9_16]);
	strcat(p9_29.name, PWM_STRING[P9_29]);
	strcat(p9_31.name, PWM_STRING[P9_31]);*/

	//busca si existe el directorio para utilizar el pwm, guarda la ruta en .path
	syslog( LOG_ERR, "[] intenta abrir %s%s", p8_13.path, p8_13.name);
	if(get_pwm_dir(p8_13.path, p8_13.name) == 0) {
		open_files(&p8_13);
	}
	syslog( LOG_ERR, "[] intenta abrir %s%s", p8_13.path, p8_13.name);
	/*if(get_pwm_dir(p8_19.path, p8_19.name) == 0) {
		//open_files(&p8_19);
	}
	if(get_pwm_dir(p9_14.path, p9_14.name) == 0) {
		//open_files(&p9_14);
	}
	if(get_pwm_dir(p9_16.path, p9_16.name) == 0) {
		//open_files(&p9_16);
	}
	if(get_pwm_dir(p9_29.path, p9_29.name) == 0) {
		//open_files(&p9_29);
	}
	if(get_pwm_dir(p9_31.path, p9_31.name) == 0) {
		open_files(&p9_31);
	}*/

	return 0;
}

static int get_pwm_dir(char* path, const char* pwm) {
	regex_t regex;
    int reti;
    char msgbuf[100];

	DIR *sys_dev;
	struct dirent *file;
	char * directory = "/sys/class/pwm/";
	sys_dev = opendir(directory);
	char ocp_dir[50] = "/sys/class/pwm";
	int ocp_exist = 0;

	/*if(sys_dev){
		/* Compile regular expression * /
	    reti = regcomp(&regex, "ocp", 0);
	    if( reti ){
	    	fprintf(stderr, "Could not compile regex\n");
	    }
		while ((file = readdir(sys_dev)) != NULL)
		{
			/* Execute regular expression * /
	        reti = regexec(&regex, file->d_name, 0, NULL, 0);
	        if( !reti ){
                puts("Match");
                printf("%s\n", file->d_name);
                strcat(ocp_dir, directory);
                strcat(ocp_dir, file->d_name);
                printf("%s\n", ocp_dir);
                syslog( LOG_INFO, "[] intentando dir %s", ocp_dir);
                ocp_exist = 0;
	        }
	        else if( reti == REG_NOMATCH ){
	                //puts("No match");
	        }
	        else{
	                //regerror(reti, &regex, msgbuf, sizeof(msgbuf));
	                //fprintf(stderr, "Regex match failed: %s\n", msgbuf);
	        }
		}
		closedir(sys_dev);
	}*/

	if(ocp_exist == 0){
		DIR *sys_dev_ocp;
		file = NULL;
		sys_dev_ocp = opendir(ocp_dir);
		char pwm_dir[50] = {"\0"};
		char pwm_reg_exp[50] = {"\0"};
		strcat(pwm_reg_exp, "pwm");
		//strcat(pwm_reg_exp, pwm);
		syslog( LOG_INFO, "[] intentando abrir_ %s", pwm_reg_exp);
					strcat(pwm_dir, ocp_dir);
	                strcat(pwm_dir, "/");
	                strcat(pwm_dir, pwm_reg_exp);
	                strcat(path, pwm_dir);
	                return 0;

		/*if(sys_dev_ocp){
			/* Compile regular expression * /
		    reti = regcomp(&regex, pwm_reg_exp, 0);
		    if( reti ){
		    	fprintf(stderr, "Could not compile regex\n");
		    }
			while ((file = readdir(sys_dev_ocp)) != NULL)
			{
				/* Execute regular expression * /
		        reti = regexec(&regex, file->d_name, 0, NULL, 0);
		        if( !reti ){
		                puts("Match");
		                printf("%s\n", file->d_name);
		                strcat(pwm_dir, ocp_dir);
		                strcat(pwm_dir, "/");
		                strcat(pwm_dir, file->d_name);
		                printf("%s\n", pwm_dir);
		                strcat(path, pwm_dir);
		                syslog( LOG_INFO, "[] intentando path %s", path);
		                return 0;
		        }
		        else if( reti == REG_NOMATCH ){
		                //puts("No match");
		        }
		        else{
		                //regerror(reti, &regex, msgbuf, sizeof(msgbuf));
		                //fprintf(stderr, "Regex match failed: %s\n", msgbuf);
		        }
			}
			closedir(sys_dev_ocp);
		}*/
	}

	return -1;
}

static int open_files(Pwm_s *pwm){
	char str_temp[50] = {"\0"};
	strcat(str_temp,pwm->path);
	strcat(str_temp,"/period_ns");
	pwm->period = fopen(str_temp,"w");
	memset(&str_temp[0], 0, sizeof(str_temp));

	strcat(str_temp,pwm->path);
	strcat(str_temp,"/duty_ns");
	pwm->duty = fopen(str_temp,"w");
	memset(&str_temp[0], 0, sizeof(str_temp));

	strcat(str_temp,pwm->path);
	strcat(str_temp,"/run");
	pwm->run = fopen(str_temp,"w");
	if(pwm->period == NULL || pwm->duty == NULL || pwm->run == NULL){
		pwm->activo = -1;
		syslog( LOG_ERR, "[] ERROR: No se pudo abrir los archivos del pwm %s", pwm->name);
		return -1;
	}
	else{
		syslog( LOG_INFO, "[] Abriendo los archivos del pwm %s", pwm->name);
		pwm->activo = 0;
		return 0;
	}
}

static int ehrpwm_setPwm_period(Pwm_s *pwm) {
	if(pwm->activo == 0){
		fseek(pwm->period, 0, SEEK_SET);
		fprintf(pwm->period, "%d", PERIODO);
		fflush(pwm->period);
		//syslog( LOG_INFO, "pwm: %s period: %d", pwm->name, PERIODO);
		return 0;
	}
	return -1;
}