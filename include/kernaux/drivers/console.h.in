#ifndef KERNAUX_INCLUDED_DRIVERS_CONSOLE
#define KERNAUX_INCLUDED_DRIVERS_CONSOLE

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

void kernaux_drivers_console_putc(char c);

void kernaux_drivers_console_print(const char *s);
@comment_line_printf@void kernaux_drivers_console_printf(const char *format, ...)
@comment_line_printf@__attribute__((format(printf, 1, 2)));
void kernaux_drivers_console_puts(const char *s);
void kernaux_drivers_console_write(const char *data, size_t size);

#ifdef __cplusplus
}
#endif

#endif
