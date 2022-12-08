#ifndef KERNAUX_INCLUDED_ARCH_I386
#define KERNAUX_INCLUDED_ARCH_I386

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/arch/i386-idt.h>
#include <kernaux/arch/x86.h>
#include <kernaux/macro.h>

#include <stdbool.h>
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

#include <kernaux/macro/packing_start.run>

/**
 * @brief CR0 bits
 *
 * @details
 * Contains system control flags that control
 * operating mode and states of the processor.
 *
 * @see https://en.wikipedia.org/wiki/Control_register#CR0
 * @see https://wiki.osdev.org/CPU_Registers_x86#CR0
 */
KERNAUX_ARCH_X86_DEFINE_CR0(I386, uint32_t);
KERNAUX_STATIC_TEST_UNION_SIZE(KernAux_Arch_I386_CR0, 4);

/**
 * @brief CR4 bits
 *
 * @details
 * Contains a group of flags that enable several architectural extensions,
 * and indicate operating system or executive support for specific processor
 * capabilities.
 *
 * @see https://en.wikipedia.org/wiki/Control_register#CR4
 * @see https://wiki.osdev.org/CPU_Registers_x86#CR4
 */
KERNAUX_ARCH_X86_DEFINE_CR4(I386, uint32_t);
KERNAUX_STATIC_TEST_UNION_SIZE(KernAux_Arch_I386_CR4, 4);

// Global, local or interrupt descriptor table register
// TODO: validate this according to spec
struct KernAux_Arch_I386_DTR {
    uint16_t size;
    uint32_t offset;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Arch_I386_DTR, 6);

// Global or local descriptor table entry
// TODO: validate this according to spec
struct KernAux_Arch_I386_DTE {
    uint16_t limit_low;
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
    uint8_t base_high;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Arch_I386_DTE, 8);

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
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Arch_I386_TSS, 104);

// Page directory entry
// TODO: validate this according to spec
union KernAux_Arch_I386_PDE {
    uint32_t number;
#ifdef KERNAUX_BITFIELDS
    struct {
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
    } KERNAUX_PACKED bitfields;
#endif
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_UNION_SIZE(KernAux_Arch_I386_PDE, 4);

// Page table entry
// TODO: validate this according to spec
union KernAux_Arch_I386_PTE {
    uint32_t number;
#ifdef KERNAUX_BITFIELDS
    struct {
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
    } KERNAUX_PACKED bitfields;
#endif
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_UNION_SIZE(KernAux_Arch_I386_PTE, 4);

// Page directory
struct KernAux_Arch_I386_PageDir {
    union KernAux_Arch_I386_PDE pdes[KERNAUX_ARCH_I386_PAGE_DIR_ENTRIES_COUNT];
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Arch_I386_PageDir, KERNAUX_ARCH_I386_PAGE_SIZE);

// Page table
struct KernAux_Arch_I386_PageTable {
    union KernAux_Arch_I386_PTE ptes[KERNAUX_ARCH_I386_PAGE_TABLE_ENTRIES_COUNT];
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Arch_I386_PageTable, KERNAUX_ARCH_I386_PAGE_SIZE);

#include <kernaux/macro/packing_end.run>

#ifdef __cplusplus
}
#endif

#endif
