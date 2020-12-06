#include "config.h"

#include <kernaux/printf.h>
#include <kernaux/stdlib.h>

void kernaux_printf(void (*putchar)(char), const char *format, ...)
{
    va_list va;
    va_start(va, format);
    kernaux_printf_va(putchar, format, va);
    va_end(va);
}

void kernaux_printf_va(
    void (*const putchar)(char),
    const char *format,
    va_list va
) {
}
