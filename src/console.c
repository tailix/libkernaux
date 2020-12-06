#include "config.h"

#ifdef ARCH_X86
#include <kernaux/arch/x86.h>
#endif

#include <kernaux/console.h>
#include <kernaux/stdlib.h>

void kernaux_console_print(const char *const s)
{
    kernaux_console_write(s, kernaux_strlen(s));
}

void kernaux_console_putc(const char c __attribute__((unused)))
{
#ifdef ARCH_X86
    kernaux_arch_x86_outportb(0x3F8, c);
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
