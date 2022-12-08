#ifndef KERNAUX_INCLUDED_ARCH_I386_IDT
#define KERNAUX_INCLUDED_ARCH_I386_IDT

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>

#include <stdint.h>

#include <kernaux/macro/packing_start.run>

/**
 * @brief Interrupt Descriptor Table entry
 *
 * @see https://en.wikibooks.org/wiki/X86_Assembly/Advanced_Interrupts#The_Interrupt_Descriptor_Table
 */
typedef struct KernAux_Arch_I386_IDTE {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t  _;
    uint8_t  flags;
    uint16_t offset_high;
}
KERNAUX_PACKED
KERNAUX_ALIGNED(8)
*KernAux_Arch_I386_IDTE;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Arch_I386_IDTE, 8);

#include <kernaux/macro/packing_end.run>

void KernAux_Arch_I386_IDTE_init_intr(
    KernAux_Arch_I386_IDTE idte,
    uint32_t offset,
    uint16_t cs_selector,
    uint8_t dpl
);
void KernAux_Arch_I386_IDTE_init_task(
    KernAux_Arch_I386_IDTE idte,
    uint16_t tss_selector,
    uint8_t dpl
);
void KernAux_Arch_I386_IDTE_init_trap(
    KernAux_Arch_I386_IDTE idte,
    uint32_t offset,
    uint16_t cs_selector,
    uint8_t dpl
);

uint32_t KernAux_Arch_I386_IDTE_offset(KernAux_Arch_I386_IDTE idte);
uint8_t  KernAux_Arch_I386_IDTE_dpl   (KernAux_Arch_I386_IDTE idte);

void
KernAux_Arch_I386_IDTE_set_offset(KernAux_Arch_I386_IDTE idte, uint32_t offset);

#ifdef __cplusplus
}
#endif

#endif
