#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "bd.h"

char *vector;

int main(int argc, char const *argv[])
{
	int barra = 40;
	int idaVuelta = 1;
	while(1){
		usleep(200);
		if(idaVuelta == 1){//incrementa
			(barra > 90) ? idaVuelta = 0 : (barra = barra + 10);
		}
		else{//decrementa
			(barra < 1) ? idaVuelta = 1 : (barra = barra - 10);
		}
		asprintf(&vector, "UPDATE variables SET barra_superior = %d WHERE 1", barra);
		Update(vector);
		printf("\n\n%d",barra);
	}
	

	return 0;
}