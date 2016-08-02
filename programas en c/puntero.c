#include <stdio.h>

void func (int *punt)
{
punt[0]=1;
punt[1]=2;

}

int main()
{
   int b[] = { 10, 20, 30, 40 };
   int *ptrB = b;    
   int i; 
   int desplazamiento;          
   printf("\n\n");
   printf( "Arreglo b impreso por subindices de arreglos\n" );
 
   for ( i = 0; i < 4; i++ )
   {
      printf( "%d = %d\n", i, b[i]);
   }
   printf("\n\n");
 
   printf( "Arreglo por desplazamiento\n" );
 
   for ( desplazamiento = 0; desplazamiento < 4; desplazamiento++)
   {
      printf( "%d = %d\n", desplazamiento, *( b + desplazamiento));  
   } 
   printf("\n\n");

   printf( "Notacion de subindices de arreglos\n" );
 
   for ( i = 0; i < 4; i++ )
   {
      printf( "%d = %d\n", i, ptrB[ i ] );
   }
   printf("\n\n");
 
   printf( "Apuntador desplazamienton\n" );
  func(b);
   for ( desplazamiento = 0; desplazamiento < 4; desplazamiento++ )
   {
      printf( "%d = %d\n", desplazamiento, *( ptrB + desplazamiento));   
   }
   
   return 0;
 
}







