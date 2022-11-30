#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/drivers/qemu.h>

#ifdef ASM_X86
#include <kernaux/asm/x86.h>
#endif

void kernaux_drivers_qemu_poweroff()
{
#ifdef ASM_X86
    // QEMU >= 2.0
    kernaux_asm_x86_outportw(0x604, 0x2000);
    // QEMU < 2.0
    kernaux_asm_x86_outportw(0xB004, 0x2000);
#endif
}
