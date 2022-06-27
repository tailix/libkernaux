#ifndef KERNAUX_INCLUDED_MEMORY_FILE
#define KERNAUX_INCLUDED_MEMORY_FILE

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/generic/file.h>
#include <kernaux/generic/mutex.h>
#include <kernaux/macro.h>

#include <stddef.h>

typedef struct KernAux_MemoryFile {
    struct KernAux_File file;

    KernAux_Mutex KERNAUX_PRIVATE_FIELD(mutex);
    char         *KERNAUX_PRIVATE_FIELD(ptr);
    size_t        KERNAUX_PRIVATE_FIELD(size);
    size_t        KERNAUX_PRIVATE_FIELD(pos);
} *KernAux_MemoryFile;

struct KernAux_MemoryFile
KernAux_MemoryFile_create(void *ptr, size_t size, KernAux_Mutex mutex);

void KernAux_MemoryFile_init(
    KernAux_MemoryFile memory_file,
    void *ptr,
    size_t size,
    KernAux_Mutex mutex
);

#ifdef __cplusplus
}
#endif

#endif
