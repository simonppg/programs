#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"

void create_node()
{
	Node *node;
	node = node_create();
	assert_non_null(node);
	node_destroy(node);
}

/*
 * pruba inserción de nodos
 */
void insert_node_test()
{
	Node *node;
	node = node_create();
	assert_non_null(node);
	assert_non_null(node->name);
}

int main()
{
	const UnitTest tests[] = {
		unit_test(create_node),
		unit_test(insert_node_test),
	};

	return run_tests(tests);
}
