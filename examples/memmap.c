#include <kernaux/free_list.h>
#include <kernaux/memmap.h>

#include <stddef.h>

static char buffer[4096];

void example_main()
{
    struct KernAux_FreeList malloc = KernAux_FreeList_create(NULL);
    KernAux_FreeList_add_zone(&malloc, buffer, sizeof(buffer));

    struct KernAux_Memmap_Builder memmap_builder =
        KernAux_Memmap_Builder_create(&malloc.malloc);

    struct KernAux_Memmap memmap =
        KernAux_Memmap_Builder_finish(&memmap_builder);

    KernAux_Memmap_free(&memmap);
}
