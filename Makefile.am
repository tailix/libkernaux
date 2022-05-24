SUBDIRS = include

AM_CFLAGS = \
	-std=c99 \
	-pedantic \
	-Wall \
	-Wextra \
	-I$(top_builddir)/include \
	-I$(top_srcdir)/include

lib_LIBRARIES = libkernaux.a

noinst_PROGRAMS = $(TESTS)

libkernaux_a_SOURCES = \
	src/assert.c \
	src/libc.c

CLEANFILES = \
	tests/test_printf_gen.c

if ASM_I386
libkernaux_a_SOURCES += src/asm/i386.S
endif

if ASM_RISCV64
libkernaux_a_SOURCES += src/asm/riscv64.S
endif

if ASM_X86_64
libkernaux_a_SOURCES += src/asm/x86_64.S
endif

if ENABLE_TESTS
TESTS = \
	examples/assert_guards \
	examples/assert_simple \
	examples/panic_guards \
	examples/panic_simple
endif

if ENABLE_PIC
AM_CFLAGS += -fpic
else
AM_CFLAGS += -fno-pic
endif

if ENABLE_WERROR
AM_CFLAGS += -Werror
endif

if WITH_CMDLINE
libkernaux_a_SOURCES += src/cmdline.c
if ENABLE_TESTS
TESTS += \
	examples/cmdline \
	tests/test_cmdline
endif
endif

if WITH_CONSOLE
libkernaux_a_SOURCES += src/console.c
endif

if WITH_ELF
libkernaux_a_SOURCES += src/elf.c
if ENABLE_TESTS
TESTS += tests/test_elf
endif
endif

if WITH_FRAMEBUFFER
libkernaux_a_SOURCES += src/framebuffer.c
endif

if WITH_MBR
libkernaux_a_SOURCES += src/mbr.c
if ENABLE_TESTS
TESTS += tests/test_mbr
endif
endif

if WITH_MULTIBOOT2
libkernaux_a_SOURCES += \
	src/multiboot2/enums_to_str.c \
	src/multiboot2/header_helpers.c \
	src/multiboot2/header_is_valid.c \
	src/multiboot2/header_print.c \
	src/multiboot2/info_helpers.c \
	src/multiboot2/info_is_valid.c \
	src/multiboot2/info_print.c
if ENABLE_TESTS
TESTS += \
	tests/test_multiboot2_header_helpers \
	tests/test_multiboot2_header_print \
	tests/test_multiboot2_header_validation \
	tests/test_multiboot2_info_helpers \
	tests/test_multiboot2_info_print \
	tests/test_multiboot2_info_validation
noinst_PROGRAMS += \
	tests/multiboot2_header_print1 \
	tests/multiboot2_header_print2 \
	tests/multiboot2_info_print1 \
	tests/multiboot2_info_print2
endif
endif

if WITH_NTOA
libkernaux_a_SOURCES += src/ntoa.c
if ENABLE_TESTS
TESTS += tests/test_ntoa
endif
endif

if WITH_PFA
libkernaux_a_SOURCES += src/pfa.c
if ENABLE_TESTS
TESTS += \
	examples/pfa \
	tests/test_pfa \
	tests/test_pfa_assert
endif
endif

if WITH_PRINTF
libkernaux_a_SOURCES += src/printf.c
if ENABLE_TESTS
TESTS += \
	examples/printf \
	examples/printf_va \
	examples/snprintf \
	examples/snprintf_va
if ENABLE_TESTS_PYTHON
TESTS += tests/test_printf_gen
noinst_SCRIPTS = tests/printf_gen.py
noinst_DATA = \
	tests/printf.yml \
	tests/printf_orig.yml
endif
endif
endif

if WITH_UNITS
libkernaux_a_SOURCES += src/units.c
if ENABLE_TESTS
TESTS += \
	examples/units_human \
	tests/test_units_human
endif
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

examples_panic_guards_SOURCES = \
	$(libkernaux_a_SOURCES) \
	examples/panic_guards.c

examples_panic_simple_SOURCES = \
	$(libkernaux_a_SOURCES) \
	examples/panic_simple.c

examples_pfa_SOURCES = \
	$(libkernaux_a_SOURCES) \
	examples/pfa.c

examples_printf_SOURCES = \
	$(libkernaux_a_SOURCES) \
	examples/printf.c

examples_printf_va_SOURCES = \
	$(libkernaux_a_SOURCES) \
	examples/printf_va.c

examples_snprintf_SOURCES = \
	$(libkernaux_a_SOURCES) \
	examples/snprintf.c

examples_snprintf_va_SOURCES = \
	$(libkernaux_a_SOURCES) \
	examples/snprintf_va.c

examples_units_human_SOURCES = \
	$(libkernaux_a_SOURCES) \
	examples/units_human.c

tests_multiboot2_header_print1_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/multiboot2_header_print1.c \
	tests/multiboot2_header_example1.h

tests_multiboot2_header_print2_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/multiboot2_header_print2.c \
	tests/multiboot2_header_example2.h

tests_multiboot2_info_print1_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/multiboot2_info_print1.c \
	tests/multiboot2_info_example1.h

tests_multiboot2_info_print2_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/multiboot2_info_print2.c \
	tests/multiboot2_info_example2.h

tests_test_cmdline_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_cmdline.c

tests_test_elf_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_elf.c

tests_test_mbr_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_mbr.c

tests_test_multiboot2_header_helpers_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_multiboot2_header_helpers.c \
	tests/multiboot2_header_example1.h \
	tests/multiboot2_header_example2.h

tests_test_multiboot2_header_print_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_multiboot2_header_print.c

tests_test_multiboot2_header_validation_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_multiboot2_header_validation.c \
	tests/multiboot2_header_example1.h \
	tests/multiboot2_header_example2.h

tests_test_multiboot2_info_helpers_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_multiboot2_info_helpers.c \
	tests/multiboot2_info_example1.h \
	tests/multiboot2_info_example2.h

tests_test_multiboot2_info_print_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_multiboot2_info_print.c

tests_test_multiboot2_info_validation_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_multiboot2_info_validation.c \
	tests/multiboot2_info_example1.h \
	tests/multiboot2_info_example2.h

tests_test_ntoa_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_ntoa.c

tests_test_pfa_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_pfa.c

tests_test_pfa_assert_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_pfa_assert.c

tests_test_printf_gen_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_printf_gen.c

tests_test_units_human_SOURCES = \
	$(libkernaux_a_SOURCES) \
	tests/test_units_human.c

tests/test_printf_gen.c: tests/printf_gen.py tests/printf.yml tests/printf_orig.yml
	python3 tests/printf_gen.py
