SUBDIRS = include

lib_LIBRARIES = libc.a

AM_CFLAGS = \
	-std=c99 \
	-pedantic \
	-Wall \
	-Wextra \
	-I$(top_builddir)/include \
	-I$(top_srcdir)/include \
	-I$(top_builddir)/libc/include \
	-I$(top_srcdir)/libc/include \
	-I$(top_builddir)/libm/include \
	-I$(top_srcdir)/libm/include

libc_a_SOURCES = \
	src/ctype.c \
	src/stdlib.c \
	src/string.c
