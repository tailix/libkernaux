#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/generic/file.h>
#include <kernaux/macro.h>

#include <stdbool.h>
#include <stddef.h>

int KernAux_File_getc(const KernAux_File file)
{
    KERNAUX_ASSERT(file);
    KERNAUX_ASSERT(file->getc);

    return file->getc((void*)file);
}

int KernAux_File_putc(const KernAux_File file, const int c)
{
    KERNAUX_ASSERT(file);
    KERNAUX_ASSERT(file->putc);

    return file->putc((void*)file, c);
}

bool KernAux_File_puts(const KernAux_File file, const char *const s)
{
    KERNAUX_ASSERT(file);

    // Common implementation
    if (!s) return true;

    // Inherited implementation
    if (file->puts) return file->puts((void*)file, s);

    // Default implementation
    for (const char *ss = s; *ss; ++ss) {
        if (KernAux_File_putc(file, *ss) == KERNAUX_EOF) return false;
    }
    return true;
}

bool KernAux_File_read(
    const KernAux_File file,
    void *const buffer,
    size_t *const count
) {
    KERNAUX_ASSERT(file);
    KERNAUX_ASSERT(buffer);
    KERNAUX_ASSERT(count);

    // Common implementation
    if (*count == 0) return true;

    // Inherited implementation
    if (file->read) return file->read((void*)file, buffer, count);

    // Default implementation
    size_t index = 0;
    for (char *ss = buffer; index < *count; ++ss, ++index) {
        const int c = KernAux_File_getc(file);
        if (c == KERNAUX_EOF) {
            *count = index;
            return false;
        }
        *ss = c;
    }
    *count = index;
    return true;
}

bool KernAux_File_write(
    const KernAux_File file,
    const void *const buffer,
    const size_t count
) {
    KERNAUX_ASSERT(file);
    KERNAUX_ASSERT(buffer);

    // Common implementation
    if (count == 0) return true;

    // Inherited implementation
    if (file->write) return file->write((void*)file, buffer, count);

    // Default implementation
    size_t index = 0;
    for (const char *ss = buffer; index < count; ++ss, ++index) {
        if (KernAux_File_putc(file, *ss) == KERNAUX_EOF) return false;
    }
    return true;
}

void KernAux_File_rewind(const KernAux_File file)
{
    KERNAUX_ASSERT(file);
    KERNAUX_ASSERT(file->rewind);

    file->rewind((void*)file);
}
