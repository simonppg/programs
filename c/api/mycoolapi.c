#include "mycoolapi.h"

/* Note: This does **not** pollute the global namespace,
 * since the function is static.
*/
static int add(int x, int y)
{
	return x + y;
}

static int sub(int x, int y)
{
	return x - y;
}

struct MyCoolApi * my_cool_api_initialize(void)
{
	/* Since we don't need to do anything at initialize,
	 * just keep a const struct ready and return it.
	*/
	static const struct MyCoolApi the_api = {
		add,
		sub
	};

	return (struct MyCoolApi *) &the_api;
}