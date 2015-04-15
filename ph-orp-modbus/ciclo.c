#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus.h>
#include <modbus-rtu.h>

modbus_t *ctx = NULL;

//lista de registros arc sensors
#define ADDRESS 4096 	/*N_reg 2, 
						Descrip: direccion del sensor en la red modbus
						Modbus func: 3, 4, 16
						I/O U/A/S - S
						*/

int main(){
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
		addr = 4096-1;
		nb = 2;
		rc = modbus_read_registers( ctx, addr, nb, dest);
		for (i=0; i < rc; i++) {
		    printf("reg[%d]=%d (0x%X)\n", i, dest[i], dest[i]);
		}
		rc = addr = nb = and = or = 0;
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
