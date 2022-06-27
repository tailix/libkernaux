#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/generic/file.h>
#include <kernaux/generic/mutex.h>
#include <kernaux/memory_file.h>

static int KernAux_MemoryFile_putc(void *file, unsigned char c);

struct KernAux_MemoryFile KernAux_MemoryFile_create(
    void *const ptr,
    const size_t size,
    const KernAux_Mutex mutex
) {
    struct KernAux_MemoryFile memory_file;
    KernAux_MemoryFile_init(&memory_file, ptr, size, mutex);
    return memory_file;
}

void KernAux_MemoryFile_init(
    const KernAux_MemoryFile memory_file,
    void *const ptr,
    const size_t size,
    const KernAux_Mutex mutex
) {
    KERNAUX_ASSERT(memory_file);
    KERNAUX_ASSERT(ptr);
    KERNAUX_ASSERT(size);

    memory_file->file.putc = KernAux_MemoryFile_putc;
    memory_file->file.puts = NULL;
    memory_file->file.write = NULL;
    memory_file->mutex = mutex;
    memory_file->ptr = ptr;
    memory_file->size = size;
    memory_file->pos = 0;
}

int KernAux_MemoryFile_putc(void *const file, const unsigned char c)
{
    const KernAux_MemoryFile memory_file = file;
    KERNAUX_ASSERT(memory_file);
    KERNAUX_ASSERT(memory_file->ptr);
    KERNAUX_ASSERT(memory_file->size);

    if (memory_file->pos >= memory_file->size) return KERNAUX_EOF;
    memory_file->ptr[memory_file->pos++] = c;
    return c;
}
