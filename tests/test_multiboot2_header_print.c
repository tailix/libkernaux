#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <assert.h>

#define __USE_POSIX2
#include <stdio.h>

static const char output1[] = "";
static const char output2[] = "";

int main()
{
    {
        FILE *const fd = popen("tests/multiboot2_header_print1", "r");
        assert(fd != NULL);

        for (const char *ch = output1; *ch; ++ch) {
            assert(fgetc(fd) == *ch);
        }

        const int status = pclose(fd);
        assert(status == 0);
    }

    {
        FILE *const fd = popen("tests/multiboot2_header_print2", "r");
        assert(fd != NULL);

        for (const char *ch = output2; *ch; ++ch) {
            assert(fgetc(fd) == *ch);
        }

        const int status = pclose(fd);
        assert(status == 0);
    }

    return 0;
}
