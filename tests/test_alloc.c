#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/alloc.h>

#include <assert.h>
#include <stddef.h>

int main()
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

    return 0;
}
