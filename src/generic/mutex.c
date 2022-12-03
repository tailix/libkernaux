#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/generic/mutex.h>
#include <kernaux/panic.h>

void KernAux_Mutex_lock(const KernAux_Mutex mutex)
{
    KERNAUX_ASSERT(mutex);
    KERNAUX_ASSERT(mutex->lock);

    mutex->lock((void*)mutex);
}

void KernAux_Mutex_unlock(const KernAux_Mutex mutex)
{
    KERNAUX_ASSERT(mutex);
    KERNAUX_ASSERT(mutex->unlock);

    mutex->unlock((void*)mutex);
}
