##################
# Required files #
##################

nobase_include_HEADERS = \
	kernaux.h \
	kernaux/assert.h \
	kernaux/macro.h \
	kernaux/macro/packing_start.run \
	kernaux/macro/packing_end.run \
	kernaux/version.h \
	kernaux/generic/display.h \
	kernaux/generic/malloc.h \
	kernaux/generic/mutex.h

########
# ARCH #
########

if WITH_ARCH_I386
nobase_include_HEADERS += kernaux/arch/i386.h kernaux/arch/i386-idt.h
endif
if WITH_ARCH_RISCV64
nobase_include_HEADERS += kernaux/arch/riscv64.h
endif
if WITH_ARCH_X86_64
nobase_include_HEADERS += kernaux/arch/x86_64.h
endif

if WITH_ARCH_X86
nobase_include_HEADERS += kernaux/arch/x86.h
endif

#######
# ASM #
#######

if WITH_ASM
if ASM_I386
nobase_include_HEADERS += kernaux/asm/i386.h
endif
if ASM_RISCV64
nobase_include_HEADERS += kernaux/asm/riscv64.h
endif
if ASM_X86_64
nobase_include_HEADERS += kernaux/asm/x86_64.h
endif

if ASM_X86
nobase_include_HEADERS += kernaux/asm/x86.h
endif
endif

####################
# Default packages #
####################

if WITH_CMDLINE
nobase_include_HEADERS += kernaux/cmdline.h
endif
if WITH_ELF
nobase_include_HEADERS += kernaux/elf.h
endif
if WITH_FREE_LIST
nobase_include_HEADERS += kernaux/free_list.h
endif
if WITH_MBR
nobase_include_HEADERS += kernaux/mbr.h
endif
if WITH_MEMMAP
nobase_include_HEADERS += kernaux/memmap.h
endif
if WITH_MULTIBOOT2
nobase_include_HEADERS += \
	kernaux/multiboot2.h \
	kernaux/multiboot2/header_macro.h
endif
if WITH_NTOA
nobase_include_HEADERS += kernaux/ntoa.h
endif
if WITH_PFA
nobase_include_HEADERS += kernaux/pfa.h
endif
if WITH_PRINTF
nobase_include_HEADERS += kernaux/printf.h
endif
if WITH_PRINTF_FMT
nobase_include_HEADERS += kernaux/printf_fmt.h
endif
if WITH_SPINLOCK
nobase_include_HEADERS += kernaux/spinlock.h
endif
if WITH_UNITS
nobase_include_HEADERS += kernaux/units.h
endif
