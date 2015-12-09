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

int dump(void *myStruct, long size)
{
	unsigned int i;
	const unsigned char * const px = (unsigned char*)myStruct;
	for (i = 0; i < size; ++i) {
		if( i % (sizeof(int) * 8) == 0){
			printf("\n%08X ", i);
		}
		else if( i % 4 == 0){
			printf(" ");
		}
		printf("%02X", px[i]);
	}

	printf("\n\n");
}

int dumpToFile(void *myStruct, long size)
{
	FILE *f = fopen("dump.txt", "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		return -1;
	}
		
	unsigned int i;
	const unsigned char * const px = (unsigned char*)myStruct;
	for (i = 0; i < size; ++i) {
		fprintf(f, "%x", px[i]);
	}
	fclose(f);
}

int main(int argc, char const *argv[])
{
	open_files(&p8_13);
	printf("\npwm: %s, activo: %d ",p8_13.name, p8_13.activo);
	return 0;
}