#ifndef KERNAUX_INCLUDED_ARCH_I386
#define KERNAUX_INCLUDED_ARCH_I386

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>

#include <stdint.h>

#define KERNAUX_ARCH_I386_PAGE_SIZE     (1024 * 4)        // 4 KiB
#define KERNAUX_ARCH_I386_PAGE_BIG_SIZE (1024 * 1024 * 4) // 4 MiB

#define KERNAUX_ARCH_I386_PAGE_DIR_ENTRIES_COUNT   1024
#define KERNAUX_ARCH_I386_PAGE_TABLE_ENTRIES_COUNT 1024

#define KERNAUX_ARCH_I386_PAGES_COUNT_MAX (1024 * 1024)

#define KERNAUX_ARCH_I386_ADDR_TO_PDE_INDEX(addr) \
    ((((uint32_t)addr) & 0xffffffff) >> 22)
#define KERNAUX_ARCH_I386_ADDR_TO_PTE_INDEX(addr) \
    (((((uint32_t)addr) & 0xffffffff) >> 12) & 0x3ff)

#define KERNAUX_ARCH_I386_ADDR_TO_PDE_ADDR(addr) \
    ((((uint32_t)addr) & 0xffffffff) >> 12)
#define KERNAUX_ARCH_I386_ADDR_TO_PTE_ADDR(addr) \
    KERNAUX_ARCH_I386_ADDR_TO_PDE_ADDR(addr)

// CR0 bits
#define KERNAUX_ARCH_I386_CR0_PE ((uint32_t)0x00000001) // 0:  Protected Mode Enable
#define KERNAUX_ARCH_I386_CR0_MP ((uint32_t)0x00000002) // 1:  Monitor co-processor
#define KERNAUX_ARCH_I386_CR0_EM ((uint32_t)0x00000004) // 2:  x87 FPU Emulation
#define KERNAUX_ARCH_I386_CR0_TS ((uint32_t)0x00000008) // 3:  Task switched
#define KERNAUX_ARCH_I386_CR0_ET ((uint32_t)0x00000010) // 4:  Extension type
#define KERNAUX_ARCH_I386_CR0_NE ((uint32_t)0x00000020) // 5:  Numeric error
#define KERNAUX_ARCH_I386_CR0_WP ((uint32_t)0x00010000) // 16: Write protect
#define KERNAUX_ARCH_I386_CR0_AM ((uint32_t)0x00040000) // 18: Alignment mask
#define KERNAUX_ARCH_I386_CR0_NW ((uint32_t)0x20000000) // 29: Not-write trough
#define KERNAUX_ARCH_I386_CR0_CD ((uint32_t)0x40000000) // 30: Cache disable
#define KERNAUX_ARCH_I386_CR0_PG ((uint32_t)0x80000000) // 31: Paging

// Some CR4 bits
#define KERNAUX_ARCH_I386_CR4_VME ((uint32_t)0x00000001) // 0: Virtual 8086 Mode Extensions
#define KERNAUX_ARCH_I386_CR4_PVI ((uint32_t)0x00000002) // 1: Protected-mode Virtual Interrupts
#define KERNAUX_ARCH_I386_CR4_TSD ((uint32_t)0x00000004) // 2: Time Stamp Disable
#define KERNAUX_ARCH_I386_CR4_DE  ((uint32_t)0x00000008) // 3: Debugging Extensions
#define KERNAUX_ARCH_I386_CR4_PSE ((uint32_t)0x00000010) // 4: Page Size Extension
#define KERNAUX_ARCH_I386_CR4_PAE ((uint32_t)0x00000020) // 5: Physical Address Extension
#define KERNAUX_ARCH_I386_CR4_MCE ((uint32_t)0x00000040) // 6: Machine Check Exception
#define KERNAUX_ARCH_I386_CR4_PGE ((uint32_t)0x00000080) // 7: Page Global Enabled
// TODO: bits 8-31

KERNAUX_PACKING_START

// Global or local descriptor table entry
// TODO: validate this according to spec
struct KernAux_Arch_I386_DTE {
    unsigned limit_low              : 16;
    unsigned base_low               : 24;
    unsigned accessed               : 1;
    unsigned read_write             : 1;
    unsigned conforming_expand_down : 1;
    unsigned code                   : 1;
    unsigned always_1               : 1;
    unsigned DPL                    : 2;
    unsigned present                : 1;
    unsigned limit_high             : 4;
    unsigned available              : 1;
    unsigned always_0               : 1;
    unsigned big                    : 1;
    unsigned gran                   : 1;
    unsigned base_high              : 8;
}
KERNAUX_PACKING_ATTR;

/**
 * @brief Task state segment
 * @see The manual, page 132, figure 7-1
 */
struct KernAux_Arch_I386_TSS {
    // 0x00
    unsigned prev_tss    : 16;
    unsigned _zero0      : 16;
    // 0x04
    unsigned esp0        : 32;
    unsigned ss0         : 16;
    unsigned _zero1      : 16;
    unsigned esp1        : 32;
    unsigned ss1         : 16;
    unsigned _zero2      : 16;
    unsigned esp2        : 32;
    unsigned ss2         : 16;
    unsigned _zero3      : 16;
    // 0x1c
    unsigned cr3         : 32;
    unsigned eip         : 32;
    unsigned eflags      : 32;
    unsigned eax         : 32;
    unsigned ecx         : 32;
    unsigned edx         : 32;
    unsigned ebx         : 32;
    unsigned esp         : 32;
    unsigned ebp         : 32;
    unsigned esi         : 32;
    unsigned edi         : 32;
    // 0x48
    unsigned es          : 16;
    unsigned _zero4      : 16;
    unsigned cs          : 16;
    unsigned _zero5      : 16;
    unsigned ss          : 16;
    unsigned _zero6      : 16;
    unsigned ds          : 16;
    unsigned _zero7      : 16;
    unsigned fs          : 16;
    unsigned _zero8      : 16;
    unsigned gs          : 16;
    unsigned _zero9      : 16;
    unsigned ldt         : 16;
    unsigned _zero10     : 16;
    // 0x64
    unsigned _zero11     : 16;
    unsigned io_map_base : 16;
}
KERNAUX_PACKING_ATTR;

// Page directory entry
// TODO: validate this according to spec
struct KernAux_Arch_I386_PDE {
    unsigned present        : 1;
    unsigned writable       : 1;
    unsigned user           : 1;
    unsigned write_through  : 1;
    unsigned cache_disabled : 1;
    unsigned accessed       : 1;
    unsigned available0     : 1;
    unsigned page_size      : 1;
    unsigned available1     : 4;
    unsigned addr           : 20;
}
KERNAUX_PACKING_ATTR;

// Page table entry
// TODO: validate this according to spec
struct KernAux_Arch_I386_PTE {
    unsigned present        : 1;
    unsigned writable       : 1;
    unsigned user           : 1;
    unsigned write_through  : 1;
    unsigned cache_disabled : 1;
    unsigned accessed       : 1;
    unsigned dirty          : 1;
    unsigned attr_table     : 1;
    unsigned global         : 1;
    unsigned available      : 3;
    unsigned addr           : 20;
}
KERNAUX_PACKING_ATTR;

// Page directory
struct KernAux_Arch_I386_PageDir {
    struct KernAux_Arch_I386_PDE pdes[KERNAUX_ARCH_I386_PAGE_DIR_ENTRIES_COUNT];
}
KERNAUX_PACKING_ATTR;

// Page table
struct KernAux_Arch_I386_PageTable {
    struct KernAux_Arch_I386_PTE ptes[KERNAUX_ARCH_I386_PAGE_TABLE_ENTRIES_COUNT];
}
KERNAUX_PACKING_ATTR;

KERNAUX_PACKING_END

#ifdef __cplusplus
}
#endif

#endif
