#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/drivers/intel_8253_pit.h>

#ifdef ASM_I386
#include <kernaux/asm/i386.h>
#endif

#include <stdint.h>

#if defined(ASM_I386)
#   define inportb  kernaux_asm_i386_inportb
#   define outportb kernaux_asm_i386_outportb
#endif

void kernaux_drivers_intel_8253_pit_initialize(const unsigned int freq)
{
    KERNAUX_ASSERT(freq);

    const unsigned int divisor = 1193180 / freq;

    const uint8_t l = divisor & 0xff;
    const uint8_t h = (divisor >> 8) & 0xff;

    outportb(0x43, 0x36);
    outportb(0x40, l);
    outportb(0x40, h);
}
