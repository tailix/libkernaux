#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/multiboot2.h>

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

#include "multiboot2_info_example1.h"

static void my_printf(const char *format, ...)
{
    va_list va;
    va_start(va, format);
    vprintf(format, va);
    va_end(va);
}

void test_main()
{
    assert(KernAux_Multiboot2_Info_is_valid(
        (struct KernAux_Multiboot2_Info*)multiboot2_info_example1
    ));

    KernAux_Multiboot2_Info_print(
        (struct KernAux_Multiboot2_Info*)multiboot2_info_example1,
        my_printf
    );
}
