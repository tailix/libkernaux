#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/multiboot2.h>

#include <assert.h>
#include <stdio.h>

#include "multiboot2_header_example1.h"

int main()
{
    assert(KernAux_Multiboot2_Header_is_valid(
        (struct KernAux_Multiboot2_Header*)&multiboot2_header_example1
    ));

    KernAux_Multiboot2_Header_print(
        (struct KernAux_Multiboot2_Header*)&multiboot2_header_example1,
        (void (*)(const char *format, ...))printf
    );

    return 0;
}
