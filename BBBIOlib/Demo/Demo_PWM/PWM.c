
#include <stdio.h>
#include <stdlib.h>
#include "../../BBBio_lib/BBBiolib.h"
/* -------------------------------------------------------------- */
int pwm_conf(unsigned int PWMID);
int pwm_enable(unsigned int PWMID);
int pwm_disable(unsigned int PWMID);

float pulso = 7.5;
int dir = 0;

int main(void)
{
	iolib_init();

	while(1) {
		printf("pulso: %f, dir: %d\n", pulso, dir);
		if(pulso <= 12.5 && dir == 0){
			pulso += 0.5;
			if(pulso >= 12.5)
				dir = 1;
		}
		if(pulso >= 2.5 && dir == 1){
			pulso -= 0.5;
			if(pulso <= 2.5)
				dir = 0;
		}
		pwm_disable(BBBIO_PWMSS0);
		pwm_disable(BBBIO_PWMSS1);
		pwm_disable(BBBIO_PWMSS2);
		BBBIO_PWMSS_Setting(BBBIO_PWMSS0, 50.0f, pulso, 50.0);
		BBBIO_PWMSS_Setting(BBBIO_PWMSS1, 50.0f, pulso, 50.0);
		BBBIO_PWMSS_Setting(BBBIO_PWMSS2, 50.0f, pulso, 50.0);
		pwm_enable(BBBIO_PWMSS0);
		pwm_enable(BBBIO_PWMSS1);
		pwm_enable(BBBIO_PWMSS2);
		sleep(1);
		
	}
	pwm_disable(BBBIO_PWMSS0);
	pwm_disable(BBBIO_PWMSS1);
	pwm_disable(BBBIO_PWMSS2);

	iolib_free();
	return(0);
}

int pwm_conf(unsigned int PWMID) {
	BBBIO_PWMSS_Setting(PWMID , 1000000.0f ,50.0 , 50.0);
	printf("PWM %d setting\n", PWMID);
}

int pwm_enable(unsigned int PWMID){
	printf("PWM %d enable\n", PWMID);
	BBBIO_ehrPWM_Enable(PWMID);
}

int pwm_disable(unsigned int PWMID){
	printf("PWM %d disable\n", PWMID);
	BBBIO_ehrPWM_Disable(PWMID);
}