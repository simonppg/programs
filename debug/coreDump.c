#include <stdio.h>
int main()
{
int *null_p = NULL;
*null_p = 10; //write to null pointer memory area,Segmentation fault will happen
return 0;
}