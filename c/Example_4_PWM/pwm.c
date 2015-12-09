#include <stdio.h>
#include <signal.h>
#include <unistd.h>

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

	pwm = fopen("/sys/devices/bone_capemgr.9/slots", "w");
	/*fseek(pwm,0,SEEK_SET);
	fprintf(pwm,"am33xx_pwm");
	fflush(pwm);
	
	fprintf(pwm,"bone_pwm_P8_13");
	fflush(pwm);
*/
	char buf[0x100];
	snprintf(buf, sizeof(buf), "/sys/devices/ocp.3/pwm_test_P8_13.%d/period",11);
	period = fopen(buf,"w");//fopen("/sys/devices/ocp.3/pwm_test_P8_13.#/period", "w");
	duty = fopen("/sys/devices/ocp.3/pwm_test_P8_13.11/duty", "w");
	run = fopen("/sys/devices/ocp.3/pwm_test_P8_13.11/run", "w");

	int dir = 0;
	pulso = 1760;
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

	fclose(pwm);
	fclose(duty);
	fclose(period);
	fclose(run);
	printf("Fin\n");
	return 0;
}

