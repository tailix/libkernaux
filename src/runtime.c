#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/runtime.h>

#include <stddef.h>

KernAux_Assert_Cb kernaux_assert_cb = NULL;

void kernaux_assert_do(
    const char *const file,
    const int line,
    const char *const msg
) {
    if (kernaux_assert_cb) kernaux_assert_cb(file, line, msg);
}
