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

void kernaux_console_printf(const char *format, ...)
{
    char **arg = (char **) &format;
    int c;
    char buf[20];
    arg++;

    while ((c = *format++) != 0)
    {
        if (c != '%') {
            kernaux_console_putc(c);
        }
        else {
            char *p, *p2;
            int pad0 = 0, pad = 0;
            c = *format++;
            if (c == '0')
            {
                pad0 = 1;
                c = *format++;
            }
            if (c >= '0' && c <= '9')
            {
                pad = c - '0';
                c = *format++;
            }
            switch (c)
            {
                case 'd':
                case 'u':
                case 'x':
                    kernaux_itoa(*((int*)arg++), buf, c);
                    p = buf;
                    goto string;
                    break;
                case 's':
                    p = *arg++;
                    if (! p)
                        p = "(null)";
string:
                    for (p2 = p; *p2; p2++);
                    for (; p2 < p + pad; p2++)
                        kernaux_console_putc(pad0 ? '0' : ' ');
                    while (*p)
                        kernaux_console_putc(*p++);
                    break;
                default:
                    kernaux_console_putc(*((int *) arg++));
                    break;
            }
        }
    }
}
