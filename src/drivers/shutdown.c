#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/drivers/shutdown.h>
#include <kernaux/drivers/qemu.h>

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
    kernaux_drivers_qemu_poweroff();

    // If we can't poweroff then we halt
    kernaux_drivers_shutdown_halt();
}
