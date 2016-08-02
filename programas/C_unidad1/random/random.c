#include <stdlib.h>
#include <stdio.h>

int main()
{
    int i;
    srand (time (NULL));
    for(i=0; i<5; i++)
    {
    	//number from 10 to 100
        printf("%d\n", (rand() % 91)+10);
    }
    return 0;
}