include $(top_srcdir)/make/shared.am

SUBDIRS = include

if ENABLE_SPLIT_LIBC
lib_LTLIBRARIES = libc.la
else
EXTRA_LTLIBRARIES = libc.la
endif

libc_la_SOURCES = \
	src/ctype.c \
	src/errno.c \
	src/kernaux.c \
	src/stdlib.c \
	src/string.c

if ASM_I386
libc_la_SOURCES += \
	src/asm/i386/longjmp.S \
	src/asm/i386/setjmp.S
endif

if ASM_X86_64
libc_la_SOURCES += \
	src/asm/x86_64/longjmp.S \
	src/asm/x86_64/setjmp.S
endif

# TODO: implement setjmp/longjmp for riscv64
