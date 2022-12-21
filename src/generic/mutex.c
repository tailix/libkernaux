#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "../assert.h"

#include <kernaux/generic/mutex.h>

void KernAux_Mutex_lock(const KernAux_Mutex mutex)
{
    KERNAUX_NOTNULL(mutex);
    KERNAUX_ASSERT(mutex->lock);

    mutex->lock((void*)mutex);
}

void KernAux_Mutex_unlock(const KernAux_Mutex mutex)
{
    KERNAUX_NOTNULL(mutex);
    KERNAUX_ASSERT(mutex->unlock);

    mutex->unlock((void*)mutex);
}
