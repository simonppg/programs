#!/bin/bash
gcc -o server.out shm_server.c -lrt
gcc -o client.out shm_client.c -lrt