##########
# Common #
##########

SUBDIRS = include libc

CLEANFILES =
TESTS =

AM_CFLAGS = \
	-std=c99 \
	-pedantic \
	-Wall \
	-Wextra \
	-I$(top_builddir)/include \
	-I$(top_srcdir)/include \
	-D_POSIX_C_SOURCE=200809L

if WITH_LIBC
AM_CFLAGS += \
	-I$(top_builddir)/libc \
	-I$(top_srcdir)/libc
endif

if ENABLE_WERROR
AM_CFLAGS += -Werror
endif

# TODO: DRY (configure.ac)
if ENABLE_FREESTANDING
AM_CFLAGS += -nostdlib -ffreestanding -fno-pic -fno-stack-protector
else
AM_CFLAGS += -fpic
endif

#######
# all #
#######

lib_LIBRARIES = libkernaux.a
noinst_PROGRAMS = $(TESTS)

################
# libkernaux.a #
################

libkernaux_a_SOURCES = src/libc.h src/assert.c
if ASM_I386
libkernaux_a_SOURCES += src/asm/i386.S
endif
if ASM_RISCV64
libkernaux_a_SOURCES += src/asm/riscv64.S
endif
if ASM_X86_64
libkernaux_a_SOURCES += src/asm/x86_64.S
endif
if WITH_CMDLINE
libkernaux_a_SOURCES += src/cmdline.c
endif
if WITH_CONSOLE
libkernaux_a_SOURCES += src/console.c
endif
if WITH_ELF
libkernaux_a_SOURCES += src/elf.c
endif
if WITH_FILE
libkernaux_a_SOURCES += src/file.c
endif
if WITH_FRAMEBUFFER
libkernaux_a_SOURCES += src/framebuffer.c
endif
if WITH_LIBC
libkernaux_a_SOURCES += src/libc.c
endif
if WITH_MBR
libkernaux_a_SOURCES += src/mbr.c
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
endif
if WITH_NTOA
libkernaux_a_SOURCES += src/ntoa.c
endif
if WITH_PFA
libkernaux_a_SOURCES += src/pfa.c
endif
if WITH_PRINTF
libkernaux_a_SOURCES += src/printf.c
endif
if WITH_PRINTF_FMT
libkernaux_a_SOURCES += src/printf_fmt.c
endif
if WITH_UNITS
libkernaux_a_SOURCES += src/units.c
endif

##########################
# examples/assert_guards #
##########################

if ENABLE_TESTS
TESTS += examples/assert_guards
examples_assert_guards_LDADD = libkernaux.a
examples_assert_guards_SOURCES = examples/assert_guards.c
endif

##########################
# examples/assert_simple #
##########################

if ENABLE_TESTS
TESTS += examples/assert_simple
examples_assert_simple_LDADD = libkernaux.a
examples_assert_simple_SOURCES = examples/assert_simple.c
endif

####################
# examples/cmdline #
####################

if ENABLE_TESTS
if WITH_CMDLINE
TESTS += examples/cmdline
examples_cmdline_LDADD = libkernaux.a
examples_cmdline_SOURCES = examples/cmdline.c
endif
endif

####################
# examples/fprintf #
####################

if ENABLE_TESTS
if WITH_PRINTF
if WITH_FILE
TESTS += examples/fprintf
examples_fprintf_LDADD = libkernaux.a
examples_fprintf_SOURCES = examples/fprintf.c
endif
endif
endif

#######################
# examples/fprintf_va #
#######################

if ENABLE_TESTS
if WITH_PRINTF
if WITH_FILE
TESTS += examples/fprintf_va
examples_fprintf_va_LDADD = libkernaux.a
examples_fprintf_va_SOURCES = examples/fprintf_va.c
endif
endif
endif

#################
# examples/ntoa #
#################

if ENABLE_TESTS
if WITH_NTOA
TESTS += examples/ntoa
examples_ntoa_LDADD = libkernaux.a
examples_ntoa_SOURCES = examples/ntoa.c
endif
endif

#########################
# examples/panic_guards #
#########################

if ENABLE_TESTS
TESTS += examples/panic_guards
examples_panic_guards_LDADD = libkernaux.a
examples_panic_guards_SOURCES = examples/panic_guards.c
endif

#########################
# examples/panic_simple #
#########################

if ENABLE_TESTS
TESTS += examples/panic_simple
examples_panic_simple_LDADD = libkernaux.a
examples_panic_simple_SOURCES = examples/panic_simple.c
endif

################
# examples/pfa #
################

if ENABLE_TESTS
if WITH_PFA
TESTS += examples/pfa
examples_pfa_LDADD = libkernaux.a
examples_pfa_SOURCES = examples/pfa.c
endif
endif

#######################
# examples/printf_fmt #
#######################

if ENABLE_TESTS
if WITH_PRINTF_FMT
TESTS += examples/printf_fmt
examples_printf_fmt_LDADD = libkernaux.a
examples_printf_fmt_SOURCES = examples/printf_fmt.c
endif
endif

#####################
# examples/snprintf #
#####################

if ENABLE_TESTS
if WITH_PRINTF
TESTS += examples/snprintf
examples_snprintf_LDADD = libkernaux.a
examples_snprintf_SOURCES = examples/snprintf.c
endif
endif

########################
# examples/snprintf_va #
########################

if ENABLE_TESTS
if WITH_PRINTF
TESTS += examples/snprintf_va
examples_snprintf_va_LDADD = libkernaux.a
examples_snprintf_va_SOURCES = examples/snprintf_va.c
endif
endif

########################
# examples/units_human #
########################

if ENABLE_TESTS
if WITH_UNITS
TESTS += examples/units_human
examples_units_human_LDADD = libkernaux.a
examples_units_human_SOURCES = examples/units_human.c
endif
endif

##################################
# tests/multiboot2_header_print1 #
##################################

if ENABLE_TESTS
if WITH_MULTIBOOT2
noinst_PROGRAMS += tests/multiboot2_header_print1
tests_multiboot2_header_print1_LDADD = libkernaux.a
tests_multiboot2_header_print1_SOURCES = \
	tests/multiboot2_header_print1.c \
	tests/multiboot2_header_example1.h
endif
endif

##################################
# tests/multiboot2_header_print2 #
##################################

if ENABLE_TESTS
if WITH_MULTIBOOT2
noinst_PROGRAMS += tests/multiboot2_header_print2
tests_multiboot2_header_print2_LDADD = libkernaux.a
tests_multiboot2_header_print2_SOURCES = \
	tests/multiboot2_header_print2.c \
	tests/multiboot2_header_example2.h
endif
endif

################################
# tests/multiboot2_info_print1 #
################################

if ENABLE_TESTS
if WITH_MULTIBOOT2
noinst_PROGRAMS += tests/multiboot2_info_print1
tests_multiboot2_info_print1_LDADD = libkernaux.a
tests_multiboot2_info_print1_SOURCES = \
	tests/multiboot2_info_print1.c \
	tests/multiboot2_info_example1.h
endif
endif

################################
# tests/multiboot2_info_print2 #
################################

if ENABLE_TESTS
if WITH_MULTIBOOT2
noinst_PROGRAMS += tests/multiboot2_info_print2
tests_multiboot2_info_print2_LDADD = libkernaux.a
tests_multiboot2_info_print2_SOURCES = \
	tests/multiboot2_info_print2.c \
	tests/multiboot2_info_example2.h
endif
endif

######################
# tests/test_cmdline #
######################

if ENABLE_TESTS
if WITH_CMDLINE
TESTS += tests/test_cmdline
tests_test_cmdline_LDADD = libkernaux.a
tests_test_cmdline_SOURCES = tests/test_cmdline.c
endif
endif

##########################
# tests/test_cmdline_gen #
##########################

if ENABLE_TESTS_PYTHON
if WITH_CMDLINE
TESTS += tests/test_cmdline_gen
tests_test_cmdline_gen_LDADD = libkernaux.a
tests_test_cmdline_gen_SOURCES = \
	tests/test_cmdline_gen.c \
	tests/cmdline_gen.py \
	tests/cmdline_gen.jinja \
	common/cmdline.yml
endif
endif

CLEANFILES += tests/test_cmdline_gen.c

tests/test_cmdline_gen.c: tests/cmdline_gen.py tests/cmdline_gen.jinja common/cmdline.yml
	python3 tests/cmdline_gen.py

##################
# tests/test_elf #
##################

if ENABLE_TESTS
if WITH_ELF
TESTS += tests/test_elf
tests_test_elf_LDADD = libkernaux.a
tests_test_elf_SOURCES = tests/test_elf.c
endif
endif

##################
# tests/test_mbr #
##################

if ENABLE_TESTS
if WITH_MBR
TESTS += tests/test_mbr
tests_test_mbr_LDADD = libkernaux.a
tests_test_mbr_SOURCES = tests/test_mbr.c
endif
endif

########################################
# tests/test_multiboot2_header_helpers #
########################################

if ENABLE_TESTS
if WITH_MULTIBOOT2
TESTS += tests/test_multiboot2_header_helpers
tests_test_multiboot2_header_helpers_LDADD = libkernaux.a
tests_test_multiboot2_header_helpers_SOURCES = \
	tests/test_multiboot2_header_helpers.c \
	tests/multiboot2_header_example1.h \
	tests/multiboot2_header_example2.h
endif
endif

######################################
# tests/test_multiboot2_header_print #
######################################

if ENABLE_TESTS
if WITH_MULTIBOOT2
TESTS += tests/test_multiboot2_header_print
tests_test_multiboot2_header_print_DEPENDENCIES = \
	tests/multiboot2_header_print1 \
	tests/multiboot2_header_print2
tests_test_multiboot2_header_print_LDADD = libkernaux.a
tests_test_multiboot2_header_print_SOURCES = \
	tests/test_multiboot2_header_print.c
endif
endif

###########################################
# tests/test_multiboot2_header_validation #
###########################################

if ENABLE_TESTS
if WITH_MULTIBOOT2
TESTS += tests/test_multiboot2_header_validation
tests_test_multiboot2_header_validation_LDADD = libkernaux.a
tests_test_multiboot2_header_validation_SOURCES = \
	tests/test_multiboot2_header_validation.c \
	tests/multiboot2_header_example1.h \
	tests/multiboot2_header_example2.h
endif
endif

######################################
# tests/test_multiboot2_info_helpers #
######################################

if ENABLE_TESTS
if WITH_MULTIBOOT2
TESTS += tests/test_multiboot2_info_helpers
tests_test_multiboot2_info_helpers_LDADD = libkernaux.a
tests_test_multiboot2_info_helpers_SOURCES = \
	tests/test_multiboot2_info_helpers.c \
	tests/multiboot2_info_example1.h \
	tests/multiboot2_info_example2.h
endif
endif

####################################
# tests/test_multiboot2_info_print #
####################################

if ENABLE_TESTS
if WITH_MULTIBOOT2
TESTS += tests/test_multiboot2_info_print
tests_test_multiboot2_info_print_DEPENDENCIES = \
	tests/multiboot2_info_print1 \
	tests/multiboot2_info_print2
tests_test_multiboot2_info_print_LDADD = libkernaux.a
tests_test_multiboot2_info_print_SOURCES = \
	tests/test_multiboot2_info_print.c
endif
endif

#########################################
# tests/test_multiboot2_info_validation #
#########################################

if ENABLE_TESTS
if WITH_MULTIBOOT2
TESTS += tests/test_multiboot2_info_validation
tests_test_multiboot2_info_validation_LDADD = libkernaux.a
tests_test_multiboot2_info_validation_SOURCES = \
	tests/test_multiboot2_info_validation.c \
	tests/multiboot2_info_example1.h \
	tests/multiboot2_info_example2.h
endif
endif

###################
# tests/test_ntoa #
###################

if ENABLE_TESTS
if WITH_NTOA
TESTS += tests/test_ntoa
tests_test_ntoa_LDADD = libkernaux.a
tests_test_ntoa_SOURCES = tests/test_ntoa.c
endif
endif

##################
# tests/test_pfa #
##################

if ENABLE_TESTS
if WITH_PFA
TESTS += tests/test_pfa
tests_test_pfa_LDADD = libkernaux.a
tests_test_pfa_SOURCES = tests/test_pfa.c
endif
endif

#########################
# tests/test_pfa_assert #
#########################

if ENABLE_TESTS
if WITH_PFA
TESTS += tests/test_pfa_assert
tests_test_pfa_assert_LDADD = libkernaux.a
tests_test_pfa_assert_SOURCES = tests/test_pfa_assert.c
endif
endif

#############################
# tests/test_printf_fmt_gen #
#############################

if ENABLE_TESTS_PYTHON
if WITH_PRINTF_FMT
TESTS += tests/test_printf_fmt_gen
tests_test_printf_fmt_gen_LDADD = libkernaux.a
tests_test_printf_fmt_gen_SOURCES = \
	tests/test_printf_fmt_gen.c \
	tests/printf_fmt_gen.py \
	tests/printf_fmt_gen.jinja \
	common/printf_fmt.yml
endif
endif

CLEANFILES += tests/test_printf_fmt_gen.c

tests/test_printf_fmt_gen.c: tests/printf_fmt_gen.py tests/printf_fmt_gen.jinja common/printf_fmt.yml
	python3 tests/printf_fmt_gen.py

#########################
# tests/test_printf_gen #
#########################

if ENABLE_TESTS_PYTHON
if WITH_PRINTF
TESTS += tests/test_printf_gen
tests_test_printf_gen_LDADD = libkernaux.a
tests_test_printf_gen_SOURCES = \
	tests/test_printf_gen.c \
	tests/printf_gen.py \
	tests/printf_gen.jinja \
	common/printf.yml \
	common/printf_orig.yml
endif
endif

CLEANFILES += tests/test_printf_gen.c

tests/test_printf_gen.c: tests/printf_gen.py tests/printf_gen.jinja common/printf.yml common/printf_orig.yml
	python3 tests/printf_gen.py

##########################
# tests/test_units_human #
##########################

if ENABLE_TESTS
if WITH_UNITS
TESTS += tests/test_units_human
tests_test_units_human_LDADD = libkernaux.a
tests_test_units_human_SOURCES = tests/test_units_human.c
endif
endif
