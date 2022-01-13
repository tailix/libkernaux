#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/multiboot2.h>

#include <assert.h>
#include <stdio.h>

#include "multiboot2_example2.h"

int main()
{
    assert(KernAux_Multiboot2_Info_is_valid(
        &multiboot2_example2.multiboot2_info
    ));

    KernAux_Multiboot2_Info_print(
        &multiboot2_example2.multiboot2_info,
        (void (*)(const char *format, ...))printf
    );

    return 0;
}
