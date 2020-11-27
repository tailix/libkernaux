SUBDIRS = include

ACLOCAL_AMFLAGS = -I m4 --install
AM_CFLAGS = -std=c99 -I$(top_srcdir)/include

lib_LIBRARIES = libkernaux.a

EXTRA_DIST = m4/.keep

libkernaux_a_SOURCES = \
	src/arch/i386.S \
	src/pfa.c
