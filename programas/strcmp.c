#include <stdio.h>

void main ()
{
	char **array, **argv;
	int i;
  
  	for( i = 0; i < 10; i++){
    	array[i][0] = '\0';
  	}
  	for( i = 0; i < 10; i++){
    	argv[i][0] = '\0';
  	}

	for( i = 0; i < 7; i++){
		if(strcmp(array[i], argv[i]))
			printf("\nIguales");
		else
			printf("\nEnviar al bioreactor");
	}

}