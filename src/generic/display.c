#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/generic/display.h>

#include <stdarg.h>
#include <stddef.h>

void KernAux_Display_putc(const KernAux_Display display, const char c)
{
    KERNAUX_ASSERT(display);
    KERNAUX_ASSERT(display->putc);

    // Inherited implementation
    display->putc((void*)display, c);
}

void KernAux_Display_print(const KernAux_Display display, const char *const s)
{
    KERNAUX_ASSERT(display);
    KERNAUX_ASSERT(display->putc);

    // Default implementation
    for (const char *c = s; *c; ++c) display->putc((void*)display, *c);
}

void KernAux_Display_println(const KernAux_Display display, const char *const s)
{
    KERNAUX_ASSERT(display);
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
    KERNAUX_ASSERT(display);
    KERNAUX_ASSERT(display->putc);

    // Default implementation
    for (size_t i = 0; i < size; ++i) display->putc((void*)display, data[i]);
}

void KernAux_Display_writeln(
    const KernAux_Display display,
    const char *const data,
    const size_t size
) {
    KERNAUX_ASSERT(display);
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
    KERNAUX_ASSERT(display);
    KERNAUX_ASSERT(display->printf);

    // Inherited implementation
    va_list va;
    va_start(va, format);
    display->printf((void*)display, format, va);
    va_end(va);
}

void KernAux_Display_printlnf(
    const KernAux_Display display,
    const char *const format,
    ...
) {
    KERNAUX_ASSERT(display);
    KERNAUX_ASSERT(display->putc);

    // Default implementation
    va_list va;
    va_start(va, format);
    KernAux_Display_printf(display, format, va);
    va_end(va);
    display->putc((void*)display, '\n');
}
