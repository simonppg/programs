#include <stdio.h>



typedef struct {
	char name[5];
	char path[50];
	FILE *duty,*period,*run;
	int activo;
} Pwm_s;

Pwm_s p8_13 = { .name = {"\0"}, .path = {"\0"}, .duty = NULL, .period = NULL, .run = NULL, .activo = -1 };

static int open_files(Pwm_s *pwm){
	pwm->activo = 0;
}

int main(int argc, char const *argv[])
{
	open_files(&p8_13);
	printf("\npwm: %s, activo: %d ",p8_13.name, p8_13.activo);
	return 0;
}