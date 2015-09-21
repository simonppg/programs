#include <stdio.h>
#include <stdlib.h>

#include "mycoolapi.h"

int main(void)
{
	struct MyCoolApi *api;

	if((api = my_cool_api_initialize()) != NULL)
	{
		int sum = api->add(3, 39);
		printf("The cool API considers 3 + 39 to be %d\n", sum);
		int sub = api->sub(3, 39);
		printf("The cool API considers 3 - 39 to be %d\n", sub);
	}
	return 0;
}