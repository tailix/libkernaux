#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/libc.h>

#include <stddef.h>

struct KernAux_Libc kernaux_libc = {
    .abort = NULL,
    .exit = NULL,

    .calloc = NULL,
    .free = NULL,
    .malloc = NULL,
    .realloc = NULL,
};
