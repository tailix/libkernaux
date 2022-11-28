#ifndef KERNAUX_INCLUDED_DRIVERS_SHUTDOWN
#define KERNAUX_INCLUDED_DRIVERS_SHUTDOWN

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

// TODO: make this cross-platform
#define KERNAUX_DRIVERS_SHUTDOWN_INT 3
#define KERNAUX_DRIVERS_SHUTDOWN_ASM "int $3"

bool kernaux_drivers_shutdown_is_doing();

__attribute__((noreturn))
void kernaux_drivers_shutdown_halt();
void kernaux_drivers_shutdown_poweroff();

#ifdef __cplusplus
}
#endif

#endif
