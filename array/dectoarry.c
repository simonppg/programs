#include <stdio.h>

float decToHex(int user, int pass, short *dest)
{
	int i = 0,j=0;
	int ant[64];
	char lo1,hi1,lo2,hi2;
	lo1 = hi1 = lo2 = hi2 = 0;
	for ( i = 0; i < 64; ++i)
	{
		dest[i] = 0;
		ant[i] = 0;
	}
	ant[0] = pass;
	i=0;
	while(ant[i] > 0 && i<64)
	{
		ant[i+1] = ant[i]/16;
		i++;
	}
	printf("\n");
	i=0;
	while(ant[i] > 0)
	{
		j = 0;
		while(j < 4)
		{
			switch(j){
				case 0:
					lo2 = (ant[i] - (ant[i]/16)*16);
					//printf("_%d",hi1);
					break;
				case 1:
					hi2 = (ant[i+1] - (ant[i+1]/16)*16);
					//printf("_%d",lo1);
					break;
				case 2:
					lo1 = (ant[i+2] - (ant[i+2]/16)*16);
					//printf("_%d",hi2);
					break;
				case 3:
					hi1 = (ant[i+3] - (ant[i+3]/16)*16);
					//printf("_%d",lo2);
					break;
			}			
			j++;
		}
		printf("  i:%d %x%x%x%x  ",((i/4)+1),lo2,hi2,lo1,hi1);
		dest[4-((i/4)+1)] = lo2 | (hi2) << 4 | (lo1) << 8 | (hi1) << 12;
		//dest[4-(i-(i/2)+1)] = lo2 | (hi2) << 4 | (lo1) << 8 | (hi1) << 16;

		//dest[4-(i-(i/2)+1)] = lo | (hi1) << 8;
		//dest[3-(i-(i/2))] |= lo;
		//dest[3-(i-(i/2)+1)] |= (hi1) << 8;
		lo1 = hi1 = lo2 = hi2 = 0;
		i += 4;
	}
	dest[1] += user;
	/*printf("\n");
	for ( i = 0; i < 4; ++i)
	{
		lo = dest[i] & 0xFF;
		hi = dest[i] >> 8;

		printf("[%x]",lo);
		printf("[%x]",hi);
	}*/
}

int main(){

	//int adminPass = 2227169;//nada
	int adminPass = 18111978;//0xc
	//int adminPass = 16021966;//0x30
	
	short dest[64];
	
	int i = 0,j=0;
	char lo = 0;
	char hi = 0;

	decToHex(0x0C, adminPass, dest);
	printf("\n");
	//decToHexmal(0xC, adminPass, dest);

	printf("\n\n");
	for ( i = 0; i < 4; ++i)
	{
		printf("[%x]", dest[i]);
	}
	printf("\n");
	return 0;
}
/*[0,1][1,4][5,d][e,a]
[c][1][1][4][5][d][e][a] //mi trama
[01]//slave
[10]//16 escritura
[10][BF]//addr 4288-1
[00][04]//numero de registros
[08]//no se
[01][0C]
[04][01]
[0D][05]
[0A][0E]
[7A][81]//fin trama

//trama 2
[01]
[10]
[10][BF]
[00][04]
[08]
[00][00]
[00][0C]
[01][14]
[5D][EA]
[36][26]
*/