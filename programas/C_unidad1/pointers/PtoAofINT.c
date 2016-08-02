#include <stdio.h>

void main()
{
    int b[] = { 10, 20, 30, 40 };
    int *ptrB = b;
    int i;
    int offset;

    printf("\nArray b printed by subindex of arrays\n");
    for ( i = 0; i < 4; i++ )
        printf( "%d = %d\n", i, b[i]);

    printf("\nArray b printed by offset\n");
    for ( offset = 0; offset < 4; offset++)
        printf( "%d = %d\n", offset, *( b + offset));

    printf("\nPointer ptrB printed by subindex of arrays\n");
    for ( i = 0; i < 4; i++ )
        printf( "%d = %d\n", i, ptrB[ i ] );
 
    printf("\nPointer ptrB printed by offset\n");
    for ( offset = 0; offset < 4; offset++ )
        printf( "%d = %d\n", offset, *( ptrB + offset));
}