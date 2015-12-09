#include <stdio.h>

#include "arp.h"
#include "ip.h"

// Definición de variables globales...
int  arpGlobal;

// Definición y declaración de variables locales...
static  int  arpLocal;

// Declaración de funciones locales...
static  int  arpSResetCache( void );

// Definición de funciones globales...
int arpLeerCache()
{
	printf("\narpLeerCache");
}

// Definición de funciones locales...
static  int  arpSResetCache( void )
{
	printf("\narpSResetCache");

}