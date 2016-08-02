#include <stdio.h>
#define MACRO(intno) (1U << intno)
#define TIMER_FIQ0	23

int main(int argc, char const *argv[])
{
	printf("FIQ %32x\n",TIMER_FIQ0);
	printf("Despues %32x\n",MACRO(TIMER_FIQ0));
	return 0;
}