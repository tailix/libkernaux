include $(top_srcdir)/shared.am

TESTS =
noinst_PROGRAMS = $(TESTS)

##########
# assert #
##########

TESTS += assert
assert_LDADD = $(top_builddir)/libkernaux.la
assert_SOURCES = assert.c

###########
# cmdline #
###########

if WITH_CMDLINE
TESTS += cmdline
cmdline_LDADD = $(top_builddir)/libkernaux.la
cmdline_SOURCES = cmdline.c
endif

###########
# fprintf #
###########

if WITH_PRINTF
if WITH_IO
TESTS += fprintf
fprintf_LDADD = $(top_builddir)/libkernaux.la
fprintf_SOURCES = fprintf.c
endif
endif

##############
# fprintf_va #
##############

if WITH_PRINTF
if WITH_IO
TESTS += fprintf_va
fprintf_va_LDADD = $(top_builddir)/libkernaux.la
fprintf_va_SOURCES = fprintf_va.c
endif
endif

###############
# io_memstore #
###############

if WITH_IO
TESTS += io_memstore
io_memstore_LDADD = $(top_builddir)/libkernaux.la
io_memstore_SOURCES = io_memstore.c
endif

##########
# memmap #
##########

if WITH_MEMMAP
TESTS += memmap
memmap_LDADD = $(top_builddir)/libkernaux.la
memmap_SOURCES = memmap.c
endif

########
# ntoa #
########

if WITH_NTOA
TESTS += ntoa
ntoa_LDADD = $(top_builddir)/libkernaux.la
ntoa_SOURCES = ntoa.c
endif

#########
# panic #
#########

TESTS += panic
panic_LDADD = $(top_builddir)/libkernaux.la
panic_SOURCES = panic.c

#######
# pfa #
#######

if WITH_PFA
TESTS += pfa
pfa_LDADD = $(top_builddir)/libkernaux.la
pfa_SOURCES = pfa.c
endif

##############
# printf_fmt #
##############

if WITH_PRINTF_FMT
TESTS += printf_fmt
printf_fmt_LDADD = $(top_builddir)/libkernaux.la
printf_fmt_SOURCES = printf_fmt.c
endif

############
# snprintf #
############

if WITH_PRINTF
TESTS += snprintf
snprintf_LDADD = $(top_builddir)/libkernaux.la
snprintf_SOURCES = snprintf.c
endif

###############
# snprintf_va #
###############

if WITH_PRINTF
TESTS += snprintf_va
snprintf_va_LDADD = $(top_builddir)/libkernaux.la
snprintf_va_SOURCES = snprintf_va.c
endif

###############
# units_human #
###############

if WITH_UNITS
TESTS += units_human
units_human_LDADD = $(top_builddir)/libkernaux.la
units_human_SOURCES = units_human.c
endif
