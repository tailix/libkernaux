#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/runtime.h>

#include <stdio.h>
#include <stdlib.h>

void example_main();

static void assert_cb(
    const char *const file,
    const int line,
    const char *const msg
) {
    fprintf(stderr, "%s:%d:%s\n", file, line, msg);
    abort();
}

int main()
{
    kernaux_assert_cb = assert_cb;
    example_main();
    exit(EXIT_SUCCESS);
}
