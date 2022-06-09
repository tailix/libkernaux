include $(top_srcdir)/shared.am
ACLOCAL_AMFLAGS = -I m4

SUBDIRS = include

if WITH_LIBC
SUBDIRS += libc
endif
if WITH_LIBM
SUBDIRS += libm
endif

SUBDIRS += .

if ENABLE_TESTS
SUBDIRS += examples tests
endif

lib_LIBRARIES = libkernaux.a

libkernaux_a_SOURCES = src/libc.h src/assert.c
libkernaux_a_LIBADD =

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
libkernaux_a_LIBADD += libc/libc.a
endif
if WITH_LIBM
libkernaux_a_LIBADD += libm/libm.a
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
