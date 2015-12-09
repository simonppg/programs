#include <stdlib.h>

#include <native/task.h>
#include <native/timer.h>
#include <math.h>

#include "modbus.h"
#include "modbus-rtu.h"

#include "planificacion.h"
#include "modbus_sensor.h"
#include "brix_orp_test.h"

void modbus_sensor(void *arg)
{
	fprintf( fichero_prueba, "iniciando modbus_sensor\n" );
	fflush( fichero_prueba );

	// Declaración de variables locales a las tareas
	modbus_t *ctx = NULL;
	float valor;
	int i,j;
	int slave = -1;
	int rc, addr, nb;
	uint16_t dest[64], and, or;


	ctx = modbus_new_rtu("/dev/ttyUSB0", 19200, 'N', 8, 2);
	if(ctx == NULL)
	{
        fprintf( fichero_prueba, "Error al abrir el dispositivo\n");
        fflush( fichero_prueba );
	}
    if (modbus_connect(ctx) == -1) {
        fprintf( fichero_prueba, "Connection failed: %s\n", modbus_strerror(errno));
        fflush( fichero_prueba );
        modbus_free(ctx);
    }

	/*
	 * Arguments: &task (NULL=self), the current task
	 *            start time, delay before release, TM_NOW = none
	 *            period (here: 1 s) 
	 */
	rt_task_set_periodic(NULL, TM_NOW, modbus_sensor_task_period);
	while (1) {
		rt_task_wait_period(NULL);

		fprintf( fichero_prueba, "ph: %f, orp: %f\n", ph_modbus, orp_modbus);
        fflush( fichero_prueba );

		slave = 1;
		modbus_set_slave(ctx, slave);
		addr = PMC1_REG;
		nb = 10;
		rc = modbus_read_registers( ctx, addr, nb, dest);
		ph_modbus = getFloat(dest[3], dest[2]);
		rc = addr = nb = and = or = 0;
		for (j = 0; j < 64; ++j)
		{
			dest[j] = 0;
		}
		sleep(1);

		slave = 4;
		modbus_set_slave(ctx, slave);
		addr = PMC1_REG;
		nb = 10;
		rc = modbus_read_registers( ctx, addr, nb, dest);
		orp_modbus = getFloat(dest[3], dest[2]);
		rc = addr = nb = and = or = 0;
		for (j = 0; j < 64; ++j)
		{
			dest[j] = 0;
		}
		sleep(1);

		/*// Código aqui
		slave = 1;
		modbus_set_slave(ctx, slave);
		//ph_temp
		addr = TEMP_REG;
		nb = 10;
		rc = modbus_read_registers( ctx, addr, nb, dest);
		//printReg(rc, dest);
		temp_modbus = getFloat(dest[3], dest[2]);
		//printf("temperatura: %f\n", temp_modbus);
		//temp_modbus = -1;
		dest[3] = dest[2] = rc = addr = nb = and = or = 0;
		sleep(5);
		//ph_ph
		addr = PMC1_REG;
		nb = 10;
		rc = modbus_read_registers( ctx, addr, nb, dest);
		//printReg(rc, dest);
		ph_modbus = getFloat(dest[3], dest[2]);
		//printf("ph: %f\n", ph_modbus);
		dest[3] = dest[2] = rc = addr = nb = and = or = 0;
		sleep(5);
		//orp_temp
		slave = 4;
		modbus_set_slave(ctx, slave);
		addr = TEMP_REG;
		nb = 10;
		rc = modbus_read_registers( ctx, addr, nb, dest);
		//printReg(rc, dest);
		temp_modbus = getFloat(dest[3], dest[2]);
		//printf("temperatura: %f\n", temp_modbus);
		//temp_modbus = -1;
		dest[3] = dest[2] = rc = addr = nb = and = or = 0;
		sleep(5);
		//orp_orp
		addr = PMC1_REG;
		nb = 10;
		rc = modbus_read_registers( ctx, addr, nb, dest);
		//printReg(rc, dest);
		orp_modbus = getFloat(dest[3], dest[2]);
		//printf("orp: %f\n", orp_modbus);
		//orp_modbus = -1;
		dest[3] = dest[2] = rc = addr = nb = and = or = 0;
		sleep(5);*/
		
		//fprintf( fichero_prueba, "modbus_sensor\n" );
    	//fflush( fichero_prueba );
	}
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