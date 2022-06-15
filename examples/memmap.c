#include <kernaux/memmap.h>

#include <assert.h>
#include <string.h>

#define SIZE_1GiB (1024 * 1024 * 1024)

KernAux_MemMap memmap;

int main()
{
    KernAux_MemMap_init(memmap, SIZE_1GiB);

    return 0;
}
