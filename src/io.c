#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/io.h>

#include <stddef.h>
#include <stdint.h>

/*****************
 * KernAux_Store *
 *****************/

int KernAux_Store_put_char(KernAux_Store store, int c)
{
    KERNAUX_ASSERT(store);
    KERNAUX_ASSERT(store->put_char);

    return store->put_char(store, c);
}

/********************
 * KernAux_MemStore *
 ********************/

static int KernAux_MemStore_get_char(void *store);
static int KernAux_MemStore_put_char(void *store, int c);

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

    mem_store->store.get_char = KernAux_MemStore_get_char;
    mem_store->store.put_char = KernAux_MemStore_put_char;

    mem_store->start = start;
    mem_store->size  = size;
    mem_store->end   = mem_store->start + size - 1;
    mem_store->limit = mem_store->start + size;
    mem_store->ptr   = mem_store->start;

    KERNAUX_ASSERT(mem_store->start < mem_store->limit);
}

int KernAux_MemStore_get_char(void *store)
{
    struct KernAux_MemStore *mem_store = store;
    KERNAUX_ASSERT(mem_store);
    KERNAUX_ASSERT(mem_store->ptr >= mem_store->start);

    if (mem_store->ptr > mem_store->end) return KERNAUX_EOF;

    return *(mem_store->ptr++);
}

int KernAux_MemStore_put_char(void *store, const int c)
{
    struct KernAux_MemStore *mem_store = store;
    KERNAUX_ASSERT(mem_store);

    if (mem_store->ptr > mem_store->end) return KERNAUX_EOF;

    return *(mem_store->ptr++) = c;
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
