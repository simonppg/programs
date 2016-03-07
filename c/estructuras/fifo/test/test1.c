#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "fifo.h"

void create_fifo()
{
	Fifo *fifo;
	fifo = fifo_create();
	assert_non_null(fifo);
	fifo_destroy(fifo);
}

