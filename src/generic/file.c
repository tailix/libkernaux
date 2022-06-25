#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/generic/file.h>

#include <stddef.h>

int KernAux_File_putc(KernAux_File file, const int c)
{
    KERNAUX_ASSERT(file);
    KERNAUX_ASSERT(file->putc);

    return file->putc(file, c);
}

int KernAux_File_puts(KernAux_File file, const char *const s)
{
    KERNAUX_ASSERT(file);

    if (file->puts) return file->puts(file, s);

    // Default implementation

    size_t count = 0;
    for (const char *ss = s; *ss; ++ss, ++count) {
        if (KernAux_File_putc(file, *ss) == KERNAUX_EOF) return KERNAUX_EOF;
    }
    const int int_count = count;
    return int_count >= 0 ? int_count : 0;
}
