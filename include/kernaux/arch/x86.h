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
    }                                                      \
    KERNAUX_PACKED
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

#ifdef __cplusplus
}
#endif

#endif
