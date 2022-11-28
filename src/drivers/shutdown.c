#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/drivers/shutdown.h>
#include <kernaux/drivers/qemu.h>

#include <stdbool.h>

static bool is_doing = false;

bool kernaux_drivers_shutdown_is_doing()
{
    return is_doing;
}

void kernaux_drivers_shutdown_halt()
{
    is_doing = true;

#ifdef ASM_X86
    for (;;) __asm__ __volatile__(KERNAUX_DRIVERS_SHUTDOWN_ASM);
#endif

    volatile int x = 0;
    for (;;) ++x;
}

void kernaux_drivers_shutdown_poweroff()
{
    is_doing = true;

    kernaux_drivers_qemu_poweroff();

    // If we can't poweroff then we halt
    kernaux_drivers_shutdown_halt();
}
