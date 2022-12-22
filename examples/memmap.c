#include <kernaux/free_list.h>
#include <kernaux/memmap.h>

#include <stddef.h>
#include <stdio.h>

static char buffer[4096];

void example_main()
{
    struct KernAux_FreeList malloc = KernAux_FreeList_create(NULL);
    KernAux_FreeList_add_zone(&malloc, buffer, sizeof(buffer));

    struct KernAux_Memmap_Builder memmap_builder =
        KernAux_Memmap_Builder_create(&malloc.malloc);

    KernAux_Memmap_Builder_add(&memmap_builder, 0x0, 654336);
    KernAux_Memmap_Builder_add(&memmap_builder, 0x9fc00, 1024);
    KernAux_Memmap_Builder_add(&memmap_builder, 0xf0000, 65536);
    KernAux_Memmap_Builder_add(&memmap_builder, 0x100000, 133038080);
    KernAux_Memmap_Builder_add(&memmap_builder, 0x7fe0000, 131072);
    KernAux_Memmap_Builder_add(&memmap_builder, 0xfffc0000, 262144);

    struct KernAux_Memmap memmap =
        KernAux_Memmap_Builder_finish(&memmap_builder);

    // TODO: remove this
    for (
        KernAux_Memmap_Node node = memmap.KERNAUX_PRIVATE_FIELD(node);
        node;
        node = node->next
    ) {
        printf("{\n");
        printf("  mem_start: %lx\n", node->mem_start);
        printf("  mem_size:  %lu\n", node->mem_size);
        printf("  mem_end:   %lx\n", node->mem_end);
        printf("}\n");
    }

    KernAux_Memmap_free(&memmap);
}
