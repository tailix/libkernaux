#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <assert.h>

#define __USE_POSIX2
#include <stdio.h>

// static const char output1[] = "";

// TODO: add more tags
static const char output2[] =
    "Multiboot 2 header\n"
    "  magic: 920085129\n"
    "  arch: 1\n"
    "  size: 120\n"
    "  checksum: 3374882046\n"
    "Multiboot 2 header tag\n"
    "  type: 1 (information request)\n"
    "  flags: 0\n"
    "  size: 96\n"
    "Multiboot 2 header tag\n"
    "  type: 0 (none)\n"
    "  flags: 0\n"
    "  size: 8\n";

int main()
{
    /*
    {
        FILE *const fd = popen("tests/multiboot2_header_print1", "r");
        assert(fd != NULL);

        for (const char *ch = output1; *ch; ++ch) {
            assert(fgetc(fd) == *ch);
        }

        const int status = pclose(fd);
        assert(status == 0);
    }
    */

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
