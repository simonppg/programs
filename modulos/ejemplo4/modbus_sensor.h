#if !defined (_MODBUS_SENSOR_H_)
#define _MODBUS_SENSOR_H_

void modbus_sensor(void *arg);
float getFloat(uint16_t h, uint16_t l);

//extern modbus_t *ctx; //variable para leer desde el modbus


#endif
