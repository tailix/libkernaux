#ifndef KERNAUX_INCLUDED_DRIVERS_SHUTDOWN
#define KERNAUX_INCLUDED_DRIVERS_SHUTDOWN

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((noreturn))
void kernaux_drivers_shutdown_halt();
void kernaux_drivers_shutdown_poweroff();

#ifdef __cplusplus
}
#endif

#endif
