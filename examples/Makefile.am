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

################
# cmdline_file #
################

if WITH_CMDLINE
TESTS += cmdline_file
cmdline_file_LDADD = $(top_builddir)/libkernaux.la
cmdline_file_SOURCES = main.c cmdline_file.c
endif

################
# generic_file #
################

TESTS += generic_file
generic_file_LDADD = $(top_builddir)/libkernaux.la
generic_file_SOURCES = main.c generic_file.c

##################
# generic_malloc #
##################

TESTS += generic_malloc
generic_malloc_LDADD = $(top_builddir)/libkernaux.la
generic_malloc_SOURCES = main.c generic_malloc.c

#################
# generic_mutex #
#################

TESTS += generic_mutex
generic_mutex_LDADD = $(top_builddir)/libkernaux.la
generic_mutex_SOURCES = main.c generic_mutex.c

######################
# macro_container_of #
######################

TESTS += macro_container_of
macro_container_of_LDADD = $(top_builddir)/libkernaux.la
macro_container_of_SOURCES = main.c macro_container_of.c

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

###############
# printf_file #
###############

if WITH_PRINTF
TESTS += printf_file
printf_file_LDADD = $(top_builddir)/libkernaux.la
printf_file_SOURCES = main.c printf_file.c
endif

##################
# printf_file_va #
##################

if WITH_PRINTF
TESTS += printf_file_va
printf_file_va_LDADD = $(top_builddir)/libkernaux.la
printf_file_va_SOURCES = main.c printf_file_va.c
endif

##############
# printf_fmt #
##############

if WITH_PRINTF_FMT
TESTS += printf_fmt
printf_fmt_LDADD = $(top_builddir)/libkernaux.la
printf_fmt_SOURCES = main.c printf_fmt.c
endif

##############
# printf_str #
##############

if WITH_PRINTF
TESTS += printf_str
printf_str_LDADD = $(top_builddir)/libkernaux.la
printf_str_SOURCES = main.c printf_str.c
endif

#################
# printf_str_va #
#################

if WITH_PRINTF
TESTS += printf_str_va
printf_str_va_LDADD = $(top_builddir)/libkernaux.la
printf_str_va_SOURCES = main.c printf_str_va.c
endif

###############
# units_human #
###############

if WITH_UNITS
TESTS += units_human
units_human_LDADD = $(top_builddir)/libkernaux.la
units_human_SOURCES = main.c units_human.c
endif
