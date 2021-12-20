#ifndef KERNAUX_INCLUDED_ARCH_I386
#define KERNAUX_INCLUDED_ARCH_I386 1

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define KERNAUX_ARCH_I386_PAGE_DIR_TABLE_LENGTH 1024

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

// Global descriptor table entry
// TODO: validate this according to spec
struct KernAux_Arch_I386_GDTE {
    unsigned int limit_low              : 16;
    unsigned int base_low               : 24;
    unsigned int accessed               : 1;
    unsigned int read_write             : 1;
    unsigned int conforming_expand_down : 1;
    unsigned int code                   : 1;
    unsigned int always_1               : 1;
    unsigned int DPL                    : 2;
    unsigned int present                : 1;
    unsigned int limit_high             : 4;
    unsigned int available              : 1;
    unsigned int always_0               : 1;
    unsigned int big                    : 1;
    unsigned int gran                   : 1;
    unsigned int base_high              : 8;
}
__attribute__((packed));

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
__attribute__((packed));

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
__attribute__((packed));

// Page directory
struct KernAux_Arch_I386_PageDir {
    struct KernAux_Arch_I386_PDE pdes[KERNAUX_ARCH_I386_PAGE_DIR_TABLE_LENGTH];
}
__attribute__((packed));

// Page table
struct KernAux_Arch_I386_PageTable {
    struct KernAux_Arch_I386_PTE ptes[KERNAUX_ARCH_I386_PAGE_DIR_TABLE_LENGTH];
}
__attribute__((packed));

#ifdef __cplusplus
}
#endif

#endif
