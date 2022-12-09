#ifndef KERNAUX_INCLUDED_DISPLAY
#define KERNAUX_INCLUDED_DISPLAY

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>

#include <stdarg.h>
#include <stddef.h>

typedef void (*KernAux_Display_Putc   )(void *display, char c);
typedef void (*KernAux_Display_Vprintf)(void *display, const char *format, va_list va);

typedef const struct KernAux_Display {
    KernAux_Display_Putc    KERNAUX_PROTECTED_FIELD(putc);
    KernAux_Display_Vprintf KERNAUX_PROTECTED_FIELD(vprintf);
} *KernAux_Display;

void KernAux_Display_putc     (KernAux_Display display, char c);
void KernAux_Display_print    (KernAux_Display display, const char *s);
void KernAux_Display_println  (KernAux_Display display, const char *s);
void KernAux_Display_write    (KernAux_Display display, const char *data, size_t size);
void KernAux_Display_writeln  (KernAux_Display display, const char *data, size_t size);
KERNAUX_PRINTF(2, 3)
void KernAux_Display_printf   (KernAux_Display display, const char *format, ...);
KERNAUX_PRINTF(2, 3)
void KernAux_Display_printlnf (KernAux_Display display, const char *format, ...);
void KernAux_Display_vprintf  (KernAux_Display display, const char *format, va_list va);
void KernAux_Display_vprintlnf(KernAux_Display display, const char *format, va_list va);

#ifdef __cplusplus
}
#endif

#endif
