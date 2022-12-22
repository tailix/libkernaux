#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/free_list.h>
#include <kernaux/memmap.h>
#include <kernaux/multiboot2.h>

#include <assert.h>
#include <stddef.h>

#include "../fixtures/multiboot2_info_example0.h"
#include "../fixtures/multiboot2_info_example1.h"
#include "../fixtures/multiboot2_info_example2.h"

static char buffer[4096];

void test_main()
{
    struct KernAux_FreeList malloc = KernAux_FreeList_create(NULL);
    KernAux_FreeList_add_zone(&malloc, buffer, sizeof(buffer));

    {
        const KernAux_Memmap_Builder builder =
            KernAux_Multiboot2_Info_to_memmap_builder(
                &multiboot2_info_example0.multiboot2_info,
                &malloc.malloc
            );
        assert(builder == NULL);
    }

    {
        const KernAux_Memmap_Builder builder =
            KernAux_Multiboot2_Info_to_memmap_builder(
                (const struct KernAux_Multiboot2_Info*)
                    &multiboot2_info_example1,
                &malloc.malloc
            );
        assert(builder);
        const KernAux_Memmap memmap =
            KernAux_Memmap_Builder_finish_and_free(builder);
        assert(memmap);
        KernAux_Memmap_free(memmap);
    }

    {
        const KernAux_Memmap_Builder builder =
            KernAux_Multiboot2_Info_to_memmap_builder(
                &multiboot2_info_example2.multiboot2_info,
                &malloc.malloc
            );
        assert(builder);
        const KernAux_Memmap memmap =
            KernAux_Memmap_Builder_finish_and_free(builder);
        assert(memmap);
        KernAux_Memmap_free(memmap);
    }
}
