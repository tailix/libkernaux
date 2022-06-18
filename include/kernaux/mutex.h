#ifndef KERNAUX_INCLUDED_MUTEX
#define KERNAUX_INCLUDED_MUTEX

#ifdef __cplusplus
extern "C" {
#endif

#define KERNAUX_MUTEX_EXTRA_DATA_SIZE (32)

typedef void (*KernAux_Mutex_Lock  )(void *extra_data);
typedef void (*KernAux_Mutex_Unlock)(void *extra_data);

typedef struct KernAux_Mutex {
    KernAux_Mutex_Lock lock;
    KernAux_Mutex_Unlock unlock;
    char extra_data[KERNAUX_MUTEX_EXTRA_DATA_SIZE];
} *KernAux_Mutex;

#ifdef __cplusplus
}
#endif

#endif
