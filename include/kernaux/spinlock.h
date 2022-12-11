#ifndef KERNAUX_INCLUDED_SPINLOCK
#define KERNAUX_INCLUDED_SPINLOCK

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/generic/mutex.h>
#include <kernaux/macro.h>

#include <stdint.h>

typedef struct KernAux_Spinlock {
    struct KernAux_Mutex mutex;
    volatile uint32_t KERNAUX_PRIVATE_FIELD(locked);
} *KernAux_Spinlock;

struct KernAux_Spinlock KernAux_Spinlock_create();

#ifdef __cplusplus
}
#endif

#endif
