#include <stdio.h>

void main()
{
    int b[] = { 10, 20, 30, 40 };
    int i;

    printf("\nArray b printed by subindex of arrays\n");
    for ( i = 0; i < 4; i++ )
        printf( "%d = %d\n", i, b[i]);
}