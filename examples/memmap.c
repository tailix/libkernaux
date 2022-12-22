#include <kernaux/free_list.h>
#include <kernaux/memmap.h>

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

static char buffer[4096];

// TODO: remove this
static void print_nodes(KernAux_Memmap_Node node, unsigned indent);

void example_main()
{
    struct KernAux_FreeList malloc = KernAux_FreeList_create(NULL);
    KernAux_FreeList_add_zone(&malloc, buffer, sizeof(buffer));

    KernAux_Memmap_Builder memmap_builder =
        KernAux_Memmap_Builder_new(&malloc.malloc);
    assert(memmap_builder);

    assert(KernAux_Memmap_Builder_add(memmap_builder, NULL, 0x0, 654336));
    assert(KernAux_Memmap_Builder_add(memmap_builder, NULL, 0x9fc00, 1024));
    assert(KernAux_Memmap_Builder_add(memmap_builder, NULL, 0xf0000, 65536));
    assert(KernAux_Memmap_Builder_add(memmap_builder, NULL, 0x100000, 133038080));
    assert(KernAux_Memmap_Builder_add(memmap_builder, NULL, 0x7fe0000, 131072));
    assert(KernAux_Memmap_Builder_add(memmap_builder, NULL, 0xfffc0000, 262144));

    KernAux_Memmap memmap =
        KernAux_Memmap_Builder_finish_and_free(memmap_builder);
    assert(memmap);

    print_nodes(memmap->root_node, 0);

    KERNAUX_MEMMAP_FREE(memmap);
}

#define INDENT \
    do { for (unsigned i = 0; i < indent; ++i) printf("  "); } while (0)

void print_nodes(KernAux_Memmap_Node node, const unsigned indent)
{
    for (; node; node = node->next) {
        INDENT; printf("{\n");
        INDENT; printf("  mem_start: 0x%lx\n", node->mem_start);
        INDENT; printf("  mem_size:  %lu\n", node->mem_size);
        INDENT; printf("  mem_end:   0x%lx\n", node->mem_end);

        INDENT; printf("  children: [\n");
        print_nodes(node->children, indent + 2);
        INDENT; printf("  ]\n");

        INDENT; printf("}\n");
    }
}
