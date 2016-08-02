#include <stdio.h>
typedef unsigned int _alineacion;

typedef union head{
    struct {
        unsigned int size;
        union head *sig;
    }head;
    _alineacion _alineacion;
}Head;

int main()
{
    int b[] = { 10, 20, 30, 40 };
    int *ptrB = b;
    int i;
    int desplazamiento;

    printf("\nArreglo b impreso por subindices de arreglos\n");
    for ( i = 0; i < 4; i++ )
        printf( "%d = %d\n", i, b[i]);

    printf("\nArreglo b impreso por desplazamiento\n");
    for ( desplazamiento = 0; desplazamiento < 4; desplazamiento++)
        printf( "%d = %d\n", desplazamiento, *( b + desplazamiento));

    printf("\nApuntador ptrB impreso por subindices de arreglos\n");
    for ( i = 0; i < 4; i++ )
        printf( "%d = %d\n", i, ptrB[ i ] );
 
    printf("\nApuntador ptrB impreso por desplazamiento\n");
    for ( desplazamiento = 0; desplazamiento < 4; desplazamiento++ )
        printf( "%d = %d\n", desplazamiento, *( ptrB + desplazamiento));

    Head hola[10];
    hola[0].head.size =0;
    hola[1].head.size =1;
    hola[2].head.size =2;
    hola[3].head.size =3;
    Head *ptr = hola;

    printf("\nvalor 1: %d",ptr->head.size);
    ptr += 1;
    printf("\nvalor 1: %d",ptr->head.size);
    printf("\nHead.size %ld\n",sizeof(Head)>>2);
   
   return 0;
}







