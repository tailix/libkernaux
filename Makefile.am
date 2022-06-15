include $(top_srcdir)/shared.am

ACLOCAL_AMFLAGS = -I m4
EXTRA_DIST = autogen.sh CONTRIBUTING.md sha256sums.txt

SUBDIRS = include

if WITH_LIBC
# FIXME: after "make clean" libc is not rebuiling
SUBDIRS += libc
endif

SUBDIRS += .

if ENABLE_TESTS
SUBDIRS += examples tests
endif

libc/libc.la:
	$(MAKE) $(AM_MAKEFLAGS) -C $(top_builddir)/libc libc.la

lib_LTLIBRARIES = libkernaux.la
libexec_PROGRAMS =

libkernaux_la_SOURCES = src/libc.h src/assert.c
libkernaux_la_LIBADD =

if ASM_I386
libkernaux_la_SOURCES += src/asm/i386.S
endif
if ASM_RISCV64
libkernaux_la_SOURCES += src/asm/riscv64.S
endif
if ASM_X86_64
libkernaux_la_SOURCES += src/asm/x86_64.S
endif
if WITH_CMDLINE
libkernaux_la_SOURCES += src/cmdline.c
endif
if WITH_CONSOLE
libkernaux_la_SOURCES += src/console.c
endif
if WITH_ELF
libkernaux_la_SOURCES += src/elf.c
endif
if WITH_FRAMEBUFFER
libkernaux_la_SOURCES += src/framebuffer.c
endif
if WITH_IO
libkernaux_la_SOURCES += src/io.c
endif
if WITH_LIBC
libkernaux_la_LIBADD += libc/libc.la
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

#############################
# kernaux-tester-multiboot2 #
#############################

if WITH_TESTER_MULTIBOOT2
libexec_PROGRAMS += kernaux-tester-multiboot2
kernaux_tester_multiboot2_DEPENDENCIES = libkernaux.la
kernaux_tester_multiboot2_LDADD = -lkernaux -lgcc
kernaux_tester_multiboot2_LDFLAGS = \
	$(AM_LDFLAGS) -T src/testers/multiboot2/linker.ld -Wl,-L.
kernaux_tester_multiboot2_SOURCES = \
	src/testers/multiboot2/linker.ld \
	src/testers/multiboot2/main.c \
	src/testers/multiboot2/multiboot2.c \
	src/testers/multiboot2/start.S
endif

#############################
# kernaux-tester-stivale2 #
#############################

if WITH_TESTER_STIVALE2
libexec_PROGRAMS += kernaux-tester-stivale2
kernaux_tester_stivale2_DEPENDENCIES = libkernaux.la
kernaux_tester_stivale2_LDADD = -lkernaux -lgcc
kernaux_tester_stivale2_LDFLAGS = \
	$(AM_LDFLAGS) -T src/testers/stivale2/linker.ld -Wl,-L.
kernaux_tester_stivale2_SOURCES = \
	src/testers/stivale2/linker.ld \
	src/testers/stivale2/main.c \
	src/testers/stivale2/stivale2.h \
	src/testers/stivale2/stivale2.c
endif
