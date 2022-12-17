#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define KERNAUX_ACCESS_PROTECTED

#include <kernaux/generic/display.h>
#include <kernaux/macro.h>
#include <kernaux/multiboot2.h>

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

#include "../fixtures/multiboot2_header_example0.h"

static void my_putc(void *display KERNAUX_UNUSED, char c)
{
    putchar(c);
}

static
void my_vprintf(void *display KERNAUX_UNUSED, const char *format, va_list va)
{
    vprintf(format, va);
}

static const struct KernAux_Display display = {
    .putc = my_putc,
    .vprintf = my_vprintf,
};

void test_main()
{
    assert(KernAux_Multiboot2_Header_is_valid(
        (struct KernAux_Multiboot2_Header*)&multiboot2_header_example0
    ));

    KernAux_Multiboot2_Header_print(
        (struct KernAux_Multiboot2_Header*)&multiboot2_header_example0,
        &display
    );
}
