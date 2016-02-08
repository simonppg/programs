ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libbowling.la
libbowling_la_SOURCES = src/bowling_game.c src/bowling_game.h

check_PROGRAMS = test/game
TESTS = test/game

test_game_CFLAGS =  -I$(top_srcdir)/src
test_game_LDFLAGS = -lbowling

maintainer-clean-local:
	rm -rf aclocal.m4 configure Makefile.in autotools m4
