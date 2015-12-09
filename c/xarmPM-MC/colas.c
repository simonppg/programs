/*
  Name: Colas
  Copyright: casicodigo.blogspot.com
  Author: Jose Martin Cruz Otiniano
  Date: 27/10/12 12:27
  Description: Encola elemento, Desesencola elemento, Mostrar cola, Vaciar cola
*/
 
#include <stdio.h>
#include <stdlib.h>
 
 
/*                Estructura de los nodos de la cola      
-----------------------------------------------------------------*/
struct nodo
{
    int nro;
    struct nodo *sgte;
};
 
 
/*                      Estructura de la cola      
-----------------------------------------------------------------*/
struct cola
{
    struct nodo *delante;
    struct nodo *atras  ;
};
 
 
/*                        Encolar elemento      
------------------------------------------------------------------*/
void encolar( struct cola q, int valor )
{
     struct nodo *aux;// = new(struct nodo);
     
     aux->nro = valor;
     aux->sgte = NULL;
     
     if( q.delante == NULL)
         q.delante = aux;   // encola el primero elemento
     else
         (q.atras)->sgte = aux;
         
     q.atras = aux;        // puntero que siempre apunta al ultimo elemento
     
}
 
/*                        Desencolar elemento      
------------------------------------------------------------------*/
int desencolar( struct cola q )
{
     int num ;
     struct nodo *aux ;
     
     aux = q.delante;      // aux apunta al inicio de la cola
     num = aux->nro;
     q.delante = (q.delante)->sgte;
     //delete(aux);          // libera memoria a donde apuntaba aux
     
     return num;
}
 
/*                        Mostrar Cola      
-------------------------------------------------------------------*/
void muestraCola( struct cola q )
{
     struct nodo *aux;
     
     aux = q.delante;
         
     while( aux != NULL )
     {
            printf("   %d",aux->nro) ;
            aux = aux->sgte;
     }    
}
 
/*              Eliminar todos los elementos de la Cola      
-------------------------------------------------------------------*/
void vaciaCola( struct cola q)
{
     struct nodo *aux;
     
     while( q.delante != NULL)
     {
            aux = q.delante;
            q.delante = aux->sgte;
            //delete(aux);
     }
     q.delante = NULL;
     q.atras   = NULL;
     
}
 
/*                        Menu de opciones    
--------------------------------------------------------------------*/
void menu()
{
    printf("\n\t IMPLEMENTACION DE COLAS EN C++\n\n");
    printf("\n1. ENCOLAR                               ");
    printf("\n2. DESENCOLAR                            ");
    printf("\n3. MOSTRAR COLA                          ");
    printf("\n4. VACIAR COLA                           ");
    printf("\n5. SALIR                                 ");
 
    printf("\n\nINGRESE OPCION: ");
}
 
/*                        Funcion Principal        
--------------------------------------------------------------------*/
int main()
{
    struct cola q;
   
    q.delante = NULL;
    q.atras   = NULL;
   
   
    int dato;  // numero a encolar
    int op;    // opcion del menu
    int x ;    // numero que devuelve la funcon pop
   
    system("color 0b");
 
    do
    {
        menu();  scanf("%d",&op);
 
        switch(op)
        {
            case 1:
 
                 printf( "\n NUMERO A ENCOLAR: "); scanf("%d",&dato);
                 encolar( q, dato );
                 printf("\n\n\t\tNumero %d encolado...\n\n",dato);
            break;
 
 
            case 2:
 
                 x = desencolar( q );
                 printf("\n\n\t\tNumero %d desencolado...\n\n",x);
            break;
                 
 
            case 3:
 
                 printf("\n\n MOSTRANDO COLA\n\n");
                 if(q.delante!=NULL) muestraCola( q );
                 else   printf("\n\n\tCola vacia...!\n");
            break;
 
 
            case 4:
 
                 vaciaCola( q );
                 printf("\n\n\t\tHecho...\n\n");
            break;
           
         }
 
        printf("\n\n");
        system("pause");  system("clear");
 
    }while(op!=5);
   
   
    return 0;
}