SUBDIRS = include

AM_CFLAGS = -std=c99 -I$(top_srcdir)/include

lib_LIBRARIES = libkernaux.a

TESTS = \
	tests/test_hang_segfault

noinst_PROGRAMS = \
	$(TESTS) \
	tests/hang

libkernaux_a_SOURCES = \
	src/arch/i386.S \
	src/pfa.c

tests_hang_SOURCES = $(libkernaux_a_SOURCES) tests/hang.c

tests_test_hang_segfault_SOURCES = tests/test_hang_segfault.c
