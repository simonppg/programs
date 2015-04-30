#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <dirent.h>
#include <regex.h>



static int keepRunning = 1;

void intHandler(int dummy) {
    keepRunning = 0;
    printf("saliendo\n");
}

int main()
{
	FILE *duty,*period,*run;
	int periodo = 2000*10000;
	int pulso = 1760*10000;
	int i = 0;

    regex_t regex;
    int reti;
    char msgbuf[100];

	/* Compile regular expression */
    reti = regcomp(&regex, "pwm", 0);
    if( reti ){
    	fprintf(stderr, "Could not compile regex\n");
    }


	DIR *d;
	struct dirent *dir;
	d = opendir("/sys/devices/ocp.3/");
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			/* Execute regular expression */
	        reti = regexec(&regex, dir->d_name, 0, NULL, 0);
	        if( !reti ){
	                puts("Match");
	                printf("%s\n", dir->d_name);
	        }
	        else if( reti == REG_NOMATCH ){
	                //puts("No match");
	        }
	        else{
	                //regerror(reti, &regex, msgbuf, sizeof(msgbuf));
	                //fprintf(stderr, "Regex match failed: %s\n", msgbuf);
	        }
		}
	closedir(d);
	}






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
		//sleep(1);
		usleep(200*1000);
		/*printf("pulso: \n");
		scanf("%d",&pulso);

		pulso *=10000;*/
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

