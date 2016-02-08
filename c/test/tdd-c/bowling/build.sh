#!/bin/sh
echo "========================================================="
echo "TEST"
echo "========================================================="
gcc -std=c99 -Wall bowling_game_test.c bowling_game.c && ./a.out
echo "========================================================="
echo "STATIC ANALISYS"
echo "========================================================="
splint bowling_game_test.c
splint bowling_game.c
splint bowling_game.h
