#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/free_list.h>
#include <kernaux/memmap.h>
#include <kernaux/multiboot2.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "../fixtures/multiboot2_info_example0.h"
#include "../fixtures/multiboot2_info_example1.h"
#include "../fixtures/multiboot2_info_example2.h"

static char buffer[4096];

static void test_examples_1_and_2(KernAux_Memmap memmap);

void test_main()
{
    struct KernAux_FreeList malloc = KernAux_FreeList_create(NULL);
    KernAux_FreeList_add_zone(&malloc, buffer, sizeof(buffer));

    {
        const KernAux_Memmap_Builder builder =
            KernAux_Memmap_Builder_new(&malloc.malloc);
        assert(builder != NULL);

        const bool result = KernAux_Multiboot2_Info_to_memmap(
            &multiboot2_info_example0.multiboot2_info,
            builder,
            NULL
        );
        assert(!result);
    }

    {
        const KernAux_Memmap_Builder builder =
            KernAux_Memmap_Builder_new(&malloc.malloc);
        assert(builder != NULL);

        const bool result = KernAux_Multiboot2_Info_to_memmap(
            (const struct KernAux_Multiboot2_Info*)
                &multiboot2_info_example1,
            builder,
            NULL
        );
        assert(result);

        const KernAux_Memmap memmap =
            KernAux_Memmap_Builder_finish_and_free(builder);
        assert(memmap);

        test_examples_1_and_2(memmap);

        KernAux_Memmap_free(memmap);
    }

    {
        const KernAux_Memmap_Builder builder =
            KernAux_Memmap_Builder_new(&malloc.malloc);
        assert(builder != NULL);

        const bool result = KernAux_Multiboot2_Info_to_memmap(
            &multiboot2_info_example2.multiboot2_info,
            builder,
            NULL
        );
        assert(result);

        const KernAux_Memmap memmap =
            KernAux_Memmap_Builder_finish_and_free(builder);
        assert(memmap);

        test_examples_1_and_2(memmap);

        KernAux_Memmap_free(memmap);
    }
}

void test_examples_1_and_2(const KernAux_Memmap memmap)
{
    KernAux_Memmap_Node node = memmap->root_node;

    assert(node);
    assert(node->mem_start == 0x0);
    assert(node->mem_size  == 0xffffffffffffffff);
    assert(node->mem_end   == 0xffffffffffffffff);
    assert(node->tag == NULL);
    assert(node->next == NULL);

    node = node->children;
    assert(node);
    assert(node->mem_start == 0x0);
    assert(node->mem_size  == 654336);
    assert(node->mem_end   == 0x9fbff);
    assert(strcmp(node->tag, "available") == 0);
    assert(node->children  == NULL);
    assert(node == KernAux_Memmap_node_by_addr(memmap, 0x0));
    assert(node == KernAux_Memmap_node_by_addr(memmap, 0x9fbff));

    node = node->next;
    assert(node);
    assert(node->mem_start == 0x9fc00);
    assert(node->mem_size  == 1024);
    assert(node->mem_end   == 0x9ffff);
    assert(strcmp(node->tag, "reserved") == 0);
    assert(node->children  == NULL);
    assert(node == KernAux_Memmap_node_by_addr(memmap, 0x9fc00));
    assert(node == KernAux_Memmap_node_by_addr(memmap, 0x9ffff));

    node = node->next;
    assert(node);
    assert(node->mem_start == 0xf0000);
    assert(node->mem_size  == 65536);
    assert(node->mem_end   == 0xfffff);
    assert(strcmp(node->tag, "reserved") == 0);
    assert(node->children  == NULL);
    assert(node == KernAux_Memmap_node_by_addr(memmap, 0xf0000));
    assert(node == KernAux_Memmap_node_by_addr(memmap, 0xfffff));

    node = node->next;
    assert(node);
    assert(node->mem_start == 0x100000);
    assert(node->mem_size  == 133038080);
    assert(node->mem_end   == 0x7fdffff);
    assert(strcmp(node->tag, "available") == 0);
    assert(node->children  == NULL);
    assert(node == KernAux_Memmap_node_by_addr(memmap, 0x100000));
    assert(node == KernAux_Memmap_node_by_addr(memmap, 0x7fdffff));

    node = node->next;
    assert(node);
    assert(node->mem_start == 0x7fe0000);
    assert(node->mem_size  == 131072);
    assert(node->mem_end   == 0x7ffffff);
    assert(strcmp(node->tag, "reserved") == 0);
    assert(node->children  == NULL);
    assert(node == KernAux_Memmap_node_by_addr(memmap, 0x7fe0000));
    assert(node == KernAux_Memmap_node_by_addr(memmap, 0x7ffffff));

    node = node->next;
    assert(node);
    assert(node->mem_start == 0xfffc0000);
    assert(node->mem_size  == 262144);
    assert(node->mem_end   == 0xffffffff);
    assert(strcmp(node->tag, "reserved") == 0);
    assert(node->children  == NULL);
    assert(node == KernAux_Memmap_node_by_addr(memmap, 0xfffc0000));
    assert(node == KernAux_Memmap_node_by_addr(memmap, 0xffffffff));

    node = node->next;
    assert(node == NULL);
}
