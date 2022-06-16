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

KernAux_File KernAux_Store_open(const KernAux_Store store)
{
    KERNAUX_ASSERT(store);
    KERNAUX_ASSERT(store->open);

    return store->open(store);
}

/****************
 * KernAux_File *
 ****************/

struct KernAux_File {
    bool is_active;
    KernAux_Store store;
};

size_t KernAux_File_write(
    const KernAux_File file,
    const void *const buffer,
    const size_t size
) {
    KERNAUX_ASSERT(file);
    KERNAUX_ASSERT(file->store);
    KERNAUX_ASSERT(file->store->write);

    return file->store->write(file->store, buffer, size);
}

int KernAux_File_putc(const KernAux_File file, const int c)
{
    KERNAUX_ASSERT(file);

    char buffer[1] = { c };
    const size_t result = KernAux_File_write(file, buffer, 1);
    return result == 0 ? KERNAUX_EOF : buffer[0];
}

bool KernAux_File_puts(const KernAux_File file, const char *const s)
{
    KERNAUX_ASSERT(file);
    if (!s) return 0;

    const size_t size = strlen(s);
    return KernAux_File_write(file, s, size) >= size;
}

/********************
 * KernAux_MemStore *
 ********************/

#define MEMSTORE_FILES(mem_store) \
    ((struct KernAux_MemFile*)((mem_store)->store.files->ptr))

typedef struct KernAux_MemFile {
    struct KernAux_File file;
    uint8_t *ptr;
} *KernAux_MemFile;

static KernAux_File KernAux_MemStore_open(void *store);
static size_t KernAux_MemStore_read(void *store, void *buffer, size_t size);
static size_t KernAux_MemStore_write(void *store, const void *buffer, size_t size);

struct KernAux_MemStore KernAux_MemStore_create(
    const KernAux_SizedVoid files,
    void *const start,
    const size_t size
) {
    struct KernAux_MemStore mem_store;
    KernAux_MemStore_init(&mem_store, files, start, size);
    return mem_store;
}

void KernAux_MemStore_init(
    KernAux_MemStore mem_store,
    const KernAux_SizedVoid files,
    void *const start,
    const size_t size
) {
    KERNAUX_ASSERT(mem_store);
    KERNAUX_ASSERT(files);

    KernAux_SizedVoid_memset(files, 0);

    mem_store->store.files = files;
    mem_store->store.open  = KernAux_MemStore_open;
    mem_store->store.write = KernAux_MemStore_write;
    mem_store->store.read  = KernAux_MemStore_read;

    mem_store->start = start;
    mem_store->size  = size;
    mem_store->end   = mem_store->start + size - 1;
    mem_store->limit = mem_store->start + size;
    mem_store->ptr   = mem_store->start;

    KERNAUX_ASSERT(mem_store->start < mem_store->limit);
}

KernAux_File KernAux_MemStore_open(void *const store)
{
    struct KernAux_MemStore *mem_store = store;
    KERNAUX_ASSERT(mem_store);

    // FIXME: open many files
    const KernAux_MemFile mem_file = &MEMSTORE_FILES(mem_store)[0];

    if (mem_file->file.is_active) return NULL;

    mem_file->file.is_active = true;
    mem_file->file.store = &mem_store->store;
    mem_file->ptr = mem_store->start;

    return &mem_file->file;
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

struct KernAux_OldFile KernAux_OldFile_create(const KernAux_OldFile_Out out)
{
    struct KernAux_OldFile file;
    KernAux_OldFile_init(&file, out);
    return file;
}

void KernAux_OldFile_init(const KernAux_OldFile file, const KernAux_OldFile_Out out)
{
    KERNAUX_ASSERT(file);
    KERNAUX_ASSERT(out);

    file->out = out;
}
