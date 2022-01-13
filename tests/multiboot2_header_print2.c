#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/multiboot2.h>

#include <assert.h>
#include <stdio.h>

#include "multiboot2_header_example2.h"

int main()
{
    assert(KernAux_Multiboot2_Header_is_valid(
        &multiboot2_header_example2.multiboot2_header
    ));

    KernAux_Multiboot2_Header_print(
        &multiboot2_header_example2.multiboot2_header,
        (void (*)(const char *format, ...))printf
    );

    return 0;
}
