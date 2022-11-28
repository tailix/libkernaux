#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/drivers/intel_8253_pit.h>

#ifdef ASM_I386
#include <kernaux/asm/i386.h>
#endif

#include <stdint.h>

void kernaux_drivers_intel_8253_pit_initialize(const unsigned int freq)
{
    KERNAUX_ASSERT(freq);

    const unsigned int divisor = 1193180 / freq;

    const uint8_t l = divisor & 0xff;
    const uint8_t h = (divisor >> 8) & 0xff;

    kernaux_asm_x86_outportb(0x43, 0x36);
    kernaux_asm_x86_outportb(0x40, l);
    kernaux_asm_x86_outportb(0x40, h);
}
