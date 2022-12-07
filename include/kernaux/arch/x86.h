#ifndef KERNAUX_INCLUDED_ARCH_X86
#define KERNAUX_INCLUDED_ARCH_X86

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>

#include <stdbool.h>

#ifndef KERNAUX_BITFIELDS
#define KERNAUX_ARCH_X86_DEFINE_CR0(arch, number_type) \
    union KernAux_Arch_##arch##_CR0 { number_type number; } KERNAUX_PACKED
#else
#define KERNAUX_ARCH_X86_DEFINE_CR0(arch, number_type) \
    union KernAux_Arch_##arch##_CR0 {                      \
        number_type number;                                \
        struct {                                           \
            bool     pe : 1; /* 0:  Protection Enable   */ \
            bool     mp : 1; /* 1:  Monitor Coprocessor */ \
            bool     em : 1; /* 2:  Emulation (x87 FPU) */ \
            bool     ts : 1; /* 3:  Task Switched       */ \
            bool     et : 1; /* 4:  Extension Type      */ \
            bool     ne : 1; /* 5:  Numeric Error       */ \
            unsigned _0 : 10;                              \
            bool     wp : 1; /* 16: Write Protect       */ \
            unsigned _1 : 1;                               \
            bool     am : 1; /* 18: Alignment Mask      */ \
            unsigned _2 : 10;                              \
            bool     nw : 1; /* 29: Not Write-trough    */ \
            bool     cd : 1; /* 30: Cache Disable       */ \
            bool     pg : 1; /* 31: Paging              */ \
        } KERNAUX_PACKED bitfields;                        \
    } KERNAUX_PACKED
#endif

#define KERNAUX_ARCH_X86_CR0_PE KERNAUX_BITS32(0)  // Protection Enable
#define KERNAUX_ARCH_X86_CR0_MP KERNAUX_BITS32(1)  // Monitor Coprocessor
#define KERNAUX_ARCH_X86_CR0_EM KERNAUX_BITS32(2)  // Emulation (x87 FPU)
#define KERNAUX_ARCH_X86_CR0_TS KERNAUX_BITS32(3)  // Task Switched
#define KERNAUX_ARCH_X86_CR0_ET KERNAUX_BITS32(4)  // Extension Type
#define KERNAUX_ARCH_X86_CR0_NE KERNAUX_BITS32(5)  // Numeric Error
#define KERNAUX_ARCH_X86_CR0_WP KERNAUX_BITS32(16) // Write Protect
#define KERNAUX_ARCH_X86_CR0_AM KERNAUX_BITS32(18) // Alignment Mask
#define KERNAUX_ARCH_X86_CR0_NW KERNAUX_BITS32(29) // Not Write-trough
#define KERNAUX_ARCH_X86_CR0_CD KERNAUX_BITS32(30) // Cache Disable
#define KERNAUX_ARCH_X86_CR0_PG KERNAUX_BITS32(31) // Paging

#ifndef KERNAUX_BITFIELDS
#define KERNAUX_ARCH_X86_DEFINE_CR4(arch, number_type) \
    union KernAux_Arch_##arch##_CR4 { number_type number; } KERNAUX_PACKED
#else
#define KERNAUX_ARCH_X86_DEFINE_CR4(arch, number_type) \
    union KernAux_Arch_##arch##_CR4 {                                                             \
        number_type number;                                                                       \
        struct {                                                                                  \
            bool     vme        : 1; /* 0:  Virtual-8086 Mode Extensions                       */ \
            bool     pvi        : 1; /* 1:  Protected-Mode Virtual Interrupts                  */ \
            bool     tsd        : 1; /* 2:  Time Stamp Disable                                 */ \
            bool     de         : 1; /* 3:  Debugging Extensions                               */ \
            bool     pse        : 1; /* 4:  Page Size Extension                                */ \
            bool     pae        : 1; /* 5:  Physical Address Extension                         */ \
            bool     mce        : 1; /* 6:  Machine-Check Exception                            */ \
            bool     pge        : 1; /* 7:  Page Global Enable                                 */ \
            bool     pce        : 1; /* 8:  Performance-Monitoring Counter Enabled             */ \
            bool     osfxsr     : 1; /* 9:  Operating System Support for                       */ \
                                     /*     FXSAVE and FXRSTOR instructions                    */ \
            bool     osxmmexcpt : 1; /* 10: Operating System Support for                       */ \
                                     /*     Unmasked SIMD Floating-Point Exceptions            */ \
            bool     umip       : 1; /* 11: User-Mode Instruction Prevention                   */ \
            unsigned _0         : 1;                                                              \
            bool     vmxe       : 1; /* 13: VME (Virtual Machine Extensions) Enable            */ \
            bool     smxe       : 1; /* 14: SME (Safer Mode Extensions) Enable                 */ \
            unsigned _1         : 1;                                                              \
            bool     fsgsbase   : 1; /* 16: FSGSBASE Enable                                    */ \
            bool     pcide      : 1; /* 17: PCID Enable                                        */ \
            bool     osxsave    : 1; /* 18: XSAVE and Processor Extended States Enable         */ \
            unsigned _2         : 1;                                                              \
            bool     smep       : 1; /* 20: SMEP (Supervisor Mode Execution Protection) Enable */ \
            bool     smap       : 1; /* 21: SMAP (Supervisor Mode Access Prevention) Enable    */ \
            bool     pke        : 1; /* 22: Protection Key Enable                              */ \
            unsigned _3         : 9;                                                              \
        } KERNAUX_PACKED bitfields;                                                               \
    } KERNAUX_PACKED
#endif

#define KERNAUX_ARCH_X86_CR4_VME        KERNAUX_BITS32(0)  // Virtual-8086 Mode Extensions
#define KERNAUX_ARCH_X86_CR4_PVI        KERNAUX_BITS32(1)  // Protected-Mode Virtual Interrupts
#define KERNAUX_ARCH_X86_CR4_TSD        KERNAUX_BITS32(2)  // Time Stamp Disable
#define KERNAUX_ARCH_X86_CR4_DE         KERNAUX_BITS32(3)  // Debugging Extensions
#define KERNAUX_ARCH_X86_CR4_PSE        KERNAUX_BITS32(4)  // Page Size Extension
#define KERNAUX_ARCH_X86_CR4_PAE        KERNAUX_BITS32(5)  // Physical Address Extension
#define KERNAUX_ARCH_X86_CR4_MCE        KERNAUX_BITS32(6)  // Machine-Check Exception
#define KERNAUX_ARCH_X86_CR4_PGE        KERNAUX_BITS32(7)  // Page Global Enable
#define KERNAUX_ARCH_X86_CR4_PCE        KERNAUX_BITS32(8)  // Performance-Monitoring Counter Enabled
#define KERNAUX_ARCH_X86_CR4_OSFXSR     KERNAUX_BITS32(9)  // Operating System Support for FXSAVE and FXRSTOR instructions
#define KERNAUX_ARCH_X86_CR4_OSXMMEXCPT KERNAUX_BITS32(10) // Operating System Support for Unmasked SIMD Floating-Point Exceptions
#define KERNAUX_ARCH_X86_CR4_UMIP       KERNAUX_BITS32(11) // User-Mode Instruction Prevention
#define KERNAUX_ARCH_X86_CR4_VMXE       KERNAUX_BITS32(13) // VME (Virtual Machine Extensions) Enable
#define KERNAUX_ARCH_X86_CR4_SMXE       KERNAUX_BITS32(14) // SME (Safer Mode Extensions) Enable
#define KERNAUX_ARCH_X86_CR4_FSGSBASE   KERNAUX_BITS32(16) // FSGSBASE Enable (enable the instructions RDFSBASE, RDGSBASE, WRFSBASE, and WRGSBASE)
#define KERNAUX_ARCH_X86_CR4_PCIDE      KERNAUX_BITS32(17) // PCID Enable
#define KERNAUX_ARCH_X86_CR4_OSXSAVE    KERNAUX_BITS32(18) // XSAVE and Processor Extended States Enable
#define KERNAUX_ARCH_X86_CR4_SMEP       KERNAUX_BITS32(20) // SMEP (Supervisor Mode Execution Protection) Enable
#define KERNAUX_ARCH_X86_CR4_SMAP       KERNAUX_BITS32(21) // SMAP (Supervisor Mode Access Prevention) Enable
#define KERNAUX_ARCH_X86_CR4_PKE        KERNAUX_BITS32(22) // Protection Key Enable

#ifdef __cplusplus
}
#endif

#endif
