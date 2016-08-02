#include <stdio.h>
#include <stdlib.h>
#include<iostream>

int main ()
{
  int i;
  char cad[256];
  printf ("Enter a number: ");
  std::cin>>cad;
  i = atoi (cad);
  printf ("The value entered is %d. The double is %d.\n",i,i*2);
  return 0;
}
