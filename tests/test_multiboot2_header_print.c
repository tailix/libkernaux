#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <assert.h>

#ifndef __USE_POSIX2
#define __USE_POSIX2
#endif
#include <stdio.h>

static const char output1[] =
    "Multiboot 2 header\n"
    "  magic: 3897708758\n"
    "  arch: 4 (MIPS32)\n"
    "  size: 88\n"
    "  checksum: 397258446\n"
    "Multiboot 2 header tag\n"
    "  type: 4 (flags)\n"
    "  flags: 0\n"
    "  size: 12\n"
    "  console flags: 0 ()\n"
    "Multiboot 2 header tag\n"
    "  type: 4 (flags)\n"
    "  flags: 0\n"
    "  size: 12\n"
    "  console flags: 1 (\n"
    "    REQUIRE_CONSOLE\n"
    "  )\n"
    "Multiboot 2 header tag\n"
    "  type: 4 (flags)\n"
    "  flags: 0\n"
    "  size: 12\n"
    "  console flags: 2 (\n"
    "    EGA_SUPPORT\n"
    "  )\n"
    "Multiboot 2 header tag\n"
    "  type: 4 (flags)\n"
    "  flags: 0\n"
    "  size: 12\n"
    "  console flags: 3 (\n"
    "    REQUIRE_CONSOLE |\n"
    "    EGA_SUPPORT\n"
    "  )\n"
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
    "  mbi_tag_types:\n"
    "    0 (none)\n"
    "    1 (boot cmd line)\n"
    "    2 (boot loader name)\n"
    "    3 (module)\n"
    "    4 (basic memory info)\n"
    "    5 (BIOS boot device)\n"
    "    6 (memory map)\n"
    "    7 (VBE info)\n"
    "    8 (framebuffer info)\n"
    "    9 (ELF symbols)\n"
    "    10 (APM table)\n"
    "    11 (EFI 32bit system table ptr)\n"
    "    12 (EFI 64bit system table ptr)\n"
    "    13 (SMBIOS tables)\n"
    "    14 (ACPI old RSDP)\n"
    "    15 (ACPI new RSDP)\n"
    "    16 (networking info)\n"
    "    17 (EFI memory map)\n"
    "    18 (EFI boot services not terminated)\n"
    "    19 (EFI 32bit image handle ptr)\n"
    "    20 (EFI 64bit image handle ptr)\n"
    "    21 (image load base phys addr)\n"
    "Multiboot 2 header tag\n"
    "  type: 2 (address)\n"
    "  flags: 0\n"
    "  size: 24\n"
    "  header addr: 3405691582\n"
    "  load addr: 3735928495\n"
    "  load end addr: 3735927486\n"
    "  bss end addr: 3405692591\n"
    "Multiboot 2 header tag\n"
    "  type: 3 (entry address)\n"
    "  flags: 0\n"
    "  size: 12\n"
    "  entry addr: 3405691582\n"
    "Multiboot 2 header tag\n"
    "  type: 4 (flags)\n"
    "  flags: 0\n"
    "  size: 12\n"
    "  console flags: 0 ()\n"
    "Multiboot 2 header tag\n"
    "  type: 5 (framebuffer)\n"
    "  flags: 0\n"
    "  size: 20\n"
    "  width: 80\n"
    "  height: 25\n"
    "  depth: 8\n"
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
    "  entry addr: 3405691582\n"
    "Multiboot 2 header tag\n"
    "  type: 9 (EFI amd64 entry address)\n"
    "  flags: 0\n"
    "  size: 12\n"
    "  entry addr: 3735928495\n"
    "Multiboot 2 header tag\n"
    "  type: 10 (relocatable header)\n"
    "  flags: 0\n"
    "  size: 24\n"
    "  min addr: 3405691582\n"
    "  max addr: 3735928495\n"
    "  align: 8\n"
    "Multiboot 2 header tag\n"
    "  type: 0 (none)\n"
    "  flags: 0\n"
    "  size: 8\n";

void test_main()
{
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
}
