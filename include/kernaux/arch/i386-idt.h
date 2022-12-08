#ifndef KERNAUX_INCLUDED_ARCH_I386_IDT
#define KERNAUX_INCLUDED_ARCH_I386_IDT

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>

#include <stdint.h>

#include <kernaux/macro/packing_start.run>

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

#include <kernaux/macro/packing_end.run>

#ifdef __cplusplus
}
#endif

#endif
