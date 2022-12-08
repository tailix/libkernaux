#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/arch/i386.h>
#include <kernaux/assert.h>

#include <string.h>

#define SET_OFFSET do { \
    idte->offset_low  |= 0xffffu & offset;         \
    idte->offset_high |= 0xffffu & (offset >> 16); \
} while (0)

#define DPL (0x60u & (dpl << 5))

void KernAux_Arch_I386_IDTE_init_intr(
    const KernAux_Arch_I386_IDTE idte,
    const uint32_t offset,
    const uint16_t cs_selector,
    const uint8_t dpl
) {
    KERNAUX_ASSERT(idte);

    memset(idte, 0, sizeof(*idte));
    SET_OFFSET;
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
    idte->flags |= 0x80u | DPL | 0x1eu; // 1-00-11110
}

void KernAux_Arch_I386_IDTE_init_trap(
    const KernAux_Arch_I386_IDTE idte,
    const uint32_t offset,
    const uint16_t cs_selector,
    const uint8_t dpl
) {
    KERNAUX_ASSERT(idte);

    memset(idte, 0, sizeof(*idte));
    SET_OFFSET;
    idte->selector = cs_selector;
    idte->flags |= 0x80u | DPL | 0x14u; // 1-00-10100
}
