#ifndef KERNAUX_INCLUDED_DRIVERS_SHUTDOWN
#define KERNAUX_INCLUDED_DRIVERS_SHUTDOWN

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>

KERNAUX_NORETURN void kernaux_drivers_shutdown_halt();
KERNAUX_NORETURN void kernaux_drivers_shutdown_poweroff();

#ifdef __cplusplus
}
#endif

#endif
