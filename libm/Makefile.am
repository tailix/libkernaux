SUBDIRS = include

lib_LIBRARIES = libm.a

AM_CFLAGS = \
	-std=c99 \
	-pedantic \
	-Wall \
	-Wextra \
	-I$(top_builddir)/libc/include \
	-I$(top_srcdir)/libc/include \
	-I$(top_builddir)/libm/include \
	-I$(top_srcdir)/libm/include

libm_a_SOURCES = src/main.c
