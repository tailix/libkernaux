#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/io.h>

#include <stddef.h>

struct KernAux_OldFile KernAux_OldFile_create(const KernAux_OldFile_Out out)
{
    struct KernAux_OldFile file;
    KernAux_OldFile_init(&file, out);
    return file;
}

void KernAux_OldFile_init(const KernAux_OldFile file, const KernAux_OldFile_Out out)
{
    KERNAUX_ASSERT(file);
    KERNAUX_ASSERT(out);

    file->out = out;
}
