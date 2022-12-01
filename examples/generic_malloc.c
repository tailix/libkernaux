//=============
// my_malloc.c
//=============

// To not always use macro "KERNAUX_PROTECTED_FIELD" around the names of
// structure fields you may define "KERNAUX_ACCESS_PROTECTED" before including
// any other headers, but ONLY in the file where you implement a generic type.
//
#define KERNAUX_ACCESS_PROTECTED

//=============
// my_malloc.h
//=============

#include <kernaux/generic/malloc.h>

typedef struct MyMalloc {
    struct KernAux_Malloc malloc;
} *MyMalloc;

struct MyMalloc MyMalloc_create();

//=============
// my_malloc.c
//=============

#include <kernaux/generic/malloc.h>
#include <stddef.h>
#include <stdlib.h>

static void *MyMalloc_calloc (void *malloc, size_t nmemb, size_t size);
static void  MyMalloc_free   (void *malloc, void *ptr);
static void *MyMalloc_malloc (void *malloc, size_t size);
static void *MyMalloc_realloc(void *malloc, void *ptr, size_t size);

struct MyMalloc MyMalloc_create()
{
    return (struct MyMalloc){
        .malloc = {
            .calloc  = MyMalloc_calloc,
            .free    = MyMalloc_free,
            .malloc  = MyMalloc_malloc,
            .realloc = MyMalloc_realloc,
        },
    };
}

void *MyMalloc_calloc(void *const malloc, const size_t nmemb, const size_t size)
{
    (void)malloc; // unused
    return calloc(nmemb, size);
}

void MyMalloc_free(void *const malloc, void *const ptr)
{
    (void)malloc; // unused
    free(ptr);
}

void *MyMalloc_malloc(void *const malloc_, const size_t size)
{
    (void)malloc_; // unused
    return malloc(size);
}

void *MyMalloc_realloc(void *const malloc, void *const ptr, const size_t size)
{
    (void)malloc; // unused
    return realloc(ptr, size);
}

//========
// main.c
//========

#include <assert.h>
#include <string.h>

void example_main()
{
    // Create memory allocator
    struct MyMalloc my_malloc = MyMalloc_create();

    // Allocate memory
    void *ptr = KernAux_Malloc_malloc(&my_malloc.malloc, 1000);

    // Use memory
    strcpy(ptr, "Hello, World!");
    assert(strcmp(ptr, "Hello, World!") == 0);

    // Free memory
    KernAux_Malloc_free(&my_malloc.malloc, ptr);
}
