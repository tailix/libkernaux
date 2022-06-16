#include <kernaux/memmap.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#define SIZE_256MiB ( 256 * 1024 * 1024)
#define SIZE_512MiB ( 512 * 1024 * 1024)
#define SIZE_1GiB   (1024 * 1024 * 1024)

void example_main()
{
    KernAux_MemMap memmap = { KernAux_MemMap_create(SIZE_1GiB) };

    assert(KernAux_MemMap_add_entry(memmap, true,  NULL,  0,           SIZE_256MiB));
    assert(KernAux_MemMap_add_entry(memmap, false, "foo", SIZE_256MiB, SIZE_256MiB));
    assert(KernAux_MemMap_add_entry(memmap, true,  "bar", SIZE_512MiB, SIZE_512MiB));

    assert(KernAux_MemMap_finish(memmap));

    // You can get the entry by it's index:
    assert(       KernAux_MemMap_entry_by_index(memmap, 0)->is_available == true);
    assert(strcmp(KernAux_MemMap_entry_by_index(memmap, 0)->tag, "") == 0);
    assert(       KernAux_MemMap_entry_by_index(memmap, 0)->start == 0);
    assert(       KernAux_MemMap_entry_by_index(memmap, 0)->size  == SIZE_256MiB);
    assert(       KernAux_MemMap_entry_by_index(memmap, 0)->end   == SIZE_256MiB - 1);
    assert(       KernAux_MemMap_entry_by_index(memmap, 0)->limit == SIZE_256MiB);

    // You can get the entry by it's start address:
    assert(       KernAux_MemMap_entry_by_start(memmap, SIZE_256MiB)->is_available == false);
    assert(strcmp(KernAux_MemMap_entry_by_start(memmap, SIZE_256MiB)->tag, "foo") == 0);
    assert(       KernAux_MemMap_entry_by_start(memmap, SIZE_256MiB)->start == SIZE_256MiB);
    assert(       KernAux_MemMap_entry_by_start(memmap, SIZE_256MiB)->size  == SIZE_256MiB);
    assert(       KernAux_MemMap_entry_by_start(memmap, SIZE_256MiB)->end   == SIZE_512MiB - 1);
    assert(       KernAux_MemMap_entry_by_start(memmap, SIZE_256MiB)->limit == SIZE_512MiB);

    // You can get the entry by any address inside it:
    assert(       KernAux_MemMap_entry_by_addr(memmap, SIZE_512MiB              )->is_available == true);
    assert(strcmp(KernAux_MemMap_entry_by_addr(memmap, SIZE_512MiB + 1          )->tag, "bar") == 0);
    assert(       KernAux_MemMap_entry_by_addr(memmap, SIZE_512MiB + SIZE_256MiB)->start == SIZE_512MiB);
    assert(       KernAux_MemMap_entry_by_addr(memmap, SIZE_1GiB - 3            )->size  == SIZE_512MiB);
    assert(       KernAux_MemMap_entry_by_addr(memmap, SIZE_1GiB - 2            )->end   == SIZE_1GiB - 1);
    assert(       KernAux_MemMap_entry_by_addr(memmap, SIZE_1GiB - 1            )->limit == SIZE_1GiB);
}
