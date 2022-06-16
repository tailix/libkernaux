#ifndef KERNAUX_INCLUDED_IO
#define KERNAUX_INCLUDED_IO

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/sized_void.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define KERNAUX_EOF (-1)

/****************
 * KernAux_File *
 ****************/

typedef const struct KernAux_File *KernAux_File;

size_t KernAux_File_write(KernAux_File file, const void *buffer, size_t size);
int KernAux_File_putc(KernAux_File file, int c);
bool KernAux_File_puts(KernAux_File file, const char *s);

/*****************
 * KernAux_Store *
 *****************/

typedef KernAux_File (*KernAux_Store_Open)(void *store);
typedef size_t (*KernAux_Store_Read)(void *store, void *buffer, size_t size);
typedef size_t (*KernAux_Store_Write)(void *store, const void *buffer, size_t size);

typedef struct KernAux_Store {
    KernAux_SizedVoid files;
    KernAux_Store_Open open;
    KernAux_Store_Read read;
    KernAux_Store_Write write;
} *KernAux_Store;

KernAux_File KernAux_Store_open(KernAux_Store store);

/********************
 * KernAux_MemStore *
 ********************/

typedef struct KernAux_MemStore {
    struct KernAux_Store store;
    uint8_t *start, *end, *limit, *ptr;
    size_t size;
} *KernAux_MemStore;

struct KernAux_MemStore
KernAux_MemStore_create(KernAux_SizedVoid files, void *start, size_t size);

void KernAux_MemStore_init(
    KernAux_MemStore mem_store,
    KernAux_SizedVoid files,
    void *start,
    size_t size
);

/***********
 * Old API *
 ***********/

typedef void (*KernAux_OldFile_Out)(char c, void *arg);

typedef struct KernAux_OldFile {
    KernAux_OldFile_Out out;
} *KernAux_OldFile;

struct KernAux_OldFile KernAux_OldFile_create(KernAux_OldFile_Out out);
void KernAux_OldFile_init(KernAux_OldFile file, KernAux_OldFile_Out out);

#ifdef __cplusplus
}
#endif

#endif
