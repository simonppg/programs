#include <stdio.h>

int main(){

	int adminPass = 18111978;
	short dest[64];
	int ant[64];
	int i = 0;

	printf("\n%d ",adminPass);
	for ( i = 0; i < 64; ++i)
	{
		dest[i] = 0;
		ant[i] = 0;
	}

	/*dest[0] = 0x0;
	dest[1] = 0xC;
	dest[2] = (adminPass >> 16) & 0xffff;
	dest[3] = adminPass & 0xffff;*/

	/*dest[2] = adminPass / 100000;
	dest[3] = adminPass % 100000;*/

	/*for ( i = 0; i < 4; ++i)
	{
		printf("%d_", dest[i]);
	}
	printf("\n");
	for ( i = 0; i < 4; ++i)
	{
		printf("%x_", dest[i]);
	}

	printf("\npass: %d", dest[2] + (dest[3] << 16));*/

	ant[0] = adminPass;

	for ( i = 0; i < 16; ++i)
	{
		dest[i+2] = (ant[i] - (ant[i]/16)*16);
		ant[i+1] = ant[i]/16;
		//TODO guardar dos valores en un mismo offset del vector
		//[0][0][a][e][d][5][4][1][1][0][0][0][0][0][0][0] //trama generada por este programa y la segunda es la generada por modbus, nota como tambien cuenta la parte alta del vector
		//[01][10][10][BF][00][08][10][00][00][00][0C][00][0A][00][0E][00][0D][00][05][00][04][00][01][E9][3D]
		//printf("\nant %d_",ant[i]);
	}
	printf("\n");
	for ( i = 0; i < 16; ++i)
	{
		printf("[%x]", dest[i]);
	}
	printf("\n");
	for ( i = 0; i < 16; ++i)
	{
		printf("[%d]", ant[i]);
	}

	
	/*printf("\nvalor: %d",adminPass - (adminPass/16)*16);
	printf("\n%ld",sizeof(char));
	printf("\n%ld",sizeof(short));*/


	return 0;
}


/*18 111 978/16 
1 131 998/16
70749/16
4421/16
276/16
17/16
1/16*/