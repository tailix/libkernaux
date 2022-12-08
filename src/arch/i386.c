#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/arch/i386.h>
#include <kernaux/assert.h>

#include <string.h>

#define DPL (0x60u & (dpl << 5))

void KernAux_Arch_I386_IDTE_init_intr(
    const KernAux_Arch_I386_IDTE idte,
    const uint32_t offset,
    const uint16_t cs_selector,
    const uint8_t dpl
) {
    KERNAUX_ASSERT(idte);

    memset(idte, 0, sizeof(*idte));
    KernAux_Arch_I386_IDTE_set_offset(idte, offset);
    idte->selector = cs_selector;
    idte->flags |= 0x80u | DPL | 0xeu; // 1-00-01110
}

void KernAux_Arch_I386_IDTE_init_task(
    const KernAux_Arch_I386_IDTE idte,
    const uint16_t tss_selector,
    const uint8_t dpl
) {
    KERNAUX_ASSERT(idte);

    memset(idte, 0, sizeof(*idte));
    idte->selector = tss_selector;
    idte->flags |= 0x80u | DPL | 0x5u; // 1-00-00101
}

void KernAux_Arch_I386_IDTE_init_trap(
    const KernAux_Arch_I386_IDTE idte,
    const uint32_t offset,
    const uint16_t cs_selector,
    const uint8_t dpl
) {
    KERNAUX_ASSERT(idte);

    memset(idte, 0, sizeof(*idte));
    KernAux_Arch_I386_IDTE_set_offset(idte, offset);
    idte->selector = cs_selector;
    idte->flags |= 0x80u | DPL | 0xfu; // 1-00-01111
}

void KernAux_Arch_I386_IDTE_set_offset(
    const KernAux_Arch_I386_IDTE idte,
    const uint32_t offset
) {
    KERNAUX_ASSERT(idte);

    idte->offset_low  = 0xffffu & offset;
    idte->offset_high = 0xffffu & (offset >> 16);
}
