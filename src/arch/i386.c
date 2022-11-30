#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/arch/i386.h>

void KernAux_Arch_I386_IDTE_set_offset(
    const KernAux_Arch_I386_IDTE idte,
    const uint32_t address
)
{
    idte->offset_low  = 0xFFFF & address;
    idte->offset_high = 0xFFFF & (address >> 16);
}
