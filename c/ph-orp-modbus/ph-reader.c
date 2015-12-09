#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus.h>
#include <modbus-rtu.h>

modbus_t *ctx = NULL;
int rc, addr, nb, sensor;
uint16_t dest[64], and, or;
int i = 0;

int fun3(int code){
	rc = addr = nb = *dest = and = or = 0;
    printf("In fun3\n");
	printf("addr: \n");
	scanf("%d",&addr);
	printf("nb: \n");
	scanf("%d",&nb);
	//printf("contesto1/2: \n");
	//scanf("%d",&sensor);
	/*if(sensor == 1)
		*/rc = modbus_read_registers( ctx, addr, nb, dest);
	/*if(sensor == 2)
		rc = modbus_read_registers( ctx2, addr, nb, dest);*/
	if (rc == -1) {
	    fprintf(stderr, "%s\n", modbus_strerror(errno));
	    return -1;
	}

	for (i=0; i < rc; i++) {
	    printf("reg[%d]=%d (0x%X)\n", i, dest[i], dest[i]);
	}
	return rc;
}

int fun4(int code){
	rc = addr = nb = *dest = and = or = 0;
    printf("In fun4\n");
	printf("addr: \n");
	scanf("%d",&addr);
	printf("nb: \n");
	scanf("%d",&nb);
	rc = modbus_read_input_registers(ctx, addr, nb, dest);
	if (rc == -1) {
	    fprintf(stderr, "%s\n", modbus_strerror(errno));
	    return -1;
	}

	for (i=0; i < rc; i++) {
	    printf("reg[%d]=%d (0x%X)\n", i, dest[i], dest[i]);
	}
	return rc;
}

int fun16(code){
	rc = addr = nb = *dest = and = or = 0;
	printf("In fun16");
	rc = modbus_mask_write_register(ctx, addr, and, or);
}

int modbus_fun(int code){
	switch(code){
        case 3:
            printf("3\n");
            fun3(code);
            break;
		case 4:
			printf("4\n");
			fun4(code);
			break;
		case 16:
			printf("16\n");
			fun16(code);
			break;
        default:
                printf("Error opcion no valida.\n");
       		return 0;
	}
	return 0;
}

int main(){
	int valor = -1, error = 100;
	int slave=-1;
	printf("Nuevo rtu\n");
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

	printf("Ejecutar comandos.\n");
	int funcCode;
	while(1){
		funcCode = -1;
		printf("Function code: \n");
		scanf("%d",&funcCode);
		printf("Esclavo: \n");
		scanf("%d",&slave);
		modbus_set_slave(ctx, slave);
		if(funcCode == -1){
			printf("fin.\n");
			return 0;
		}
		modbus_fun(funcCode);
	}
	return 0;
}

