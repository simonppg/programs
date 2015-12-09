
ARMGNU ?= arm-none-eabi

#COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding
COPS = -O2 -nostdlib -nostartfiles -ffreestanding 

#gcc: uartx01.hex uartx01.bin

all: pub.elf

clean:
	rm -f *.out
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -f *.list
	rm -f *.img
	rm -f *.bc
	rm -f *.clang.opt.s

pub.elf: middleware.c pub.c
	gcc middleware.c pub.c