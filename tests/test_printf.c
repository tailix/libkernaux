#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/printf.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_main()
{
    char buffer[1000];

    // Sanity check
    {
        memset(buffer, 0xff, sizeof(buffer));
        const int result =
            kernaux_snprintf(buffer, sizeof(buffer), "%s", "Hello, World!");
        fprintf(stderr, "%d:%s\n", result, buffer);
        assert(result == 13);
        assert(strcmp(buffer, "Hello, World!") == 0);
    }

    // i386 requires "(long long)0" instead of just "0"
    {
        memset(buffer, 0xff, sizeof(buffer));
        const int result =
            kernaux_snprintf(buffer, sizeof(buffer), "%#.0llx", (long long)0);
        fprintf(stderr, "%d:%s\n", result, buffer);
        assert(result == 0);
        assert(strcmp(buffer, "") == 0);
    }
}
