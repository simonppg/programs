/*Cacracteres*/#include <stdio.h>
#include <stdlib.h>
int main(){
// Declaramos la varible número, pausa y p_cada:
    int    numero,pausa,p_cada;
// Cada cuantas lineas quieres la pausa?
    p_cada=20;
    pausa=p_cada;
    for(numero=0;numero<257;numero++){
    printf("\t\t %i equivale a %c\r\n",numero,numero);
    if(numero>p_cada){
    system("pause");
    p_cada+=pausa;
    }}
    system("pause");
    return 0;
    }
