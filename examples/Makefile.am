include $(top_srcdir)/shared.am

TESTS =
noinst_PROGRAMS = $(TESTS)

#################
# assert_guards #
#################

TESTS += assert_guards
assert_guards_LDADD = $(top_builddir)/libkernaux.a
assert_guards_SOURCES = assert_guards.c

#################
# assert_simple #
#################

TESTS += assert_simple
assert_simple_LDADD = $(top_builddir)/libkernaux.a
assert_simple_SOURCES = assert_simple.c

###########
# cmdline #
###########

if WITH_CMDLINE
TESTS += cmdline
cmdline_LDADD = $(top_builddir)/libkernaux.a
cmdline_SOURCES = cmdline.c
endif

###########
# fprintf #
###########

if WITH_PRINTF
if WITH_FILE
TESTS += fprintf
fprintf_LDADD = $(top_builddir)/libkernaux.a
fprintf_SOURCES = fprintf.c
endif
endif

##############
# fprintf_va #
##############

if WITH_PRINTF
if WITH_FILE
TESTS += fprintf_va
fprintf_va_LDADD = $(top_builddir)/libkernaux.a
fprintf_va_SOURCES = fprintf_va.c
endif
endif

########
# ntoa #
########

if WITH_NTOA
TESTS += ntoa
ntoa_LDADD = $(top_builddir)/libkernaux.a
ntoa_SOURCES = ntoa.c
endif

################
# panic_guards #
################

TESTS += panic_guards
panic_guards_LDADD = $(top_builddir)/libkernaux.a
panic_guards_SOURCES = panic_guards.c

################
# panic_simple #
################

TESTS += panic_simple
panic_simple_LDADD = $(top_builddir)/libkernaux.a
panic_simple_SOURCES = panic_simple.c

#######
# pfa #
#######

if WITH_PFA
TESTS += pfa
pfa_LDADD = $(top_builddir)/libkernaux.a
pfa_SOURCES = pfa.c
endif

##############
# printf_fmt #
##############

if WITH_PRINTF_FMT
TESTS += printf_fmt
printf_fmt_LDADD = $(top_builddir)/libkernaux.a
printf_fmt_SOURCES = printf_fmt.c
endif

############
# snprintf #
############

if WITH_PRINTF
TESTS += snprintf
snprintf_LDADD = $(top_builddir)/libkernaux.a
snprintf_SOURCES = snprintf.c
endif

###############
# snprintf_va #
###############

if WITH_PRINTF
TESTS += snprintf_va
snprintf_va_LDADD = $(top_builddir)/libkernaux.a
snprintf_va_SOURCES = snprintf_va.c
endif

###############
# units_human #
###############

if WITH_UNITS
TESTS += units_human
units_human_LDADD = $(top_builddir)/libkernaux.a
units_human_SOURCES = units_human.c
endif
