SUBDIRS = include

AM_CFLAGS = -std=c99 -Wall -Wextra -I$(top_srcdir)/include

lib_LIBRARIES = libkernaux.a

TESTS = \
	tests/test_multiboot2_print \
	tests/test_multiboot2_validation

noinst_PROGRAMS = \
	$(TESTS) \
	tests/multiboot2_print

libkernaux_a_SOURCES = \
	src/arch/i386.S \
	src/multiboot2/is_valid.c \
	src/multiboot2/print.c \
	src/pfa.c

tests_multiboot2_print_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/multiboot2_print.c

tests_test_multiboot2_print_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_multiboot2_print.c

tests_test_multiboot2_validation_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_multiboot2_validation.c
