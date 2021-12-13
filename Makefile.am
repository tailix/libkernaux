SUBDIRS = include

AM_CFLAGS = \
	-std=c99 \
	-pedantic \
	-Wall \
	-Wextra \
	-Wno-gnu-variable-sized-type-not-at-end \
	-I$(top_srcdir)/include

lib_LIBRARIES = libkernaux.a

TESTS = \
	examples/printf \
	examples/printf_va \
	tests/test_printf \
	tests/test_stdlib

noinst_PROGRAMS = $(TESTS)

libkernaux_a_SOURCES = \
	src/printf.c \
	src/stdlib.c

if ARCH_I386
libkernaux_a_SOURCES += src/arch/i386.S
endif

if ARCH_X86_64
libkernaux_a_SOURCES += src/arch/x86_64.S
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

if ENABLE_ELF
libkernaux_a_SOURCES += src/elf.c
TESTS += tests/test_elf
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

if ENABLE_UNITS
libkernaux_a_SOURCES += src/units.c
TESTS += \
	examples/units_human \
	tests/test_units_human
endif

examples_cmdline_SOURCES = \
	$(libkernaux_a_SOURCES) \
	examples/cmdline.c

examples_printf_SOURCES = \
	$(libkernaux_a_SOURCES) \
	examples/printf.c

examples_printf_va_SOURCES = \
	$(libkernaux_a_SOURCES) \
	examples/printf_va.c

examples_units_human_SOURCES = \
	$(libkernaux_a_SOURCES) \
	examples/units_human.c

tests_multiboot2_print1_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/multiboot2_print1.c

tests_multiboot2_print2_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/multiboot2_print2.c

tests_test_cmdline_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_cmdline.c

tests_test_elf_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_elf.c

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

tests_test_printf_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_printf.c

tests_test_stdlib_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_stdlib.c

tests_test_units_human_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_units_human.c
