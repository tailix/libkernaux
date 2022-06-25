#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/generic/file.h>

#include <stddef.h>

int KernAux_File_putc(const KernAux_File file, const int c)
{
    KERNAUX_ASSERT(file);
    KERNAUX_ASSERT(file->putc);

    return file->putc((void*)file, c);
}

int KernAux_File_puts(const KernAux_File file, const char *const s)
{
    KERNAUX_ASSERT(file);

    // Common implementation
    if (!s) return 0;

    // Inherited implementation
    if (file->puts) return file->puts((void*)file, s);

    // Default implementation
    size_t ccount = 0;
    for (const char *ss = s; *ss; ++ss, ++ccount) {
        if (KernAux_File_putc(file, *ss) == KERNAUX_EOF) return KERNAUX_EOF;
    }
    const int icount = ccount;
    return icount >= 0 ? icount : 0;
}

int KernAux_File_write(
    const KernAux_File file,
    const void *const buffer,
    const size_t count
) {
    KERNAUX_ASSERT(file);

    // Common implementation
    if (count == 0 || !buffer) return 0;

    // Inherited implementation
    if (file->write) return file->write((void*)file, buffer, count);

    // Default implementation
    size_t ccount = 0;
    for (const char *ss = buffer; ccount < count; ++ss, ++ccount) {
        if (KernAux_File_putc(file, *ss) == KERNAUX_EOF) return KERNAUX_EOF;
    }
    const int icount = ccount;
    return icount >= 0 ? icount : 0;
}
