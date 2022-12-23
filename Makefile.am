include $(top_srcdir)/make/shared.am
include $(top_srcdir)/make/checks.am

ACLOCAL_AMFLAGS = -I m4
EXTRA_DIST = autogen.sh CONTRIBUTING.md sha256sums.txt src/assert.h

SUBDIRS = include

if WITH_LIBC
# FIXME: after "make clean" libc is not rebuiling
SUBDIRS += libc
endif

SUBDIRS += .

if ENABLE_FIXTURES
SUBDIRS += fixtures
endif

if ENABLE_CHECKS
SUBDIRS += examples tests
endif

libc/libc.la:
	$(MAKE) $(AM_MAKEFLAGS) -C $(top_builddir)/libc libc.la

AM_CFLAGS += -DKERNAUX_ACCESS_PRIVATE

lib_LTLIBRARIES = libkernaux.la

if ENABLE_PKG_CONFIG
pkgconfigdir = @pkgconfdir@
pkgconfig_DATA = libkernaux.pc
endif

##################
# Required files #
##################

libkernaux_la_LDFLAGS = -version-info @PACKAGE_VERSION_SO@
libkernaux_la_LIBADD =
libkernaux_la_SOURCES = \
	src/generic/display.c \
	src/generic/malloc.c \
	src/generic/mutex.c \
	src/runtime.c

########
# libc #
########

if WITH_LIBC
libkernaux_la_LIBADD += libc/libc.la
endif

#######
# ARCH #
#######

if WITH_ARCH_I386
libkernaux_la_SOURCES += src/arch/i386/idt.c
endif

#######
# ASM #
#######

if WITH_ASM
if ASM_I386
libkernaux_la_SOURCES += src/asm/i386.S
endif
if ASM_RISCV64
libkernaux_la_SOURCES += src/asm/riscv64.S
endif
if ASM_X86_64
libkernaux_la_SOURCES += src/asm/x86_64.S
endif
endif

####################
# Default packages #
####################

if WITH_CMDLINE
libkernaux_la_SOURCES += src/cmdline.c
endif
if WITH_ELF
libkernaux_la_SOURCES += src/elf.c
endif
if WITH_FREE_LIST
libkernaux_la_SOURCES += src/free_list.c
endif
if WITH_MBR
libkernaux_la_SOURCES += src/mbr.c
endif
if WITH_MEMMAP
libkernaux_la_SOURCES += src/memmap.c
endif
if WITH_MULTIBOOT2
libkernaux_la_SOURCES += \
	src/multiboot2/header_enums.c \
	src/multiboot2/header_helpers.c \
	src/multiboot2/header_is_valid.c \
	src/multiboot2/header_print.c \
	src/multiboot2/info_convert.c \
	src/multiboot2/info_enums.c \
	src/multiboot2/info_helpers.c \
	src/multiboot2/info_is_valid.c \
	src/multiboot2/info_print.c
endif
if WITH_NTOA
libkernaux_la_SOURCES += src/ntoa.c
endif
if WITH_PFA
libkernaux_la_SOURCES += src/pfa.c
endif
if WITH_PRINTF
libkernaux_la_SOURCES += src/printf.c
endif
if WITH_PRINTF_FMT
libkernaux_la_SOURCES += src/printf_fmt.c
endif
if WITH_UNITS
libkernaux_la_SOURCES += src/units.c
endif
