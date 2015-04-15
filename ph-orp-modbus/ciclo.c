#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus.h>
#include <modbus-rtu.h>
#include <math.h>

modbus_t *ctx = NULL;

//lista de registros arc sensors
#define ADDRESS 4096-1 	/*N_reg 2, 
						Descrip: direccion del sensor en la red modbus
						Modbus func: 3, 4, 16
						I/O U/A/S - S
						*/
#define D_PMC1 2080-1 	/*N_reg 8, 
						Descrip: descripcion de PCM1
						Modbus func: 3, 4
						I/O U/A/S - none
						*/
#define APU_PMC1 2088-1 /*N_reg 2, 
						Descrip: Available physical units of PMC1
						Modbus func: 3, 4
						I/O U/A/S - none
						*/
#define RMV_PMC1 2090-1 /*N_reg 10, 
						Descrip: read the measurement values of PMC1
						Modbus func: 3, 4
						I/O U/A/S - none
						*/

float getFloat(uint16_t h, uint16_t l);

int main(){
	float val;
	uint32_t temperatura = 0;
	int i,j;
	int valor = -1, error = 100;
	int slave=-1;
	int rc, addr, nb, sensor;
	uint16_t dest[64], and, or;
	printf("Lectura de PH y orp\n");
	ctx = modbus_new_rtu("/dev/ttyUSB0", 19200, 'N', 8, 2);
	if(ctx == NULL)
	{
		printf("Error al abrir el dispositivo\n");
		return -1;
	}
	modbus_set_debug(ctx, TRUE);
    if (modbus_connect(ctx) == -1) {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        return -1;
    }
	int funcCode;
	while(1){
		funcCode = -1;
		printf("PH: \n");
		slave = 1;
		modbus_set_slave(ctx, slave);
		addr = RMV_PMC1;
		nb = 10;
		rc = modbus_read_registers( ctx, addr, nb, dest);
		for (i=0; i < rc; i++) {
		    printf("reg[%d]=%d (0x%X) %c\n", i, dest[i], dest[i], dest[i]);
		}
		val = getFloat(dest[3], dest[2]);
		printf("val: %d, 0x%x %f\n", val, val, val);
		val = rc = addr = nb = and = or = 0;
		for (j = 0; j < 64; ++j)
		{
			dest[j] = 0;
		}
		sleep(5);

		/*printf("ORP: \n");
		slave = 4;
		modbus_set_slave(ctx, slave);
		addr = 2409;
		nb = 10;
		rc = modbus_read_registers( ctx, addr, nb, dest);
		for (i=0; i < rc; i++) {
	    	printf("reg[%d]=%d (0x%X)\n", i, dest[i], dest[i]);
		}
		temperatura = dest[3];
		temperatura = temperatura << 16;
		temperatura = temperatura + dest[2];
		printf("Temperatura: %d, 0x%x\n", temperatura, temperatura);
		rc = addr = nb = *dest = and = or = 0;
		temperatura = 0;
		sleep(5);*/
	}
	return 0;
}

float getFloat(uint16_t h, uint16_t l)
{
	float valor;
	uint32_t tempEnC, s, e, m;
	tempEnC = s = e = m = 0;
	tempEnC = h;
	tempEnC = tempEnC << 16;
	tempEnC = tempEnC + l;
	s = (tempEnC & 0x80000000) >> 31;
	e = (tempEnC & 0x7F800000) >> 23;
	m = (tempEnC & 0x007FFFFF);
	valor = pow(-1,s)*(1.0+m/pow(2,23))*pow(2,(e-127));
	return valor;
}
