#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>

#include <stdio.h>
#include <stdlib.h>

static void assert_cb_abort(const char *file, int line, const char *msg);

void setup_assert_abort()
{
    kernaux_assert_cb = assert_cb_abort;
}

void assert_cb_abort(
    const char *const file,
    const int line,
    const char *const msg
) {
    fprintf(stderr, "%s:%d:%s\n", file, line, msg);
    abort();
}
