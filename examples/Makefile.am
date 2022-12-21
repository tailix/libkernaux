include $(top_srcdir)/make/shared.am

TESTS =
noinst_PROGRAMS = $(TESTS)

###########
# cmdline #
###########

if WITH_CMDLINE
TESTS += cmdline
cmdline_LDADD = $(top_builddir)/libkernaux.la
cmdline_SOURCES = main.c cmdline.c
endif

###################
# generic_display #
###################

TESTS += generic_display
generic_display_LDADD = $(top_builddir)/libkernaux.la
generic_display_SOURCES = main.c generic_display.c

##################
# generic_malloc #
##################

TESTS += generic_malloc
generic_malloc_LDADD = $(top_builddir)/libkernaux.la
generic_malloc_SOURCES = main.c generic_malloc.c

#################
# generic_mutex #
#################

if ENABLE_CHECKS_PTHREADS
TESTS += generic_mutex
generic_mutex_LDADD = $(top_builddir)/libkernaux.la
generic_mutex_SOURCES = main.c generic_mutex.c
endif

##############
# macro_bits #
##############

TESTS += macro_bits
macro_bits_LDADD = $(top_builddir)/libkernaux.la
macro_bits_SOURCES = main.c macro_bits.c

##############
# macro_cast #
##############

TESTS += macro_cast
macro_cast_LDADD = $(top_builddir)/libkernaux.la
macro_cast_SOURCES = main.c macro_cast.c

######################
# macro_container_of #
######################

TESTS += macro_container_of
macro_container_of_LDADD = $(top_builddir)/libkernaux.la
macro_container_of_SOURCES = main.c macro_container_of.c

#################
# macro_packing #
#################

TESTS += macro_packing
macro_packing_LDADD = $(top_builddir)/libkernaux.la
macro_packing_SOURCES = main.c macro_packing.c

#####################
# macro_static_test #
#####################

TESTS += macro_static_test
macro_static_test_LDADD = $(top_builddir)/libkernaux.la
macro_static_test_SOURCES = main.c macro_static_test.c

##########
# memmap #
##########

if WITH_MEMMAP
TESTS += memmap
memmap_LDADD = $(top_builddir)/libkernaux.la
memmap_SOURCES = main.c memmap.c
endif

###########################
# multiboot2_header_macro #
###########################

if WITH_MULTIBOOT2
TESTS += multiboot2_header_macro
multiboot2_header_macro_LDADD = $(top_builddir)/libkernaux.la
multiboot2_header_macro_SOURCES = main.c multiboot2_header_macro.c
endif

########
# ntoa #
########

if WITH_NTOA
TESTS += ntoa
ntoa_LDADD = $(top_builddir)/libkernaux.la
ntoa_SOURCES = main.c ntoa.c
endif

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
