#include <kernaux/multiboot2.h>

#include <assert.h>
#include <stdio.h>

#include "multiboot2_example1.h"

int main()
{
    assert(KernAux_Multiboot2_is_valid(
        (struct KernAux_Multiboot2*)multiboot2_example1
    ));

    KernAux_Multiboot2_print(
        (struct KernAux_Multiboot2*)multiboot2_example1,
        (void (*)(const char *format, ...))printf
    );

    return 0;
}
