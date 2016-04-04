ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libfifo.la
libfifo_la_SOURCES = src/fifo.c

check_PROGRAMS = check_fifo
TESTS = check_fifo
check_fifo_SOURCES = test/fifo.c
check_fifo_CFLAGS = -I$(top_srcdir)/src
check_fifo_LDFLAGS = -lfifo -lcmocka

maintainer-clean-local:
	rm -rf aclocal.m4 configure Makefile.in autotools m4
