#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "helper.h"

#include <kernaux/multiboot2.h>

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

#include "multiboot2_header_example2.h"

static void my_printf(const char *format, ...)
{
    va_list va;
    va_start(va, format);
    vprintf(format, va);
    va_end(va);
}

int main()
{
    setup_assert_abort();

    assert(KernAux_Multiboot2_Header_is_valid(
        &multiboot2_header_example2.multiboot2_header
    ));

    KernAux_Multiboot2_Header_print(
        &multiboot2_header_example2.multiboot2_header,
        my_printf
    );

    return 0;
}
