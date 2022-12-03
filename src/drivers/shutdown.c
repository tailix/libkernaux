#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/drivers/shutdown.h>

#ifdef ASM_X86
#include <kernaux/asm/x86.h>
#endif

void kernaux_drivers_shutdown_halt()
{
#ifdef ASM_X86
    // Disable interrupts
    KERNAUX_ASM("cli");
#endif

    volatile int x = 0;
    for (;;) ++x;
}

void kernaux_drivers_shutdown_poweroff()
{
#ifdef ASM_X86
    // QEMU >= 2.0
    kernaux_asm_x86_outportw(0x604, 0x2000);
    // QEMU < 2.0
    kernaux_asm_x86_outportw(0xB004, 0x2000);
#endif

    // If we can't poweroff then we halt
    kernaux_drivers_shutdown_halt();
}
