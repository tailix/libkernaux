include $(top_srcdir)/make/shared.am

noinst_PROGRAMS =
nodist_noinst_DATA =

EXTRA_DIST = \
	multiboot2_header_example0.txt \
	multiboot2_header_example1.txt \
	multiboot2_header_example2.txt \
	multiboot2_info_example0.txt \
	multiboot2_info_example1.txt \
	multiboot2_info_example2.txt

#########################################
# multiboot2_(header|info)_example*.bin #
#########################################

if WITH_MULTIBOOT2
nodist_noinst_DATA += \
	multiboot2_header_example0.bin \
	multiboot2_header_example1.bin \
	multiboot2_header_example2.bin \
	multiboot2_info_example0.bin \
	multiboot2_info_example1.bin \
	multiboot2_info_example2.bin
endif

multiboot2_header_example0.bin: multiboot2_bin_examples_gen
	./multiboot2_bin_examples_gen header 0

multiboot2_header_example1.bin: multiboot2_bin_examples_gen
	./multiboot2_bin_examples_gen header 1

multiboot2_header_example2.bin: multiboot2_bin_examples_gen
	./multiboot2_bin_examples_gen header 2

multiboot2_info_example0.bin: multiboot2_bin_examples_gen
	./multiboot2_bin_examples_gen info 0

multiboot2_info_example1.bin: multiboot2_bin_examples_gen
	./multiboot2_bin_examples_gen info 1

multiboot2_info_example2.bin: multiboot2_bin_examples_gen
	./multiboot2_bin_examples_gen info 2

###############################
# multiboot2_bin_examples_gen #
###############################

if WITH_MULTIBOOT2
noinst_PROGRAMS += multiboot2_bin_examples_gen
multiboot2_bin_examples_gen_LDADD = $(top_builddir)/libkernaux.la
nodist_multiboot2_bin_examples_gen_SOURCES = multiboot2_bin_examples_gen.c
multiboot2_bin_examples_gen_SOURCES = \
	multiboot2_header_example0.h \
	multiboot2_header_example1.h \
	multiboot2_header_example2.h \
	multiboot2_info_example0.h \
	multiboot2_info_example1.h \
	multiboot2_info_example2.h
endif
