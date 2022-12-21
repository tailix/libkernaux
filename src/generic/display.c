#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "../assert.h"

#include <kernaux/generic/display.h>

#include <stdarg.h>
#include <stddef.h>

void KernAux_Display_putc(const KernAux_Display display, const char c)
{
    KERNAUX_NOTNULL(display);
    KERNAUX_ASSERT(display->putc);

    // Inherited implementation
    display->putc((void*)display, c);
}

void KernAux_Display_print(const KernAux_Display display, const char *const s)
{
    KERNAUX_NOTNULL(display);
    KERNAUX_ASSERT(display->putc);

    // Default implementation
    for (const char *c = s; *c; ++c) display->putc((void*)display, *c);
}

void KernAux_Display_println(const KernAux_Display display, const char *const s)
{
    KERNAUX_NOTNULL(display);
    KERNAUX_ASSERT(display->putc);

    // Default implementation
    KernAux_Display_print(display, s);
    display->putc((void*)display, '\n');
}

void KernAux_Display_write(
    const KernAux_Display display,
    const char *const data,
    const size_t size
) {
    KERNAUX_NOTNULL(display);
    KERNAUX_ASSERT(display->putc);

    // Default implementation
    for (size_t i = 0; i < size; ++i) display->putc((void*)display, data[i]);
}

void KernAux_Display_writeln(
    const KernAux_Display display,
    const char *const data,
    const size_t size
) {
    KERNAUX_NOTNULL(display);
    KERNAUX_ASSERT(display->putc);

    // Default implementation
    KernAux_Display_write(display, data, size);
    display->putc((void*)display, '\n');
}

void KernAux_Display_printf(
    const KernAux_Display display,
    const char *const format,
    ...
) {
    KERNAUX_NOTNULL(display);

    // Default implementation
    va_list va;
    va_start(va, format);
    KernAux_Display_vprintf(display, format, va);
    va_end(va);
}

void KernAux_Display_printlnf(
    const KernAux_Display display,
    const char *const format,
    ...
) {
    KERNAUX_NOTNULL(display);

    // Default implementation
    va_list va;
    va_start(va, format);
    KernAux_Display_vprintlnf(display, format, va);
    va_end(va);
}

void KernAux_Display_vprintf(
    const KernAux_Display display,
    const char *const format,
    va_list va
) {
    KERNAUX_NOTNULL(display);
    KERNAUX_ASSERT(display->vprintf);

    // Inherited implementation
    display->vprintf((void*)display, format, va);
}

void KernAux_Display_vprintlnf(
    const KernAux_Display display,
    const char *const format,
    va_list va
) {
    KERNAUX_NOTNULL(display);
    KERNAUX_ASSERT(display->putc);

    // Default implementation
    KernAux_Display_vprintf(display, format, va);
    display->putc((void*)display, '\n');
}
