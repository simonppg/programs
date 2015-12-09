#include <stdio.h>

int main(int argc, char const *argv[])
{
	int frequency; // pulsos por segundo
	int rpm; // revoliciones por minuto
	float ppr; // ppr pulsos por revolicion
	float ppp; // paso por pulso

	ppp = 1.8;
	ppr = 360/ppp; 

	rpm = 400;
	frequency = (rpm/60)*ppr;
	printf("\nfreq: %d",frequency);
	printf("\nrpm: %d",rpm);


	rpm = (frequency/ppr)*60;
	printf("\nfreq: %d",frequency);
	printf("\nrpm: %d",rpm);

	printf("\n");
	return 0;
}