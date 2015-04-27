#include <stdio.h>

enum MotorPAP_Enable{
	MOTOR_PAP1_ENABLE = 1 << 0,
	MOTOR_PAP2_ENABLE = 1 << 2,
	MOTOR_PAP3_ENABLE = 1 << 4,
	MOTOR_PAP4_ENABLE = 1 << 6,
	MOTOR_PAP5_ENABLE = 1 << 10
};

#define BIT(x) (1 << (x))
#define SETBITS(x,y) ((x) |= (y))
#define CLEARBITS(x,y) ((x) &= (~(y)))
#define SETBIT(x,y) SETBITS((x), (BIT((y))))
#define CLEARBIT(x,y) CLEARBITS((x), (BIT((y))))
#define BITSET(x,y) ((x) & (BIT(y)))
#define BITCLEAR(x,y) !BITSET((x), (y))
#define BITSSET(x,y) (((x) & (y)) == (y))
#define BITSCLEAR(x,y) (((x) & (y)) == 0)
#define BITVAL(x,y) (((x)>>(y)) & 1)

/* set n-th bit in x */
#define B_SET(x, n)      ((x) |= (1<<(n)))
/* unset n-th bit in x */
#define B_UNSET(x, n)    ((x) &= ~(1<<(n)))

unsigned int enableBits = 0;

int pru_setEnableBit(int enable_bit_number) {
	switch(enable_bit_number){ //Numero de motores disponibles
		case MOTOR_PAP1_ENABLE:
		case MOTOR_PAP2_ENABLE:
		case MOTOR_PAP3_ENABLE:
		case MOTOR_PAP4_ENABLE:
		case MOTOR_PAP5_ENABLE:
			B_SET(enableBits, enable_bit_number);
			break;
		default:
			return -1;
	}
	return 0;
}

int main (){
	printf("\n");

	printf("\nMOTOR_PAP1_ENABLE %d",MOTOR_PAP1_ENABLE);
	printf("\nMOTOR_PAP2_ENABLE %d",MOTOR_PAP2_ENABLE);
	printf("\nMOTOR_PAP3_ENABLE %d",MOTOR_PAP3_ENABLE);
	printf("\nMOTOR_PAP4_ENABLE %d",MOTOR_PAP4_ENABLE);
	printf("\nMOTOR_PAP5_ENABLE %d",MOTOR_PAP5_ENABLE);

	printf("\nMOTOR_PAP1_ENABLE %x",MOTOR_PAP1_ENABLE);
	printf("\nMOTOR_PAP2_ENABLE %x",MOTOR_PAP2_ENABLE);
	printf("\nMOTOR_PAP3_ENABLE %x",MOTOR_PAP3_ENABLE);
	printf("\nMOTOR_PAP4_ENABLE %x",MOTOR_PAP4_ENABLE);
	printf("\nMOTOR_PAP5_ENABLE %x",MOTOR_PAP5_ENABLE);

	//pru_setEnableBit(0);
	SETBIT(enableBits, 10);
	printf("\nE_B %x", enableBits);

	printf("\n");
	return 0;
}