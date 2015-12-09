#include <stdio.h>
/* number of times through the loop */
extern int counter;
/* routine to increment the counter */
extern void inc_counter(void);

main()
{
	int	index; /* loop index */
	for (index = 0; index < 10; index++)
		inc_counter();
	printf("Counter is %d\n", counter);
	return (0);
}