#ifndef KERNAUX_INCLUDED_MUTEX
#define KERNAUX_INCLUDED_MUTEX

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>

typedef void (*KernAux_Mutex_Lock  )(struct KernAux_Mutex *mutex);
typedef void (*KernAux_Mutex_Unlock)(struct KernAux_Mutex *mutex);

typedef struct KernAux_Mutex {
    KernAux_Mutex_Lock   KERNAUX_PROTECTED(lock);
    KernAux_Mutex_Unlock KERNAUX_PROTECTED(unlock);
} *KernAux_Mutex;

void KernAux_Mutex_lock  (KernAux_Mutex mutex);
void KernAux_Mutex_unlock(KernAux_Mutex mutex);

#ifdef __cplusplus
}
#endif

#endif
