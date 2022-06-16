#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/io.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/*****************
 * KernAux_Store *
 *****************/

size_t KernAux_Store_write(
    const KernAux_Store store,
    const void *const buffer,
    const size_t size
) {
    KERNAUX_ASSERT(store);
    KERNAUX_ASSERT(store->write);

    return store->write(store, buffer, size);
}

int KernAux_Store_putc(const KernAux_Store store, int c)
{
    KERNAUX_ASSERT(store);

    char buffer[1] = { c };
    const size_t result = KernAux_Store_write(store, buffer, 1);
    return result == 0 ? KERNAUX_EOF : buffer[0];
}

bool KernAux_Store_puts(const KernAux_Store store, const char *s)
{
    KERNAUX_ASSERT(store);
    if (!s) return 0;

    const size_t size = strlen(s);
    return KernAux_Store_write(store, s, size) >= size;
}

/********************
 * KernAux_MemStore *
 ********************/

static size_t KernAux_MemStore_read(void *store, void *buffer, size_t size);
static size_t KernAux_MemStore_write(void *store, const void *buffer, size_t size);

struct KernAux_MemStore
KernAux_MemStore_create(void *const start, const size_t size)
{
    struct KernAux_MemStore mem_store;
    KernAux_MemStore_init(&mem_store, start, size);
    return mem_store;
}

void KernAux_MemStore_init(
    KernAux_MemStore mem_store,
    void *const start,
    const size_t size
) {
    KERNAUX_ASSERT(mem_store);

    mem_store->store.write = KernAux_MemStore_write;
    mem_store->store.read  = KernAux_MemStore_read;

    mem_store->start = start;
    mem_store->size  = size;
    mem_store->end   = mem_store->start + size - 1;
    mem_store->limit = mem_store->start + size;
    mem_store->ptr   = mem_store->start;

    KERNAUX_ASSERT(mem_store->start < mem_store->limit);
}

size_t KernAux_MemStore_read(
    void *const store,
    void *const buffer,
    size_t size
) {
    struct KernAux_MemStore *mem_store = store;
    KERNAUX_ASSERT(mem_store);
    KERNAUX_ASSERT(buffer);

    uint8_t *buffer_ptr = buffer;

    while (size && mem_store->ptr <= mem_store->end) {
        --size;
        *(buffer_ptr++) = *(mem_store->ptr++);
    }

    return (uint8_t*)buffer_ptr - (uint8_t*)buffer;
}

size_t KernAux_MemStore_write(
    void *const store,
    const void *const buffer,
    size_t size
) {
    struct KernAux_MemStore *mem_store = store;
    KERNAUX_ASSERT(mem_store);
    KERNAUX_ASSERT(buffer);

    const uint8_t *buffer_ptr = buffer;

    while (size && mem_store->ptr <= mem_store->end) {
        --size;
        *(mem_store->ptr++) = *(buffer_ptr++);
    }

    return (uint8_t*)buffer_ptr - (uint8_t*)buffer;
}

/***********
 * Old API *
 ***********/

struct KernAux_File KernAux_File_create(const KernAux_File_Out out)
{
    struct KernAux_File file;
    KernAux_File_init(&file, out);
    return file;
}

void KernAux_File_init(const KernAux_File file, const KernAux_File_Out out)
{
    KERNAUX_ASSERT(file);
    KERNAUX_ASSERT(out);

    file->out = out;
}
