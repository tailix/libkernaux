SUBDIRS = include

lib_LIBRARIES = libc.a

AM_CFLAGS = \
	-std=c99 \
	-pedantic \
	-Wall \
	-Wextra \
	-I$(builddir)/include \
	-I$(srcdir)/include

libc_a_SOURCES = \
	src/ctype.c \
	src/stdlib.c \
	src/string.c
