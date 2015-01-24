#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "bd.h"

char *vector;

int main(int argc, char const *argv[])
{
	int barra = 40;
	while(1){
		usleep(500);
		(barra > 100) ? barra = 0 : barra++;
		asprintf(&vector, "UPDATE variables SET barra_superior = %d WHERE 1", barra);
		Update(vector);
	}
	

	return 0;
}