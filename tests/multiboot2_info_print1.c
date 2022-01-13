#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/multiboot2.h>

#include <assert.h>
#include <stdio.h>

#include "multiboot2_example1.h"

int main()
{
    assert(KernAux_Multiboot2_Info_is_valid(
        (struct KernAux_Multiboot2_Info*)multiboot2_example1
    ));

    KernAux_Multiboot2_Info_print(
        (struct KernAux_Multiboot2_Info*)multiboot2_example1,
        (void (*)(const char *format, ...))printf
    );

    return 0;
}
