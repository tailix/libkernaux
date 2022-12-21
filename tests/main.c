#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/runtime.h>

#include <stdio.h>
#include <stdlib.h>

void test_main(int argc, char **argv);

static void assert_cb(
    const char *const file,
    const int line,
    const char *const msg
) {
    fprintf(stderr, "%s:%d:%s\n", file, line, msg);
    abort();
}

int main(int argc, char **argv)
{
    kernaux_assert_cb = assert_cb;
    test_main(argc, argv);
    exit(EXIT_SUCCESS);
}
