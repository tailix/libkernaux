#include <kernaux/memmap.h>

static char buffer[4096];

void example_main()
{
    struct KernAux_Memmap_Builder memmap_builder =
        KernAux_Memmap_Builder_create_from_buffer(buffer, sizeof(buffer));

    struct KernAux_Memmap memmap =
        KernAux_Memmap_Builder_finish(&memmap_builder);

    KernAux_Memmap_free(&memmap);
}
