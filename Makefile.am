SUBDIRS = include

AM_CFLAGS = \
	-std=c99 \
	-Wall \
	-Wextra \
	-Wno-gnu-variable-sized-type-not-at-end \
	-I$(top_srcdir)/include

lib_LIBRARIES = libkernaux.a

TESTS = \
	tests/test_stdlib

noinst_PROGRAMS = $(TESTS)

libkernaux_a_SOURCES = \
	src/stdlib.c

if ARCH_X86
libkernaux_a_SOURCES += src/arch/x86.S
endif

if ENABLE_CMDLINE
libkernaux_a_SOURCES += src/cmdline.c
TESTS += \
	examples/cmdline \
	tests/test_cmdline
endif

if ENABLE_CONSOLE
libkernaux_a_SOURCES += src/console.c
endif

if ENABLE_MULTIBOOT2
libkernaux_a_SOURCES += \
	src/multiboot2/helpers.c \
	src/multiboot2/is_valid.c \
	src/multiboot2/print.c
TESTS += \
	tests/test_multiboot2_helpers \
	tests/test_multiboot2_print \
	tests/test_multiboot2_validation
noinst_PROGRAMS += \
	tests/multiboot2_print1 \
	tests/multiboot2_print2
endif

if ENABLE_PFA
libkernaux_a_SOURCES += src/pfa.c
TESTS += tests/test_pfa
endif

examples_cmdline_SOURCES = \
	$(libkernaux_a_SOURCES) \
	examples/cmdline.c

tests_multiboot2_print1_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/multiboot2_print1.c

tests_multiboot2_print2_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/multiboot2_print2.c

tests_test_cmdline_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_cmdline.c

tests_test_multiboot2_helpers_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_multiboot2_helpers.c

tests_test_multiboot2_print_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_multiboot2_print.c

tests_test_multiboot2_validation_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_multiboot2_validation.c

tests_test_pfa_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_pfa.c

tests_test_stdlib_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_stdlib.c
