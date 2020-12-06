#ifndef KERNAUX_INCLUDED_CONSOLE
#define KERNAUX_INCLUDED_CONSOLE 1

#ifdef __cplusplus
extern "C" {
#endif

void kernaux_console_print(const char *s);
void kernaux_console_printf(const char *format, ...)
__attribute__((format(printf, 1, 2)));
void kernaux_console_putc(char c);
void kernaux_console_puts(const char *s);
void kernaux_console_write(const char *data, unsigned int size);

#ifdef __cplusplus
}
#endif

#endif
