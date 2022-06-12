include $(top_srcdir)/shared.am

SUBDIRS = include

if ENABLE_SPLIT_LIBC
lib_LTLIBRARIES = libc.la
else
EXTRA_LTLIBRARIES = libc.la
endif

libc_la_SOURCES = \
	src/ctype.c \
	src/errno.c \
	src/stdlib.c \
	src/string.c
