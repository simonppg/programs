#!/bin/sh
cc -c arp.c
cc -c ip.c
cc test.c arp.o ip.o -o test.out