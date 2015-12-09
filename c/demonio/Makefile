


###############################################################################
#	Makefile core/kernel
###############################################################################

CC = gcc
CPP = g++
AS = pasm
LD = ld
AR = ar

BUILD = build/

CFLAGS = -D__DEBUG -O2 -mtune=cortex-a8 -march=armv7-a
MYSQLFLAGS = `mysql_config --cflags --libs`
XENOMAIFLAGS = -I/usr/xenomai/include -L/usr/xenomai/lib -lxenomai -lnative
PRUFLAGS =-I am335x_pru_package/pru_sw/app_loader/include -L am335x_pru_package/pru_sw/app_loader/lib -lprussdrv -lpthread -lm
MODBUSFLAGS =-I. -lm
#USRSRC = movil.c bd.c
#MODBUSSRC = modbus.c modbus-rtu.c modbus-data.c

KOBJS=\
	bd.o\
	modbus.o\
	modbus-rtu.o\
	modbus-data.o\
	sensor.o\
	UserInterface.o\
	brix_orp_test.o\

vpath %.c $(SRC_DIR)
vpath %.S $(SRC_DIR)
VPATH = $(BUILD)


OBJ-C= $(wildcard *.c)
SRCC =$(OBJ-C:.c=.o)

OBJ-P=$(wildcard *.p)
SRCS= $(OBJ-P:%.p=%)

OBJ-I=$(wildcard *.i)
SRCI= $(OBJ-I:.i=.o)

COBJ = $(patsubst %.c,$(BUILD)%.o,$(SRCC))

all: sistema.out

rebuild: all

$(COBJ):  %.o:  %.c
	$(CC) -c $(CFLAGS) $(XENOMAIFLAGS) $(PRUFLAGS) $(MYSQLFLAGS) $< -o $@
 
$(SRCS): $(OBJ-P)
	$(AS) -b $@.p

clean: 
	-rm -f *.o 
	-rm -f $(BUILD)*.o
	-rm -r $(BUILD) 
	-rm -f $(BUILD)output.elf
	-rm *.out -v
	-rm *.bin -v

sistema.out: $(COBJ) $(SRCS)
	$(CC) $(KOBJS) $(CFLAGS) $(XENOMAIFLAGS) $(PRUFLAGS) $(MYSQLFLAGS) -o sistema.out
