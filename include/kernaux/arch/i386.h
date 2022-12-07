#ifndef KERNAUX_INCLUDED_ARCH_I386
#define KERNAUX_INCLUDED_ARCH_I386

#ifdef __cplusplus
extern "C" {
#endif

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
union KernAux_Arch_I386_CR4 {
    uint32_t number;
#ifdef KERNAUX_BITFIELDS
    struct {
        bool     vme        : 1; // 0:  Virtual-8086 Mode Extensions
        bool     pvi        : 1; // 1:  Protected-Mode Virtual Interrupts
        bool     tsd        : 1; // 2:  Time Stamp Disable
        bool     de         : 1; // 3:  Debugging Extensions
        bool     pse        : 1; // 4:  Page Size Extension
        bool     pae        : 1; // 5:  Physical Address Extension
        bool     mce        : 1; // 6:  Machine-Check Exception
        bool     pge        : 1; // 7:  Page Global Enable
        bool     pce        : 1; // 8:  Performance-Monitoring Counter Enabled
        bool     osfxsr     : 1; // 9:  Operating System Support for FXSAVE and FXRSTOR instructions
        bool     osxmmexcpt : 1; // 10: Operating System Support for Unmasked SIMD Floating-Point Exceptions
        bool     umip       : 1; // 11: User-Mode Instruction Prevention
        unsigned _0         : 1;
        bool     vmxe       : 1; // 13: VME (Virtual Machine Extensions) Enable
        bool     smxe       : 1; // 14: SME (Safer Mode Extensions) Enable
        unsigned _1         : 1;
        bool     fsgsbase   : 1; // 16: FSGSBASE Enable (enable the instructions RDFSBASE, RDGSBASE, WRFSBASE, and WRGSBASE)
        bool     pcide      : 1; // 17: PCID Enable
        bool     osxsave    : 1; // 18: XSAVE and Processor Extended States Enable
        unsigned _2         : 1;
        bool     smep       : 1; // 20: SMEP (Supervisor Mode Execution Protection) Enable
        bool     smap       : 1; // 21: SMAP (Supervisor Mode Access Prevention) Enable
        bool     pke        : 1; // 22: Protection Key Enable
        unsigned _3         : 10;
    } KERNAUX_PACKED bitfields;
#endif
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_UNION_SIZE(KernAux_Arch_I386_CR4, 4);

#define KERNAUX_ARCH_I386_CR4_VME        KERNAUX_BITS32(0)  // Virtual-8086 Mode Extensions
#define KERNAUX_ARCH_I386_CR4_PVI        KERNAUX_BITS32(1)  // Protected-Mode Virtual Interrupts
#define KERNAUX_ARCH_I386_CR4_TSD        KERNAUX_BITS32(2)  // Time Stamp Disable
#define KERNAUX_ARCH_I386_CR4_DE         KERNAUX_BITS32(3)  // Debugging Extensions
#define KERNAUX_ARCH_I386_CR4_PSE        KERNAUX_BITS32(4)  // Page Size Extension
#define KERNAUX_ARCH_I386_CR4_PAE        KERNAUX_BITS32(5)  // Physical Address Extension
#define KERNAUX_ARCH_I386_CR4_MCE        KERNAUX_BITS32(6)  // Machine-Check Exception
#define KERNAUX_ARCH_I386_CR4_PGE        KERNAUX_BITS32(7)  // Page Global Enable
#define KERNAUX_ARCH_I386_CR4_PCE        KERNAUX_BITS32(8)  // Performance-Monitoring Counter Enabled
#define KERNAUX_ARCH_I386_CR4_OSFXSR     KERNAUX_BITS32(9)  // Operating System Support for FXSAVE and FXRSTOR instructions
#define KERNAUX_ARCH_I386_CR4_OSXMMEXCPT KERNAUX_BITS32(10) // Operating System Support for Unmasked SIMD Floating-Point Exceptions
#define KERNAUX_ARCH_I386_CR4_UMIP       KERNAUX_BITS32(11) // User-Mode Instruction Prevention
#define KERNAUX_ARCH_I386_CR4_VMXE       KERNAUX_BITS32(13) // VME (Virtual Machine Extensions) Enable
#define KERNAUX_ARCH_I386_CR4_SMXE       KERNAUX_BITS32(14) // SME (Safer Mode Extensions) Enable
#define KERNAUX_ARCH_I386_CR4_FSGSBASE   KERNAUX_BITS32(16) // FSGSBASE Enable (enable the instructions RDFSBASE, RDGSBASE, WRFSBASE, and WRGSBASE)
#define KERNAUX_ARCH_I386_CR4_PCIDE      KERNAUX_BITS32(17) // PCID Enable
#define KERNAUX_ARCH_I386_CR4_OSXSAVE    KERNAUX_BITS32(18) // XSAVE and Processor Extended States Enable
#define KERNAUX_ARCH_I386_CR4_SMEP       KERNAUX_BITS32(20) // SMEP (Supervisor Mode Execution Protection) Enable
#define KERNAUX_ARCH_I386_CR4_SMAP       KERNAUX_BITS32(21) // SMAP (Supervisor Mode Access Prevention) Enable
#define KERNAUX_ARCH_I386_CR4_PKE        KERNAUX_BITS32(22) // Protection Key Enable

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

// Interrupt descriptor table entry
// TODO: validate this according to spec
typedef struct KernAux_Arch_I386_IDTE {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t  _zero0;
    uint8_t  flags;
    uint16_t offset_high;
}
KERNAUX_PACKED
*KernAux_Arch_I386_IDTE;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Arch_I386_IDTE, 8);

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
