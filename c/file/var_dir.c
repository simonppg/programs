#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <dirent.h>
#include <regex.h>
#include <string.h>



static int keepRunning = 1;

void intHandler(int dummy) {
    keepRunning = 0;
    printf("saliendo\n");
}

enum PWM_ENUM {
    P8_13, P8_19, P9_14, P9_16, P9_29, P9_31
};

static const char *PWM_STRING[] = {
    "P8_13", "P8_19", "P9_14", "P9_16", "P9_29", "P9_31"
};

int get_pwm_dir(char* path, const char* pwm) {
	regex_t regex;
    int reti;
    char msgbuf[100];

	DIR *sys_dev;
	struct dirent *file;
	char * directory = "/sys/devices/";
	sys_dev = opendir(directory);
	char ocp_dir[50] = {"\0"};
	int ocp_exist = -1;

	if(sys_dev){
		/* Compile regular expression */
	    reti = regcomp(&regex, "ocp", 0);
	    if( reti ){
	    	fprintf(stderr, "Could not compile regex\n");
	    }
		while ((file = readdir(sys_dev)) != NULL)
		{
			/* Execute regular expression */
	        reti = regexec(&regex, file->d_name, 0, NULL, 0);
	        if( !reti ){
                puts("Match");
                printf("%s\n", file->d_name);
                strcat(ocp_dir, directory);
                strcat(ocp_dir, file->d_name);
                printf("%s\n", ocp_dir);
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
	}

	if(ocp_exist == 0){
		DIR *sys_dev_ocp;
		file = NULL;
		sys_dev_ocp = opendir(ocp_dir);
		char pwm_dir[50] = {"\0"};
		char pwm_reg_exp[50] = {"\0"};
		strcat(pwm_reg_exp, "pwm_test_");
		strcat(pwm_reg_exp, pwm);

		if(sys_dev_ocp){
			/* Compile regular expression */
		    reti = regcomp(&regex, pwm_reg_exp, 0);
		    if( reti ){
		    	fprintf(stderr, "Could not compile regex\n");
		    }
			while ((file = readdir(sys_dev_ocp)) != NULL)
			{
				/* Execute regular expression */
		        reti = regexec(&regex, file->d_name, 0, NULL, 0);
		        if( !reti ){
		                puts("Match");
		                printf("%s\n", file->d_name);
		                strcat(pwm_dir, ocp_dir);
		                strcat(pwm_dir, "/");
		                strcat(pwm_dir, file->d_name);
		                printf("%s\n", pwm_dir);
		                strcat(path, pwm_dir);
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
		}
	}

	return -1;
}


typedef struct {
	char name[5];
	char path[50];
	FILE *duty,*period,*run;
	int activo;
} Pwm_s;

//Pwm_s p8_13, p8_19, p9_14, p9_16, p9_29, p9_31;

Pwm_s p8_13 = { .name = {"\0"}, .path = {"\0"}, .duty = NULL, .period = NULL, .run = NULL, .activo = -1 };
Pwm_s p8_19 = { .name = {"\0"}, .path = {"\0"}, .duty = NULL, .period = NULL, .run = NULL, .activo = -1 };
Pwm_s p9_14 = { .name = {"\0"}, .path = {"\0"}, .duty = NULL, .period = NULL, .run = NULL, .activo = -1 };
Pwm_s p9_16 = { .name = {"\0"}, .path = {"\0"}, .duty = NULL, .period = NULL, .run = NULL, .activo = -1 };
Pwm_s p9_29 = { .name = {"\0"}, .path = {"\0"}, .duty = NULL, .period = NULL, .run = NULL, .activo = -1 };
Pwm_s p9_31 = { .name = {"\0"}, .path = {"\0"}, .duty = NULL, .period = NULL, .run = NULL, .activo = -1 };

int open_files(Pwm_s pwm){
	char str_temp[50] = {"\0"};
	strcat(str_temp,pwm.path);
	strcat(str_temp,"/period");
	pwm.period = fopen(str_temp,"w");
	memset(&str_temp[0], 0, sizeof(str_temp));

	strcat(str_temp,pwm.path);
	strcat(str_temp,"/duty");
	pwm.duty = fopen(str_temp,"w");
	memset(&str_temp[0], 0, sizeof(str_temp));

	strcat(str_temp,pwm.path);
	strcat(str_temp,"/run");
	pwm.run = fopen(str_temp,"w");
	if(pwm.period == NULL || pwm.duty == NULL || pwm.run == NULL){
		pwm.activo = -1;
		return -1;
	}
	else{
		pwm.activo = 0;
		return 0;
	}
}

int init_pwms()
{
	strcat(p8_13.name, PWM_STRING[P8_13]);
	strcat(p8_19.name, PWM_STRING[P8_19]);
	strcat(p9_14.name, PWM_STRING[P9_14]);
	strcat(p9_16.name, PWM_STRING[P9_16]);
	strcat(p9_29.name, PWM_STRING[P9_29]);
	strcat(p9_31.name, PWM_STRING[P9_31]);

	//busca si existe el directorio para utilizar el pwm, guarda la ruta en .path
	if(get_pwm_dir(p8_13.path, p8_13.name) == 0) {
		open_files(p8_13);
	}
	if(get_pwm_dir(p8_19.path, p8_19.name) == 0) {
		open_files(p8_19);
	}
	if(get_pwm_dir(p9_14.path, p9_14.name) == 0) {
		open_files(p9_14);
	}
	if(get_pwm_dir(p9_16.path, p9_16.name) == 0) {
		open_files(p9_16);
	}
	if(get_pwm_dir(p9_29.path, p9_29.name) == 0) {
		open_files(p9_29);
	}
	if(get_pwm_dir(p9_31.path, p9_31.name) == 0) {
		open_files(p9_31);
	}

	return 0;
}

int main()
{
	FILE *duty,*period,*run;
	int periodo = 2000*10000;
	int pulso = 1760*10000;
	int i = 0;

	init_pwms();
	
	
	
	char buf[0x100];
	for (i = 0; i < 30; ++i)
	{
		snprintf(buf, sizeof(buf), "/sys/devices/ocp.3/pwm_test_P8_13.%d/period",i);
		period = fopen(buf,"w");
		if(period==NULL){
			//printf("\nno se puedo abrir %s",buf);
		}
		else{
			snprintf(buf, sizeof(buf), "/sys/devices/ocp.3/pwm_test_P8_13.%d/duty",i);
			duty = fopen(buf,"w");
			snprintf(buf, sizeof(buf), "/sys/devices/ocp.3/pwm_test_P8_13.%d/run",i);
			run = fopen(buf,"w");
			break;
		}
	}

	/*duty = fopen("/sys/devices/ocp.3/pwm_test_P8_13.11/duty", "w");
	run = fopen("/sys/devices/ocp.3/pwm_test_P8_13.11/run", "w");*/

	int direction = 0;
	pulso = 1760;
	/*min 1760, max 1950*/

	signal(SIGINT, intHandler);
	do{
		usleep(200*1000);
		printf("pulso: %d, direction: %d\n", pulso, direction);
		if(pulso <= 1950 && direction == 0){
			pulso += 10;
			if(pulso >= 1950)
				direction = 1;
		}
		if(pulso >= 1760 && direction == 1){
			pulso -= 10;
			if(pulso <= 1760)
				direction = 0;
		}

		fseek(period,0,SEEK_SET);
		fprintf(period,"%d",periodo);
		fflush(period);
		
		fseek(duty,0,SEEK_SET);
		fprintf(duty,"%d",pulso*10000);
		fflush(duty);

		fseek(run,0,SEEK_SET);
		fprintf(run,"%d",0);
		fflush(run);

		fseek(run,0,SEEK_SET);
		fprintf(run,"%d",1);
		fflush(run);
	}while(keepRunning);
	
	//while(1);

	//fclose(pwm);
	fclose(duty);
	fclose(period);
	fclose(run);
	printf("Fin\n");
	return 0;
}

