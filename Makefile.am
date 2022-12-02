include $(top_srcdir)/shared.am

ACLOCAL_AMFLAGS = -I m4
EXTRA_DIST = autogen.sh CONTRIBUTING.md sha256sums.txt

SUBDIRS = include

if WITH_LIBC
# FIXME: after "make clean" libc is not rebuiling
SUBDIRS += libc
endif

SUBDIRS += .

if ENABLE_CHECKS
SUBDIRS += examples tests
endif

libc/libc.la:
	$(MAKE) $(AM_MAKEFLAGS) -C $(top_builddir)/libc libc.la

AM_CFLAGS += -DKERNAUX_ACCESS_PRIVATE

lib_LTLIBRARIES = libkernaux.la

##########
# Checks #
##########

MY_CHECKS =
check: $(MY_CHECKS)

if HAS_CPPCHECK
MY_CHECKS += check-cppcheck
check-cppcheck:
	$(CPPCHECK) $(CPPCHECK_ARGS) $(CPPCHECK_PATHS)

CPPCHECK_ARGS = --quiet --error-exitcode=1 --std=c99 --inline-suppr --enable=warning,style,performance,portability
CPPCHECK_PATHS = examples/ include/ libc/ src/ tests/
endif

##################
# Required files #
##################

libkernaux_la_LIBADD =
libkernaux_la_SOURCES = \
	src/assert.c \
	src/generic/malloc.c \
	src/generic/mutex.c

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
libkernaux_la_SOURCES += src/arch/i386.c
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
	src/multiboot2/enums_to_str.c \
	src/multiboot2/header_helpers.c \
	src/multiboot2/header_is_valid.c \
	src/multiboot2/header_print.c \
	src/multiboot2/info_convert.c \
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

###########
# Drivers #
###########

if WITH_DRIVERS
libkernaux_la_SOURCES += \
	src/drivers/console.c \
	src/drivers/framebuffer.c \
	src/drivers/shutdown.c \
	src/drivers/qemu.c

# Intel 8253-compatible programmable interval timer

if ASM_I386
libkernaux_la_SOURCES += src/drivers/intel_8253_pit.c
endif

# Intel 8259-compatible programmable interrupt controller

if ASM_I386
libkernaux_la_SOURCES += src/drivers/intel_8259_pic.c
endif

endif # WITH_DRIVERS
