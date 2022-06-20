#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "helper.h"

#include <assert.h>

#ifndef __USE_POSIX2
#define __USE_POSIX2
#endif
#include <stdio.h>

static const char output1[] =
    "Multiboot 2 header\n"
    "  magic: 3897708758\n"
    "  arch: 4 (MIPS32)\n"
    "  size: 24\n"
    "  checksum: 397258510\n"
    "Multiboot 2 header tag\n"
    "  type: 0 (none)\n"
    "  flags: 0\n"
    "  size: 8\n";

static const char output2[] =
    "Multiboot 2 header\n"
    "  magic: 3897708758\n"
    "  arch: 0 (i386)\n"
    "  size: 272\n"
    "  checksum: 397258266\n"
    "Multiboot 2 header tag\n"
    "  type: 1 (information request)\n"
    "  flags: 0\n"
    "  size: 96\n"
    "Multiboot 2 header tag\n"
    "  type: 2 (address)\n"
    "  flags: 0\n"
    "  size: 24\n"
    "Multiboot 2 header tag\n"
    "  type: 3 (entry address)\n"
    "  flags: 0\n"
    "  size: 12\n"
    "Multiboot 2 header tag\n"
    "  type: 4 (flags)\n"
    "  flags: 0\n"
    "  size: 12\n"
    "Multiboot 2 header tag\n"
    "  type: 5 (framebuffer)\n"
    "  flags: 0\n"
    "  size: 20\n"
    "Multiboot 2 header tag\n"
    "  type: 6 (module alignment)\n"
    "  flags: 0\n"
    "  size: 8\n"
    "Multiboot 2 header tag\n"
    "  type: 7 (EFI boot services)\n"
    "  flags: 0\n"
    "  size: 8\n"
    "Multiboot 2 header tag\n"
    "  type: 8 (EFI i386 entry address)\n"
    "  flags: 0\n"
    "  size: 12\n"
    "Multiboot 2 header tag\n"
    "  type: 9 (EFI amd64 entry address)\n"
    "  flags: 0\n"
    "  size: 12\n"
    "Multiboot 2 header tag\n"
    "  type: 10 (relocatable header)\n"
    "  flags: 0\n"
    "  size: 24\n"
    "Multiboot 2 header tag\n"
    "  type: 0 (none)\n"
    "  flags: 0\n"
    "  size: 8\n";

int main()
{
    setup_assert_abort();

    {
        FILE *const fd = popen("./multiboot2_header_print1", "r");
        assert(fd != NULL);

        for (const char *ch = output1; *ch; ++ch) {
            assert(fgetc(fd) == *ch);
        }

        const int status = pclose(fd);
        assert(status == 0);
    }

    {
        FILE *const fd = popen("./multiboot2_header_print2", "r");
        assert(fd != NULL);

        for (const char *ch = output2; *ch; ++ch) {
            assert(fgetc(fd) == *ch);
        }

        const int status = pclose(fd);
        assert(status == 0);
    }

    return 0;
}
