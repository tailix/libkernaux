#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define KERNAUX_ACCESS_PRIVATE

#include <kernaux/free_list.h>

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

static void test_default();
static void test_cross_zone_defrag();

static void test_calloc();
static void test_calloc_nomem();
static void test_calloc_overflow();
static void test_calloc_zero();

static void test_realloc_alloc();
static void test_realloc_free();
static void test_realloc_memcpy();

static size_t nodes_count(KernAux_FreeList free_list);

static const char *const hello = "Hello, World!";

void test_main()
{
    test_default();
    test_cross_zone_defrag();

    test_calloc();
    test_calloc_nomem();
    test_calloc_overflow();
    test_calloc_zero();

    test_realloc_alloc();
    test_realloc_free();
    test_realloc_memcpy();
}

size_t nodes_count(const KernAux_FreeList free_list)
{
    size_t nodes_count = 0;
    for (
        KernAux_FreeList_Node item_node = free_list->head;
        item_node;
        item_node = item_node->next
    ) {
        ++nodes_count;
    }
    return nodes_count;
}

void test_default()
{
    char memory_block[1000];
    struct KernAux_FreeList free_list = KernAux_FreeList_create(NULL);
    KernAux_FreeList_add_zone(&free_list, memory_block, sizeof(memory_block));

    char *const ptr1 = KernAux_Malloc_malloc(&free_list.malloc, 100);
    assert(ptr1);
    assert(ptr1 > memory_block);
    assert(ptr1 < &memory_block[1000]);

    char *const ptr2 = KernAux_Malloc_calloc(&free_list.malloc, 100, 1);
    assert(ptr2);
    assert(ptr2 > ptr1);
    assert(ptr2 < &memory_block[1000]);

    char *const ptr3 = KernAux_Malloc_calloc(&free_list.malloc, 1, 100);
    assert(ptr3);
    assert(ptr3 > ptr2);
    assert(ptr3 < &memory_block[1000]);

    char *const ptr4 = KernAux_Malloc_malloc(&free_list.malloc, 100);
    assert(ptr4);
    assert(ptr4 > ptr3);
    assert(ptr4 < &memory_block[1000]);

    KernAux_Malloc_free(&free_list.malloc, ptr2);
    KernAux_Malloc_free(&free_list.malloc, ptr3);

    char *const ptr5 = KernAux_Malloc_malloc(&free_list.malloc, 100);
    assert(ptr5 == ptr2);

    char *const ptr6 = KernAux_Malloc_calloc(&free_list.malloc, 10, 10);
    assert(ptr6 == ptr3);

    KernAux_Malloc_free(&free_list.malloc, ptr2);
    KernAux_Malloc_free(&free_list.malloc, ptr3);

    char *const ptr7 = KernAux_Malloc_malloc(&free_list.malloc, 200);
    assert(ptr7 == ptr2);
}

void test_cross_zone_defrag()
{
    char zone[1000];
    struct KernAux_FreeList free_list = KernAux_FreeList_create(NULL);
    KernAux_FreeList_add_zone(&free_list, &zone[0],   500);
    KernAux_FreeList_add_zone(&free_list, &zone[500], 500);

    assert(nodes_count(&free_list) == 1);
}

void test_calloc()
{
    char zone[1000];
    struct KernAux_FreeList free_list = KernAux_FreeList_create(NULL);
    KernAux_FreeList_add_zone(&free_list, zone, 1000);
    char *const ptr = KernAux_Malloc_calloc(&free_list.malloc, 1, 900);
    for (size_t index = 0; index < 900; ++index) {
        assert(ptr[index] == 0);
    }
    KernAux_Malloc_free(&free_list.malloc, ptr);
}

void test_calloc_nomem()
{
    char zone[1000];
    struct KernAux_FreeList free_list = KernAux_FreeList_create(NULL);
    KernAux_FreeList_add_zone(&free_list, zone, sizeof(zone));
    void *const ptr = KernAux_Malloc_calloc(&free_list.malloc, 1, sizeof(zone));
    assert(ptr == NULL);
}

void test_calloc_overflow()
{
    char zone[1000];
    struct KernAux_FreeList free_list = KernAux_FreeList_create(NULL);
    KernAux_FreeList_add_zone(&free_list, zone, SIZE_MAX);
    {
        void *const ptr = KernAux_Malloc_calloc(&free_list.malloc, 2, SIZE_MAX);
        assert(ptr == NULL);
    }
    {
        void *const ptr = KernAux_Malloc_calloc(&free_list.malloc, SIZE_MAX, 2);
        assert(ptr == NULL);
    }
}

void test_calloc_zero()
{
    char zone[1000];
    struct KernAux_FreeList free_list = KernAux_FreeList_create(NULL);
    KernAux_FreeList_add_zone(&free_list, zone, sizeof(zone));
    void *const ptr1 = KernAux_Malloc_calloc(&free_list.malloc, 0, 900);
    assert(ptr1 == NULL);
    void *const ptr2 = KernAux_Malloc_calloc(&free_list.malloc, 900, 0);
    assert(ptr2 == NULL);
}

void test_realloc_alloc()
{
    char zone[1000];
    struct KernAux_FreeList free_list = KernAux_FreeList_create(NULL);
    KernAux_FreeList_add_zone(&free_list, zone, sizeof(zone));
    void *const ptr = KernAux_Malloc_realloc(&free_list.malloc, NULL, 900);
    assert(ptr != NULL);
}

void test_realloc_free()
{
    char zone[1000];
    struct KernAux_FreeList free_list = KernAux_FreeList_create(NULL);
    KernAux_FreeList_add_zone(&free_list, zone, sizeof(zone));

    void *const ptr1 = KernAux_Malloc_malloc(&free_list.malloc, 900);
    assert(ptr1 != NULL);

    void *const ptr2 = KernAux_Malloc_realloc(&free_list.malloc, ptr1, 0);
    assert(ptr2 == NULL);

    void *const ptr3 = KernAux_Malloc_malloc(&free_list.malloc, 900);
    assert(ptr3 != NULL);
}

void test_realloc_memcpy()
{
    char zone[1000];
    struct KernAux_FreeList free_list = KernAux_FreeList_create(NULL);
    KernAux_FreeList_add_zone(&free_list, zone, sizeof(zone));

    char *const ptr1 = KernAux_Malloc_malloc(&free_list.malloc, 400);
    assert(ptr1 != NULL);

    memset(ptr1, 0, 400);
    strcpy(ptr1, hello);
    strcpy(&ptr1[400 - strlen(hello) - 1], hello);

    char *const ptr2 = KernAux_Malloc_realloc(&free_list.malloc, ptr1, 400);
    assert(ptr2 != NULL);

    assert(strcmp(ptr2, hello) == 0);
    assert(strcmp(&ptr2[400 - strlen(hello) - 1], hello) == 0);
}
