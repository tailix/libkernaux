include $(top_srcdir)/shared.am

CLEANFILES =
TESTS =
noinst_PROGRAMS = $(TESTS)

############################
# multiboot2_header_print1 #
############################

if WITH_MULTIBOOT2
noinst_PROGRAMS += multiboot2_header_print1
multiboot2_header_print1_LDADD = $(top_builddir)/libkernaux.la
multiboot2_header_print1_SOURCES = \
	multiboot2_header_print1.c \
	multiboot2_header_example1.h
endif

############################
# multiboot2_header_print2 #
############################

if WITH_MULTIBOOT2
noinst_PROGRAMS += multiboot2_header_print2
multiboot2_header_print2_LDADD = $(top_builddir)/libkernaux.la
multiboot2_header_print2_SOURCES = \
	multiboot2_header_print2.c \
	multiboot2_header_example2.h
endif

##########################
# multiboot2_info_print1 #
##########################

if WITH_MULTIBOOT2
noinst_PROGRAMS += multiboot2_info_print1
multiboot2_info_print1_LDADD = $(top_builddir)/libkernaux.la
multiboot2_info_print1_SOURCES = \
	multiboot2_info_print1.c \
	multiboot2_info_example1.h
endif

##########################
# multiboot2_info_print2 #
##########################

if WITH_MULTIBOOT2
noinst_PROGRAMS += multiboot2_info_print2
multiboot2_info_print2_LDADD = $(top_builddir)/libkernaux.la
multiboot2_info_print2_SOURCES = \
	multiboot2_info_print2.c \
	multiboot2_info_example2.h
endif

################
# test_cmdline #
################

if WITH_CMDLINE
TESTS += test_cmdline
test_cmdline_LDADD = $(top_builddir)/libkernaux.la
test_cmdline_SOURCES = test_cmdline.c
endif

####################
# test_cmdline_gen #
####################

if ENABLE_TESTS_PYTHON
if WITH_CMDLINE
TESTS += test_cmdline_gen
test_cmdline_gen_LDADD = $(top_builddir)/libkernaux.la
test_cmdline_gen_SOURCES = \
	test_cmdline_gen.c \
	cmdline_gen.py \
	cmdline_gen.jinja \
	$(top_srcdir)/common/cmdline.yml
endif
endif

CLEANFILES += test_cmdline_gen.c

test_cmdline_gen.c: cmdline_gen.py cmdline_gen.jinja $(top_srcdir)/common/cmdline.yml
	python3 cmdline_gen.py

############
# test_elf #
############

if WITH_ELF
TESTS += test_elf
test_elf_LDADD = $(top_builddir)/libkernaux.la
test_elf_SOURCES = test_elf.c
endif

############
# test_mbr #
############

if WITH_MBR
TESTS += test_mbr
test_mbr_LDADD = $(top_builddir)/libkernaux.la
test_mbr_SOURCES = test_mbr.c
endif

##################################
# test_multiboot2_header_helpers #
##################################

if WITH_MULTIBOOT2
TESTS += test_multiboot2_header_helpers
test_multiboot2_header_helpers_LDADD = $(top_builddir)/libkernaux.la
test_multiboot2_header_helpers_SOURCES = \
	test_multiboot2_header_helpers.c \
	multiboot2_header_example1.h \
	multiboot2_header_example2.h
endif

################################
# test_multiboot2_header_print #
################################

if WITH_MULTIBOOT2
TESTS += test_multiboot2_header_print
test_multiboot2_header_print_DEPENDENCIES = \
	multiboot2_header_print1 \
	multiboot2_header_print2
test_multiboot2_header_print_LDADD = $(top_builddir)/libkernaux.la
test_multiboot2_header_print_SOURCES = test_multiboot2_header_print.c
endif

#####################################
# test_multiboot2_header_validation #
#####################################

if WITH_MULTIBOOT2
TESTS += test_multiboot2_header_validation
test_multiboot2_header_validation_LDADD = $(top_builddir)/libkernaux.la
test_multiboot2_header_validation_SOURCES = \
	test_multiboot2_header_validation.c \
	multiboot2_header_example1.h \
	multiboot2_header_example2.h
endif

################################
# test_multiboot2_info_helpers #
################################

if WITH_MULTIBOOT2
TESTS += test_multiboot2_info_helpers
test_multiboot2_info_helpers_LDADD = $(top_builddir)/libkernaux.la
test_multiboot2_info_helpers_SOURCES = \
	test_multiboot2_info_helpers.c \
	multiboot2_info_example1.h \
	multiboot2_info_example2.h
endif

################################
# test_multiboot2_info_packing #
################################

if WITH_MULTIBOOT2
TESTS += test_multiboot2_info_packing
test_multiboot2_info_packing_LDADD = $(top_builddir)/libkernaux.la
test_multiboot2_info_packing_SOURCES = \
	test_multiboot2_info_packing.c \
	multiboot2_info_example2.h
endif

##############################
# test_multiboot2_info_print #
##############################

if WITH_MULTIBOOT2
TESTS += test_multiboot2_info_print
test_multiboot2_info_print_DEPENDENCIES = \
	multiboot2_info_print1 \
	multiboot2_info_print2
test_multiboot2_info_print_LDADD = $(top_builddir)/libkernaux.la
test_multiboot2_info_print_SOURCES = test_multiboot2_info_print.c
endif

###################################
# test_multiboot2_info_validation #
###################################

if WITH_MULTIBOOT2
TESTS += test_multiboot2_info_validation
test_multiboot2_info_validation_LDADD = $(top_builddir)/libkernaux.la
test_multiboot2_info_validation_SOURCES = \
	test_multiboot2_info_validation.c \
	multiboot2_info_example1.h \
	multiboot2_info_example2.h
endif

#############
# test_ntoa #
#############

if WITH_NTOA
TESTS += test_ntoa
test_ntoa_LDADD = $(top_builddir)/libkernaux.la
test_ntoa_SOURCES = test_ntoa.c
endif

############
# test_pfa #
############

if WITH_PFA
TESTS += test_pfa
test_pfa_LDADD = $(top_builddir)/libkernaux.la
test_pfa_SOURCES = test_pfa.c
endif

###################
# test_pfa_assert #
###################

if WITH_PFA
TESTS += test_pfa_assert
test_pfa_assert_LDADD = $(top_builddir)/libkernaux.la
test_pfa_assert_SOURCES = test_pfa_assert.c
endif

#######################
# test_printf_fmt_gen #
#######################

if ENABLE_TESTS_PYTHON
if WITH_PRINTF_FMT
TESTS += test_printf_fmt_gen
test_printf_fmt_gen_LDADD = $(top_builddir)/libkernaux.la
test_printf_fmt_gen_SOURCES = \
	test_printf_fmt_gen.c \
	printf_fmt_gen.py \
	printf_fmt_gen.jinja \
	$(top_srcdir)/common/printf_fmt.yml
endif
endif

CLEANFILES += test_printf_fmt_gen.c

test_printf_fmt_gen.c: printf_fmt_gen.py printf_fmt_gen.jinja $(top_srcdir)/common/printf_fmt.yml
	python3 printf_fmt_gen.py

###################
# test_printf_gen #
###################

if ENABLE_TESTS_PYTHON
if WITH_PRINTF
TESTS += test_printf_gen
test_printf_gen_LDADD = $(top_builddir)/libkernaux.la
test_printf_gen_SOURCES = \
	test_printf_gen.c \
	printf_gen.py \
	printf_gen.jinja \
	$(top_srcdir)/common/printf.yml \
	$(top_srcdir)/common/printf_orig.yml
endif
endif

CLEANFILES += test_printf_gen.c

test_printf_gen.c: printf_gen.py printf_gen.jinja $(top_srcdir)/common/printf.yml $(top_srcdir)/common/printf_orig.yml
	python3 printf_gen.py

####################
# test_units_human #
####################

if WITH_UNITS
TESTS += test_units_human
test_units_human_LDADD = $(top_builddir)/libkernaux.la
test_units_human_SOURCES = test_units_human.c
endif
