#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef ARCH_I386
#include <kernaux/arch/i386.h>
#endif

#include <kernaux/console.h>
#include <kernaux/libc.h>
#include <kernaux/printf.h>
#include <kernaux/stdlib.h>

void kernaux_console_print(const char *const s)
{
    kernaux_console_write(s, strlen(s));
}

void kernaux_console_putc(const char c __attribute__((unused)))
{
#ifdef ARCH_I386
    kernaux_arch_i386_outportb(0x3F8, c);
#endif
}

void kernaux_console_puts(const char *const s)
{
    kernaux_console_print(s);
    kernaux_console_putc('\n');
}

void kernaux_console_write(const char *const data, const unsigned int size)
{
    for (unsigned int i = 0; i < size; i++) {
        kernaux_console_putc(data[i]);
    }
}

void kernaux_console_printf(const char *format, ...)
{
    va_list va;
    va_start(va, format);
    kernaux_printf_va(kernaux_console_putc, format, va);
    va_end(va);
}
