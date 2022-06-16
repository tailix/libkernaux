#ifndef KERNAUX_INCLUDED_IO
#define KERNAUX_INCLUDED_IO

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

#define KERNAUX_EOF (-1)

typedef int (*KernAux_Store_GetChar)(void *store);
typedef int (*KernAux_Store_PutChar)(void *store, int c);

/*****************
 * KernAux_Store *
 *****************/

typedef struct KernAux_Store {
    KernAux_Store_GetChar get_char;
    KernAux_Store_PutChar put_char;
} *KernAux_Store;

int KernAux_Store_put_char(KernAux_Store store, int c);

/********************
 * KernAux_MemStore *
 ********************/

typedef struct KernAux_MemStore {
    struct KernAux_Store store;
    uint8_t *start, *end, *limit, *ptr;
    size_t size;
} *KernAux_MemStore;

struct KernAux_MemStore
KernAux_MemStore_create(void *start, size_t size);
void
KernAux_MemStore_init(KernAux_MemStore mem_store, void *start, size_t size);

/***********
 * Old API *
 ***********/

typedef void (*KernAux_File_Out)(char c, void *arg);

typedef struct KernAux_File {
    KernAux_File_Out out;
} *KernAux_File;

struct KernAux_File KernAux_File_create(KernAux_File_Out out);
void KernAux_File_init(KernAux_File file, KernAux_File_Out out);

#ifdef __cplusplus
}
#endif

#endif
