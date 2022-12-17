include $(top_srcdir)/make/shared.am

noinst_PROGRAMS =
nodist_noinst_DATA =

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

multiboot2_header_example0.bin: $(top_builddir)/fixtures/multiboot2_bin
	$(top_builddir)/fixtures/multiboot2_bin

multiboot2_header_example1.bin: $(top_builddir)/fixtures/multiboot2_bin
	$(top_builddir)/fixtures/multiboot2_bin

multiboot2_header_example2.bin: $(top_builddir)/fixtures/multiboot2_bin
	$(top_builddir)/fixtures/multiboot2_bin

multiboot2_info_example0.bin: $(top_builddir)/fixtures/multiboot2_bin
	$(top_builddir)/fixtures/multiboot2_bin

multiboot2_info_example1.bin: $(top_builddir)/fixtures/multiboot2_bin
	$(top_builddir)/fixtures/multiboot2_bin

multiboot2_info_example2.bin: $(top_builddir)/fixtures/multiboot2_bin
	$(top_builddir)/fixtures/multiboot2_bin

##################
# multiboot2_bin #
##################

if WITH_MULTIBOOT2
noinst_PROGRAMS += multiboot2_bin
multiboot2_bin_LDADD = $(top_builddir)/libkernaux.la
nodist_multiboot2_bin_SOURCES = multiboot2_bin.c
multiboot2_bin_SOURCES = \
	multiboot2_header_example0.h \
	multiboot2_header_example1.h \
	multiboot2_header_example2.h \
	multiboot2_info_example0.h \
	multiboot2_info_example1.h \
	multiboot2_info_example2.h
endif
