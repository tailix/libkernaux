include $(top_srcdir)/shared.am

SUBDIRS = include

if ENABLE_SPLIT_LIBM
lib_LTLIBRARIES = libm.la
else
EXTRA_LTLIBRARIES = libm.la
endif

libm_la_SOURCES = src/main.c
