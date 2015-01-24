#ejemplo pwm pru1
rm *.out -v
CFLAGS="-D__DEBUG -O2 -mtune=cortex-a8 -march=armv7-a"
MYSQLFLAGS="`mysql_config --cflags --libs`"
XENOMAIFLAGS="-I/usr/xenomai/include -L/usr/xenomai/lib -lxenomai -lnative"
PRUFLAGS="-I am335x_pru_package/pru_sw/app_loader/include -L am335x_pru_package/pru_sw/app_loader/lib -lprussdrv -lpthread -lm"
MODBUSFLAGS="-I. -lm"
USRSRC="bd.c"
MODBUSSRC="modbus.c modbus-rtu.c modbus-data.c"
gcc db_test.c ${USRSRC} -o a.out ${MYSQLFLAGS}