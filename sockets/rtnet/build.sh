#!/bin/bash
gcc tarjeta.c -o server.out -lm -I/usr/xenomai/include -L/usr/xenomai/lib -lxenomai -lnative