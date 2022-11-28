#ifndef KERNAUX_INCLUDED_ARCH_I386
#define KERNAUX_INCLUDED_ARCH_I386

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/arch/x86.h>
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
#define KERNAUX_ARCH_I386_CR0_PE KERNAUX_BITS32(0)  // 0:  Protected Mode Enable
#define KERNAUX_ARCH_I386_CR0_MP KERNAUX_BITS32(1)  // 1:  Monitor co-processor
#define KERNAUX_ARCH_I386_CR0_EM KERNAUX_BITS32(2)  // 2:  x87 FPU Emulation
#define KERNAUX_ARCH_I386_CR0_TS KERNAUX_BITS32(3)  // 3:  Task switched
#define KERNAUX_ARCH_I386_CR0_ET KERNAUX_BITS32(4)  // 4:  Extension type
#define KERNAUX_ARCH_I386_CR0_NE KERNAUX_BITS32(5)  // 5:  Numeric error
#define KERNAUX_ARCH_I386_CR0_WP KERNAUX_BITS32(16) // 16: Write protect
#define KERNAUX_ARCH_I386_CR0_AM KERNAUX_BITS32(18) // 18: Alignment mask
#define KERNAUX_ARCH_I386_CR0_NW KERNAUX_BITS32(29) // 29: Not-write trough
#define KERNAUX_ARCH_I386_CR0_CD KERNAUX_BITS32(30) // 30: Cache disable
#define KERNAUX_ARCH_I386_CR0_PG KERNAUX_BITS32(31) // 31: Paging

// Some CR4 bits
#define KERNAUX_ARCH_I386_CR4_VME KERNAUX_BITS32(0) // 0: Virtual 8086 Mode Extensions
#define KERNAUX_ARCH_I386_CR4_PVI KERNAUX_BITS32(1) // 1: Protected-mode Virtual Interrupts
#define KERNAUX_ARCH_I386_CR4_TSD KERNAUX_BITS32(2) // 2: Time Stamp Disable
#define KERNAUX_ARCH_I386_CR4_DE  KERNAUX_BITS32(3) // 3: Debugging Extensions
#define KERNAUX_ARCH_I386_CR4_PSE KERNAUX_BITS32(4) // 4: Page Size Extension
#define KERNAUX_ARCH_I386_CR4_PAE KERNAUX_BITS32(5) // 5: Physical Address Extension
#define KERNAUX_ARCH_I386_CR4_MCE KERNAUX_BITS32(6) // 6: Machine Check Exception
#define KERNAUX_ARCH_I386_CR4_PGE KERNAUX_BITS32(7) // 7: Page Global Enabled
// TODO: bits 8-31

#include <kernaux/macro/packing_start.run>

// Global, local or interrupt descriptor table register
// TODO: validate this according to spec
struct KernAux_Arch_I386_DTR {
    uint16_t size;
    uint32_t offset;
}
KERNAUX_PACKING_ATTR;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Arch_I386_DTR, 6);

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

// Interrupt descriptor table entry
// TODO: validate this according to spec
typedef struct KernAux_Arch_I386_IDTE {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t  _zero0;
    uint8_t  flags;
    uint16_t offset_high;
}
KERNAUX_PACKING_ATTR
*KernAux_Arch_I386_IDTE;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Arch_I386_DTE, 8);

void KernAux_Arch_I386_IDTE_set_offset(
    KernAux_Arch_I386_IDTE idte,
    uint32_t address
);

/**
 * @brief Task state segment
 * @see The manual, page 132, figure 7-1
 */
struct KernAux_Arch_I386_TSS {
    // 0x00
    uint16_t prev_tss;
    uint16_t _zero0;
    // 0x04
    uint32_t esp0;
    uint16_t ss0;
    uint16_t _zero1;
    uint32_t esp1;
    uint16_t ss1;
    uint16_t _zero2;
    uint32_t esp2;
    uint16_t ss2;
    uint16_t _zero3;
    // 0x1c
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    // 0x48
    uint16_t es;
    uint16_t _zero4;
    uint16_t cs;
    uint16_t _zero5;
    uint16_t ss;
    uint16_t _zero6;
    uint16_t ds;
    uint16_t _zero7;
    uint16_t fs;
    uint16_t _zero8;
    uint16_t gs;
    uint16_t _zero9;
    uint16_t ldt;
    uint16_t _zero10;
    // 0x64
    uint16_t _zero11;
    uint16_t io_map_base;
}
KERNAUX_PACKING_ATTR;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Arch_I386_TSS, 104);

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

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Arch_I386_PDE, 4);

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

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Arch_I386_PDE, 4);

// Page directory
struct KernAux_Arch_I386_PageDir {
    struct KernAux_Arch_I386_PDE pdes[KERNAUX_ARCH_I386_PAGE_DIR_ENTRIES_COUNT];
}
KERNAUX_PACKING_ATTR;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Arch_I386_PageDir, KERNAUX_ARCH_I386_PAGE_SIZE);

// Page table
struct KernAux_Arch_I386_PageTable {
    struct KernAux_Arch_I386_PTE ptes[KERNAUX_ARCH_I386_PAGE_TABLE_ENTRIES_COUNT];
}
KERNAUX_PACKING_ATTR;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Arch_I386_PageTable, KERNAUX_ARCH_I386_PAGE_SIZE);

#include <kernaux/macro/packing_end.run>

#ifdef __cplusplus
}
#endif

#endif
