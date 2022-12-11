#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/generic/mutex.h>
#include <kernaux/macro.h>
#include <kernaux/spinlock.h>

#include <stdint.h>

static void KernAux_Spinlock_lock  (void *mutex);
static void KernAux_Spinlock_unlock(void *mutex);

struct KernAux_Spinlock KernAux_Spinlock_create()
{
    return (struct KernAux_Spinlock){
        .mutex = {
            .lock = KernAux_Spinlock_lock,
            .unlock = KernAux_Spinlock_unlock,
        },
        .locked = 0,
    };
}

void KernAux_Spinlock_lock(void *const mutex)
{
    const KernAux_Spinlock spinlock = mutex;
    KERNAUX_ASSERT(spinlock);
}

void KernAux_Spinlock_unlock(void *const mutex)
{
    const KernAux_Spinlock spinlock = mutex;
    KERNAUX_ASSERT(spinlock);
}
