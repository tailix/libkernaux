SUBDIRS = include

AM_CFLAGS = \
	-std=c99 \
	-pedantic \
	-Wall \
	-Wextra \
	-I$(top_srcdir)/include

lib_LIBRARIES = libkernaux.a

TESTS = \
	examples/assert_guards \
	examples/assert_simple \
	examples/printf \
	examples/printf_va \
	tests/test_itoa \
	tests/test_printf

noinst_PROGRAMS = $(TESTS)

libkernaux_a_SOURCES = \
	src/assert.c \
	src/itoa.c \
	src/libc.c \
	src/printf.c

if ASM_I386
libkernaux_a_SOURCES += src/asm/i386.S
endif

if ASM_X86_64
libkernaux_a_SOURCES += src/asm/x86_64.S
endif

if WITH_CMDLINE
libkernaux_a_SOURCES += src/cmdline.c
TESTS += \
	examples/cmdline \
	tests/test_cmdline
endif

if WITH_CONSOLE
libkernaux_a_SOURCES += src/console.c
endif

if WITH_ELF
libkernaux_a_SOURCES += src/elf.c
TESTS += tests/test_elf
endif

if WITH_FRAMEBUFFER
libkernaux_a_SOURCES += src/framebuffer.c
endif

if WITH_MULTIBOOT2
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

if WITH_PFA
libkernaux_a_SOURCES += src/pfa.c
TESTS += \
	examples/pfa \
	tests/test_pfa \
	tests/test_pfa_assert
endif

if WITH_UNITS
libkernaux_a_SOURCES += src/units.c
TESTS += \
	examples/units_human \
	tests/test_units_human
endif

examples_assert_guards_SOURCES = \
	$(libkernaux_a_SOURCES) \
	examples/assert_guards.c

examples_assert_simple_SOURCES = \
	$(libkernaux_a_SOURCES) \
	examples/assert_simple.c

examples_cmdline_SOURCES = \
	$(libkernaux_a_SOURCES) \
	examples/cmdline.c

examples_pfa_SOURCES = \
	$(libkernaux_a_SOURCES) \
	examples/pfa.c

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
	tests/multiboot2_print1.c \
	tests/multiboot2_example1.h

tests_multiboot2_print2_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/multiboot2_print2.c \
	tests/multiboot2_example2.h

tests_test_cmdline_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_cmdline.c

tests_test_elf_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_elf.c

tests_test_itoa_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_itoa.c

tests_test_multiboot2_helpers_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_multiboot2_helpers.c \
	tests/multiboot2_example1.h \
	tests/multiboot2_example2.h

tests_test_multiboot2_print_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_multiboot2_print.c

tests_test_multiboot2_validation_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_multiboot2_validation.c \
	tests/multiboot2_example1.h \
	tests/multiboot2_example2.h

tests_test_pfa_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_pfa.c

tests_test_pfa_assert_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_pfa_assert.c

tests_test_printf_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_printf.c

tests_test_units_human_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_units_human.c
