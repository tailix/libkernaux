#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>

#include <stddef.h>

void (*kernaux_assert_cb)(const char *file, int line, const char *str) = NULL;

void kernaux_assert_do(
    const char *const file,
    const int line,
    const char *const str
) {
    if (kernaux_assert_cb) kernaux_assert_cb(file, line, str);
}
