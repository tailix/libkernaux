#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/generic/file.h>

int KernAux_File_putc(KernAux_File file, int c)
{
    KERNAUX_ASSERT(file);
    KERNAUX_ASSERT(file->putc);

    return file->putc(file, c);
}
