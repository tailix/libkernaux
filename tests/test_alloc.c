#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define KERNAUX_ACCESS_MOD_OFF

#include <kernaux/alloc.h>

#include <assert.h>
#include <stddef.h>

static void test_default();
static void test_cross_zone_defrag();

void test_main()
{
    test_default();
    test_cross_zone_defrag();
}

void test_default()
{
    char memory_block[1000];
    struct KernAux_Alloc alloc = KernAux_Alloc_create(NULL);
    KernAux_Alloc_add_zone(&alloc, memory_block, sizeof(memory_block));

    char *const ptr1 = KernAux_Alloc_malloc(&alloc, 100);
    assert(ptr1);
    assert(ptr1 > memory_block);
    assert(ptr1 < &memory_block[1000]);

    char *const ptr2 = KernAux_Alloc_malloc(&alloc, 100);
    assert(ptr2);
    assert(ptr2 > ptr1);
    assert(ptr2 < &memory_block[1000]);

    char *const ptr3 = KernAux_Alloc_malloc(&alloc, 100);
    assert(ptr3);
    assert(ptr3 > ptr2);
    assert(ptr3 < &memory_block[1000]);

    char *const ptr4 = KernAux_Alloc_malloc(&alloc, 100);
    assert(ptr4);
    assert(ptr4 > ptr3);
    assert(ptr4 < &memory_block[1000]);

    KernAux_Alloc_free(&alloc, ptr2);
    KernAux_Alloc_free(&alloc, ptr3);

    char *const ptr5 = KernAux_Alloc_malloc(&alloc, 100);
    assert(ptr5 == ptr2);

    char *const ptr6 = KernAux_Alloc_malloc(&alloc, 100);
    assert(ptr6 == ptr3);

    KernAux_Alloc_free(&alloc, ptr2);
    KernAux_Alloc_free(&alloc, ptr3);

    char *const ptr7 = KernAux_Alloc_malloc(&alloc, 200);
    assert(ptr7 == ptr2);
}

void test_cross_zone_defrag()
{
    char zone[1000];
    struct KernAux_Alloc alloc = KernAux_Alloc_create(NULL);
    KernAux_Alloc_add_zone(&alloc, &zone[0],   500);
    KernAux_Alloc_add_zone(&alloc, &zone[500], 500);

    size_t nodes_count = 0;
    for (
        KernAux_Alloc_Node item_node = alloc.head;
        item_node;
        item_node = item_node->next
    ) {
        ++nodes_count;
    }

    assert(nodes_count == 1);
}
