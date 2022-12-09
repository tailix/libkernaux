#ifndef KERNAUX_INCLUDED_FORMATTER
#define KERNAUX_INCLUDED_FORMATTER

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>

#include <stddef.h>

typedef void (*KernAux_Formatter_Putc  )(void *formatter, char c);
typedef void (*KernAux_Formatter_Printf)(void *formatter, const char *format, ...) KERNAUX_PRINTF(2, 3);

typedef const struct KernAux_Formatter {
    KernAux_Formatter_Putc   KERNAUX_PROTECTED_FIELD(putc);
    KernAux_Formatter_Printf KERNAUX_PROTECTED_FIELD(printf);
} *KernAux_Formatter;

void KernAux_Formatter_putc    (KernAux_Formatter formatter, char c);
void KernAux_Formatter_print   (KernAux_Formatter formatter, const char *s);
void KernAux_Formatter_println (KernAux_Formatter formatter, const char *s);
void KernAux_Formatter_write   (KernAux_Formatter formatter, const char *data, size_t size);
void KernAux_Formatter_writeln (KernAux_Formatter formatter, const char *data, size_t size);
void KernAux_Formatter_printf  (KernAux_Formatter formatter, const char *format, ...);
void KernAux_Formatter_printlnf(KernAux_Formatter formatter, const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif
