#include <stdio.h>
#include "arp.h"
#include "ip.h"

int main(){
	printf("\nHola");
	arpLeerCache();
	ipInicializar();

	printf("\n");
	return 0;
}