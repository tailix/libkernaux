#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/free_list.h>
#include <kernaux/memmap.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

static char buffer[4096];
static struct KernAux_FreeList malloc;

void test_main()
{
    malloc = KernAux_FreeList_create(NULL);
    KernAux_FreeList_add_zone(&malloc, buffer, sizeof(buffer));

    KernAux_Memmap_Builder memmap_builder =
        KernAux_Memmap_Builder_new(&malloc.malloc);
    assert(memmap_builder);

    // Level 1
    KernAux_Memmap_Node foo_node =
        KernAux_Memmap_Builder_add(memmap_builder, 0x0ULL,                0x8000000000000000ULL, true,  "foo");
    KernAux_Memmap_Node bar_node =
        KernAux_Memmap_Builder_add(memmap_builder, 0x8000000000000000ULL, 0x8000000000000000ULL, false, "bar");

    // Level 2
    KernAux_Memmap_Node foo1_node =
        KernAux_Memmap_Builder_add(memmap_builder, 0x0ULL,                0x4000000000000000ULL, true,  "foo1");
    KernAux_Memmap_Node foo2_node =
        KernAux_Memmap_Builder_add(memmap_builder, 0x4000000000000000ULL, 0x4000000000000000ULL, false, "foo2");
    KernAux_Memmap_Node bar1_node =
        KernAux_Memmap_Builder_add(memmap_builder, 0x8000000000000000ULL, 0x4000000000000000ULL, true,  "bar1");
    KernAux_Memmap_Node bar2_node =
        KernAux_Memmap_Builder_add(memmap_builder, 0xc000000000000000ULL, 0x4000000000000000ULL, false, "bar2");

    // Level 1
    assert(foo_node);
    assert(bar_node);

    // Level 2
    assert(foo1_node);
    assert(foo2_node);
    assert(bar1_node);
    assert(bar2_node);

    const KernAux_Memmap memmap =
        KernAux_Memmap_Builder_finish_and_free(memmap_builder);
    assert(memmap);

    assert(memmap->root_node->next == NULL);
    assert(memmap->root_node->children == foo_node);

    assert(foo_node->next == bar_node);
    assert(bar_node->next == NULL);

    assert(foo_node->children == foo1_node);
    assert(foo1_node->next == foo2_node);
    assert(foo1_node->children == NULL);
    assert(foo2_node->next == NULL);
    assert(foo2_node->children == NULL);

    assert(bar_node->children == bar1_node);
    assert(bar1_node->next == bar2_node);
    assert(bar1_node->children == NULL);
    assert(bar2_node->next == NULL);
    assert(bar2_node->children == NULL);

    assert(foo1_node == KernAux_Memmap_node_by_addr(memmap, 0x0ULL));
    assert(foo1_node == KernAux_Memmap_node_by_addr(memmap, 0x0ULL + 0x4000000000000000ULL / 2));
    assert(foo1_node == KernAux_Memmap_node_by_addr(memmap, 0x0ULL + 0x4000000000000000ULL - 1));

    assert(foo2_node == KernAux_Memmap_node_by_addr(memmap, 0x4000000000000000ULL));
    assert(foo2_node == KernAux_Memmap_node_by_addr(memmap, 0x4000000000000000ULL + 0x4000000000000000ULL / 2));
    assert(foo2_node == KernAux_Memmap_node_by_addr(memmap, 0x4000000000000000ULL + 0x4000000000000000ULL - 1));

    assert(bar1_node == KernAux_Memmap_node_by_addr(memmap, 0x8000000000000000ULL));
    assert(bar1_node == KernAux_Memmap_node_by_addr(memmap, 0x8000000000000000ULL + 0x4000000000000000ULL / 2));
    assert(bar1_node == KernAux_Memmap_node_by_addr(memmap, 0x8000000000000000ULL + 0x4000000000000000ULL - 1));

    assert(bar2_node == KernAux_Memmap_node_by_addr(memmap, 0xc000000000000000ULL));
    assert(bar2_node == KernAux_Memmap_node_by_addr(memmap, 0xc000000000000000ULL + 0x4000000000000000ULL / 2));
    assert(bar2_node == KernAux_Memmap_node_by_addr(memmap, 0xc000000000000000ULL + 0x4000000000000000ULL - 1));

    assert(foo_node->mem_start == 0x0);
    assert(foo_node->mem_size  == 0x8000000000000000ULL);
    assert(foo_node->mem_end   == 0x7fffffffffffffffULL);
    assert(foo_node->is_available == true);
    assert(strcmp(foo_node->tag, "foo") == 0);

    assert(bar_node->mem_start == 0x8000000000000000ULL);
    assert(bar_node->mem_size  == 0x8000000000000000ULL);
    assert(bar_node->mem_end   == 0xffffffffffffffffULL);
    assert(bar_node->is_available == false);
    assert(strcmp(bar_node->tag, "bar") == 0);

    assert(foo1_node->mem_start == 0x0);
    assert(foo1_node->mem_size  == 0x4000000000000000ULL);
    assert(foo1_node->mem_end   == 0x3fffffffffffffffULL);
    assert(foo1_node->is_available == true);
    assert(strcmp(foo1_node->tag, "foo1") == 0);

    assert(foo2_node->mem_start == 0x4000000000000000ULL);
    assert(foo2_node->mem_size  == 0x4000000000000000ULL);
    assert(foo2_node->mem_end   == 0x7fffffffffffffffULL);
    assert(foo2_node->is_available == false);
    assert(strcmp(foo2_node->tag, "foo2") == 0);

    assert(bar1_node->mem_start == 0x8000000000000000ULL);
    assert(bar1_node->mem_size  == 0x4000000000000000ULL);
    assert(bar1_node->mem_end   == 0xbfffffffffffffffULL);
    assert(bar1_node->is_available == true);
    assert(strcmp(bar1_node->tag, "bar1") == 0);

    assert(bar2_node->mem_start == 0xc000000000000000ULL);
    assert(bar2_node->mem_size  == 0x4000000000000000ULL);
    assert(bar2_node->mem_end   == 0xffffffffffffffffULL);
    assert(bar2_node->is_available == false);
    assert(strcmp(bar2_node->tag, "bar2") == 0);
}
