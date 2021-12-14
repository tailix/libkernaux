#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>

#include <stddef.h>

void (*kernaux_assert_cb)(const char *file, int line, const char *str) = NULL;

void kernaux_assert_do(
#ifndef ENABLE_ASSERT
    __attribute__((unused))
#endif
    const char *const file,
#ifndef ENABLE_ASSERT
    __attribute__((unused))
#endif
    const int line,
#ifndef ENABLE_ASSERT
    __attribute__((unused))
#endif
    const char *const str
) {
#ifdef ENABLE_ASSERT
    if (kernaux_assert_cb) kernaux_assert_cb(file, line, str);
#endif
}
