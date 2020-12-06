#include "config.h"

#include <kernaux/printf.h>
#include <kernaux/stdlib.h>

void kernaux_printf(void (*putchar)(char), const char *const format, ...)
{
    va_list va;
    va_start(va, format);
    kernaux_printf_va(putchar, format, va);
    va_end(va);
}

void kernaux_printf_va(
    void (*const putchar)(char),
    const char *const format,
    va_list va
) {
    for (const char *current_ptr = format; *current_ptr; ++current_ptr) {
        const char current = *current_ptr;

        if (current != '%') {
            putchar(current);
            continue;
        }

        if (*(++current_ptr) == 's') {
            const char *const arg = va_arg(va, const char*);

            for (const char *arg_ptr = arg; *arg_ptr; ++arg_ptr) {
                putchar(*arg_ptr);
            }
        }
        else {
            break;
        }
    }

    putchar('\0');
}
