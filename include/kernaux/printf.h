#ifndef KERNAUX_INCLUDED_PRINTF
#define KERNAUX_INCLUDED_PRINTF 1

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

void kernaux_printf(void (*putchar)(char), const char *format, ...)
__attribute__((format(printf, 2, 3)));
void kernaux_printf_va(void (*putchar)(char), const char *format, va_list va);

#ifdef __cplusplus
}
#endif

#endif
