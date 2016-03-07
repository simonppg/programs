#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "test1.h"

int main()
{
	const UnitTest tests[] = {
		unit_test(create_fifo),
	};

	return run_tests(tests);
}
