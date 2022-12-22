include $(top_srcdir)/make/shared.am

CLEANFILES =
TESTS =
noinst_PROGRAMS = $(TESTS)

############################
# multiboot2_header_print0 #
############################

if WITH_MULTIBOOT2
noinst_PROGRAMS += multiboot2_header_print0
multiboot2_header_print0_LDADD = $(top_builddir)/libkernaux.la
multiboot2_header_print0_SOURCES = \
	main.c \
	multiboot2_header_print0.c \
	../fixtures/multiboot2_header_example0.h
endif

############################
# multiboot2_header_print1 #
############################

if WITH_MULTIBOOT2
noinst_PROGRAMS += multiboot2_header_print1
multiboot2_header_print1_LDADD = $(top_builddir)/libkernaux.la
multiboot2_header_print1_SOURCES = \
	main.c \
	multiboot2_header_print1.c \
	../fixtures/multiboot2_header_example1.h
endif

############################
# multiboot2_header_print2 #
############################

if WITH_MULTIBOOT2
noinst_PROGRAMS += multiboot2_header_print2
multiboot2_header_print2_LDADD = $(top_builddir)/libkernaux.la
multiboot2_header_print2_SOURCES = \
	main.c \
	multiboot2_header_print2.c \
	../fixtures/multiboot2_header_example2.h
endif

##########################
# multiboot2_info_print0 #
##########################

if WITH_MULTIBOOT2
noinst_PROGRAMS += multiboot2_info_print0
multiboot2_info_print0_LDADD = $(top_builddir)/libkernaux.la
multiboot2_info_print0_SOURCES = \
	main.c \
	multiboot2_info_print0.c \
	../fixtures/multiboot2_info_example0.h
endif

##########################
# multiboot2_info_print1 #
##########################

if WITH_MULTIBOOT2
noinst_PROGRAMS += multiboot2_info_print1
multiboot2_info_print1_LDADD = $(top_builddir)/libkernaux.la
multiboot2_info_print1_SOURCES = \
	main.c \
	multiboot2_info_print1.c \
	../fixtures/multiboot2_info_example1.h
endif

##########################
# multiboot2_info_print2 #
##########################

if WITH_MULTIBOOT2
noinst_PROGRAMS += multiboot2_info_print2
multiboot2_info_print2_LDADD = $(top_builddir)/libkernaux.la
multiboot2_info_print2_SOURCES = \
	main.c \
	multiboot2_info_print2.c \
	../fixtures/multiboot2_info_example2.h
endif

##################
# test_arch_i386 #
##################

if WITH_ARCH_I386
TESTS += test_arch_i386
test_arch_i386_LDADD = $(top_builddir)/libkernaux.la
test_arch_i386_SOURCES = \
	main.c \
	test_arch_i386.c
endif

################
# test_cmdline #
################

if WITH_CMDLINE
TESTS += test_cmdline
test_cmdline_LDADD = $(top_builddir)/libkernaux.la
test_cmdline_SOURCES = \
	main.c \
	test_cmdline.c \
	cmdline_test.h \
	cmdline_test.c
endif

####################
# test_cmdline_gen #
####################

if ENABLE_CHECKS_PYTHON
if WITH_CMDLINE
TESTS += test_cmdline_gen
test_cmdline_gen_LDADD = $(top_builddir)/libkernaux.la
test_cmdline_gen_SOURCES = \
	main.c \
	test_cmdline_gen.c \
	cmdline_gen.py \
	cmdline_gen.jinja \
	$(top_srcdir)/fixtures/cmdline.yml \
	cmdline_test.h \
	cmdline_test.c
endif
endif

CLEANFILES += test_cmdline_gen.c

test_cmdline_gen.c: $(top_srcdir)/tests/cmdline_gen.py $(top_srcdir)/tests/cmdline_gen.jinja $(top_srcdir)/fixtures/cmdline.yml
	$(PYTHON) $(top_srcdir)/tests/cmdline_gen.py $(top_srcdir)/tests/cmdline_gen.jinja $(top_srcdir)/fixtures/cmdline.yml test_cmdline_gen.c

############
# test_elf #
############

if WITH_ELF
TESTS += test_elf
test_elf_LDADD = $(top_builddir)/libkernaux.la
test_elf_SOURCES = \
	main.c \
	test_elf.c
endif

##################
# test_free_list #
##################

if WITH_FREE_LIST
TESTS += test_free_list
test_free_list_LDADD = $(top_builddir)/libkernaux.la
test_free_list_SOURCES = \
	main.c \
	test_free_list.c
endif

############
# test_mbr #
############

if WITH_MBR
TESTS += test_mbr
test_mbr_LDADD = $(top_builddir)/libkernaux.la
test_mbr_SOURCES = \
	main.c \
	test_mbr.c
endif

##################################
# test_multiboot2_common_packing #
##################################

if WITH_MULTIBOOT2
TESTS += test_multiboot2_common_packing
test_multiboot2_common_packing_LDADD = $(top_builddir)/libkernaux.la
test_multiboot2_common_packing_SOURCES = \
	main.c \
	test_multiboot2_common_packing.c \
	../fixtures/multiboot2_header_example2.h \
	../fixtures/multiboot2_info_example2.h
endif

##################################
# test_multiboot2_header_helpers #
##################################

if WITH_MULTIBOOT2
TESTS += test_multiboot2_header_helpers
test_multiboot2_header_helpers_LDADD = $(top_builddir)/libkernaux.la
test_multiboot2_header_helpers_SOURCES = \
	main.c \
	test_multiboot2_header_helpers.c \
	../fixtures/multiboot2_header_example1.h \
	../fixtures/multiboot2_header_example2.h
endif

################################
# test_multiboot2_header_print #
################################

if WITH_MULTIBOOT2
TESTS += test_multiboot2_header_print
test_multiboot2_header_print_DEPENDENCIES = \
	multiboot2_header_print0 \
	multiboot2_header_print1 \
	multiboot2_header_print2 \
	../fixtures/multiboot2_header_example0.txt \
	../fixtures/multiboot2_header_example1.txt \
	../fixtures/multiboot2_header_example2.txt
test_multiboot2_header_print_LDADD = $(top_builddir)/libkernaux.la
test_multiboot2_header_print_SOURCES = \
	main.c \
	test_multiboot2_header_print.c
endif

#####################################
# test_multiboot2_header_validation #
#####################################

if WITH_MULTIBOOT2
TESTS += test_multiboot2_header_validation
test_multiboot2_header_validation_LDADD = $(top_builddir)/libkernaux.la
test_multiboot2_header_validation_SOURCES = \
	main.c \
	test_multiboot2_header_validation.c \
	../fixtures/multiboot2_header_example1.h \
	../fixtures/multiboot2_header_example2.h
endif

#######################################
# test_multiboot2_info_convert_memmap #
#######################################

if WITH_MULTIBOOT2
if WITH_MEMMAP
TESTS += test_multiboot2_info_convert_memmap
test_multiboot2_info_convert_memmap_LDADD = $(top_builddir)/libkernaux.la
test_multiboot2_info_convert_memmap_SOURCES = \
	main.c \
	test_multiboot2_info_convert_memmap.c \
	../fixtures/multiboot2_header_example2.h \
	../fixtures/multiboot2_info_example2.h
endif
endif

################################
# test_multiboot2_info_helpers #
################################

if WITH_MULTIBOOT2
TESTS += test_multiboot2_info_helpers
test_multiboot2_info_helpers_LDADD = $(top_builddir)/libkernaux.la
test_multiboot2_info_helpers_SOURCES = \
	main.c \
	test_multiboot2_info_helpers.c \
	../fixtures/multiboot2_info_example1.h \
	../fixtures/multiboot2_info_example2.h
endif

##############################
# test_multiboot2_info_print #
##############################

if WITH_MULTIBOOT2
TESTS += test_multiboot2_info_print
test_multiboot2_info_print_DEPENDENCIES = \
	multiboot2_info_print0 \
	multiboot2_info_print1 \
	multiboot2_info_print2 \
	../fixtures/multiboot2_info_example0.txt \
	../fixtures/multiboot2_info_example1.txt \
	../fixtures/multiboot2_info_example2.txt
test_multiboot2_info_print_LDADD = $(top_builddir)/libkernaux.la
test_multiboot2_info_print_SOURCES = \
	main.c \
	test_multiboot2_info_print.c
endif

###################################
# test_multiboot2_info_validation #
###################################

if WITH_MULTIBOOT2
TESTS += test_multiboot2_info_validation
test_multiboot2_info_validation_LDADD = $(top_builddir)/libkernaux.la
test_multiboot2_info_validation_SOURCES = \
	main.c \
	test_multiboot2_info_validation.c \
	../fixtures/multiboot2_info_example1.h \
	../fixtures/multiboot2_info_example2.h
endif

#############
# test_ntoa #
#############

if WITH_NTOA
TESTS += test_ntoa
test_ntoa_LDADD = $(top_builddir)/libkernaux.la
test_ntoa_SOURCES = \
	main.c \
	test_ntoa.c
endif

####################
# test_ntoa_assert #
####################

if ENABLE_ASSERT
if WITH_NTOA
TESTS += test_ntoa_assert
test_ntoa_assert_LDADD = $(top_builddir)/libkernaux.la
test_ntoa_assert_SOURCES = \
	main.c \
	test_ntoa_assert.c
endif
endif

############
# test_pfa #
############

if WITH_PFA
TESTS += test_pfa
test_pfa_LDADD = $(top_builddir)/libkernaux.la
test_pfa_SOURCES = \
	main.c \
	test_pfa.c
endif

###################
# test_pfa_assert #
###################

if ENABLE_ASSERT
if WITH_PFA
TESTS += test_pfa_assert
test_pfa_assert_LDADD = $(top_builddir)/libkernaux.la
test_pfa_assert_SOURCES = \
	main.c \
	test_pfa_assert.c
endif
endif

###############
# test_printf #
###############

if WITH_PRINTF
TESTS += test_printf
test_printf_LDADD = $(top_builddir)/libkernaux.la
test_printf_SOURCES = \
	main.c \
	test_printf.c
endif

#######################
# test_printf_fmt_gen #
#######################

if ENABLE_CHECKS_PYTHON
if WITH_PRINTF_FMT
TESTS += test_printf_fmt_gen
test_printf_fmt_gen_LDADD = $(top_builddir)/libkernaux.la
test_printf_fmt_gen_SOURCES = \
	main.c \
	test_printf_fmt_gen.c \
	printf_fmt_gen.py \
	printf_fmt_gen.jinja \
	$(top_srcdir)/fixtures/printf_fmt.yml
endif
endif

CLEANFILES += test_printf_fmt_gen.c

test_printf_fmt_gen.c: $(top_srcdir)/tests/printf_fmt_gen.py $(top_srcdir)/tests/printf_fmt_gen.jinja $(top_srcdir)/fixtures/printf_fmt.yml
	$(PYTHON) $(top_srcdir)/tests/printf_fmt_gen.py $(top_srcdir)/tests/printf_fmt_gen.jinja $(top_srcdir)/fixtures/printf_fmt.yml test_printf_fmt_gen.c

###################
# test_printf_gen #
###################

if ENABLE_CHECKS_PYTHON
if WITH_PRINTF
TESTS += test_printf_gen
test_printf_gen_LDADD = $(top_builddir)/libkernaux.la
test_printf_gen_SOURCES = \
	main.c \
	test_printf_gen.c \
	printf_gen.py \
	printf_gen.jinja \
	$(top_srcdir)/fixtures/printf.yml \
	$(top_srcdir)/fixtures/printf_orig.yml
endif
endif

CLEANFILES += test_printf_gen.c

test_printf_gen.c: $(top_srcdir)/tests/printf_gen.py $(top_srcdir)/tests/printf_gen.jinja $(top_srcdir)/fixtures/printf.yml $(top_srcdir)/fixtures/printf_orig.yml
	$(PYTHON) $(top_srcdir)/tests/printf_gen.py $(top_srcdir)/tests/printf_gen.jinja $(top_srcdir)/fixtures/printf.yml $(top_srcdir)/fixtures/printf_orig.yml test_printf_gen.c

####################
# test_units_human #
####################

if WITH_UNITS
TESTS += test_units_human
test_units_human_LDADD = $(top_builddir)/libkernaux.la
test_units_human_SOURCES = \
	main.c \
	test_units_human.c
endif
