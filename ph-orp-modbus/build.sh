#gcc ph-reader.c ../src/modbus.c -o ph.out -lmodbus -I../src -I../
gcc ph-reader.c modbus.c modbus-rtu.c modbus-data.c -o ph.out -I.
gcc ciclo.c modbus.c modbus-rtu.c modbus-data.c -o orp-ph.out -I.
