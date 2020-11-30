SUBDIRS = include

AM_CFLAGS = -std=c99 -Wall -Wextra -I$(top_srcdir)/include

lib_LIBRARIES = libkernaux.a

TESTS = \
	tests/test_multiboot2_helpers \
	tests/test_multiboot2_print \
	tests/test_multiboot2_validation \
	tests/test_stdlib

noinst_PROGRAMS = \
	$(TESTS) \
	tests/multiboot2_print1 \
	tests/multiboot2_print2

libkernaux_a_SOURCES = \
	src/console.c \
	src/multiboot2/helpers.c \
	src/multiboot2/is_valid.c \
	src/multiboot2/print.c \
	src/pfa.c \
	src/stdlib.c

if ARCH_X86
libkernaux_a_SOURCES += src/arch/x86.S
endif

tests_multiboot2_print1_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/multiboot2_print1.c

tests_multiboot2_print2_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/multiboot2_print2.c

tests_test_multiboot2_helpers_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_multiboot2_helpers.c

tests_test_multiboot2_print_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_multiboot2_print.c

tests_test_multiboot2_validation_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_multiboot2_validation.c

tests_test_stdlib_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_stdlib.c
