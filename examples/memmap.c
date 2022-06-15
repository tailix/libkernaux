#include <kernaux/memmap.h>

#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define SIZE_256MiB ( 256 * 1024 * 1024)
#define SIZE_512MiB ( 512 * 1024 * 1024)
#define SIZE_1GiB   (1024 * 1024 * 1024)

KernAux_MemMap memmap;

int main()
{
    KernAux_MemMap_init(memmap, SIZE_1GiB);

    assert(KernAux_MemMap_add_entry(memmap, true,  NULL,  0,           SIZE_256MiB));
    assert(KernAux_MemMap_add_entry(memmap, false, "foo", SIZE_256MiB, SIZE_256MiB));
    assert(KernAux_MemMap_add_entry(memmap, true,  "bar", SIZE_512MiB, SIZE_512MiB));

    assert(KernAux_MemMap_finish(memmap));

    return 0;
}
