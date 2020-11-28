SUBDIRS = include

AM_CFLAGS = -std=c99 -I$(top_srcdir)/include

lib_LIBRARIES = libkernaux.a

TESTS = \
	tests/test_multiboot2_validation

noinst_PROGRAMS = $(TESTS)

libkernaux_a_SOURCES = \
	src/arch/i386.S \
	src/multiboot2/is_valid.c \
	src/multiboot2/print.c \
	src/pfa.c

tests_test_multiboot2_validation_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_multiboot2_validation.c
