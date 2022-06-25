#ifndef KERNAUX_INCLUDED_MUTEX
#define KERNAUX_INCLUDED_MUTEX

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>

typedef void (*KernAux_Mutex_Lock  )(void *mutex);
typedef void (*KernAux_Mutex_Unlock)(void *mutex);

typedef const struct KernAux_Mutex {
    KernAux_Mutex_Lock   KERNAUX_PROTECTED_FIELD(lock);
    KernAux_Mutex_Unlock KERNAUX_PROTECTED_FIELD(unlock);
} *KernAux_Mutex;

void KernAux_Mutex_lock  (KernAux_Mutex mutex);
void KernAux_Mutex_unlock(KernAux_Mutex mutex);

#ifdef __cplusplus
}
#endif

#endif
