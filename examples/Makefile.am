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
cmdline_SOURCES = main.c cmdline.c
endif

###########
# fprintf #
###########

if WITH_PRINTF
if WITH_IO
TESTS += fprintf
fprintf_LDADD = $(top_builddir)/libkernaux.la
fprintf_SOURCES = main.c fprintf.c
endif
endif

##############
# fprintf_va #
##############

if WITH_PRINTF
if WITH_IO
TESTS += fprintf_va
fprintf_va_LDADD = $(top_builddir)/libkernaux.la
fprintf_va_SOURCES = main.c fprintf_va.c
endif
endif

#################
# generic_mutex #
#################

TESTS += generic_mutex
generic_mutex_LDADD = $(top_builddir)/libkernaux.la
generic_mutex_SOURCES = main.c generic_mutex.c

##########
# memmap #
##########

if WITH_MEMMAP
TESTS += memmap
memmap_LDADD = $(top_builddir)/libkernaux.la
memmap_SOURCES = main.c memmap.c
endif

########
# ntoa #
########

if WITH_NTOA
TESTS += ntoa
ntoa_LDADD = $(top_builddir)/libkernaux.la
ntoa_SOURCES = main.c ntoa.c
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
pfa_SOURCES = main.c pfa.c
endif

##############
# printf_fmt #
##############

if WITH_PRINTF_FMT
TESTS += printf_fmt
printf_fmt_LDADD = $(top_builddir)/libkernaux.la
printf_fmt_SOURCES = main.c printf_fmt.c
endif

############
# snprintf #
############

if WITH_PRINTF
TESTS += snprintf
snprintf_LDADD = $(top_builddir)/libkernaux.la
snprintf_SOURCES = main.c snprintf.c
endif

###############
# snprintf_va #
###############

if WITH_PRINTF
TESTS += snprintf_va
snprintf_va_LDADD = $(top_builddir)/libkernaux.la
snprintf_va_SOURCES = main.c snprintf_va.c
endif

###############
# units_human #
###############

if WITH_UNITS
TESTS += units_human
units_human_LDADD = $(top_builddir)/libkernaux.la
units_human_SOURCES = main.c units_human.c
endif
