#include <stdio.h>
#include <stdlib.h>

char *Vector="hola";
char **Array;

void vector(char **cadena)
{
  *cadena="adios";
}

void array(char cadena[3][3])
{
  /*cadena[0]="adios";
  cadena[1]="esta";*/
}

void array2 ( int arc, char **argv )
{
  printf("\nArray 2");
  //printf("\n%s",argv[0]);
  int i;
  char *full;
  srand (time (NULL));
  for( i = 0; i < arc; i++){
    asprintf(&full,"Muestas = %d", (rand() % 11));
    argv[i]=full;
  }
}

 
int main()
{
  printf("(main) valor --> %s\n",Vector);

  vector(&Vector);

  printf("(main) valor --> %s\n",Vector);


  int cantidadDeMuestras=3;

  char **Muestras = malloc(cantidadDeMuestras);
  int i;
  for( i = 0; i < cantidadDeMuestras; i++){
    Muestras[i] = malloc(1024 * sizeof(char));
    Muestras[i][0] = '\0';
  }

  for( i = 0; i < cantidadDeMuestras; i++){
   Muestras[i]="hola";
  }

  printf("Array\n");

  printf("(main) valor -->\n");

  for( i = 0; i < cantidadDeMuestras; i++){
    printf("%s\n", Muestras[i] );
  }


  array2(3,Muestras);

  printf("(main) valor -->\n");

  for( i = 0; i < cantidadDeMuestras; i++){
    printf("%s\n", Muestras[i] );
  }

 return 0;   
}

