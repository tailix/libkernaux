#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/generic/mutex.h>

void KernAux_Mutex_lock(const KernAux_Mutex mutex)
{
    KERNAUX_ASSERT(mutex);
    KERNAUX_ASSERT(mutex->lock);

    mutex->lock(mutex->extra_data);
}

void KernAux_Mutex_unlock(const KernAux_Mutex mutex)
{
    KERNAUX_ASSERT(mutex);
    KERNAUX_ASSERT(mutex->unlock);

    mutex->unlock(mutex->extra_data);
}
