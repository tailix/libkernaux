#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <assert.h>

#ifndef __USE_POSIX2
#define __USE_POSIX2
#endif
#include <stdio.h>

static const char output0[] =
    "Multiboot 2 header {\n"
    "  u32 magic: 0xe85250d6\n"
    "  u32 arch: 0 (i386)\n"
    "  u32 size: 24\n"
    "  u32 checksum: 0x17adaf12\n"
    "}\n"
    "Multiboot 2 header tag {\n"
    "  u16 type: 0 (none)\n"
    "  u16 flags: 0x0 ()\n"
    "  u32 size: 8\n"
    "}\n";

static const char output1[] =
    "Multiboot 2 header {\n"
    "  u32 magic: 0xe85250d6\n"
    "  u32 arch: 4 (MIPS32)\n"
    "  u32 size: 104\n"
    "  u32 checksum: 0x17adaebe\n"
    "}\n"
    "Multiboot 2 header tag {\n"
    "  u16 type: 4 (flags)\n"
    "  u16 flags: 0x0 ()\n"
    "  u32 size: 12\n"
    "  u32 console_flags: 0x0 ()\n"
    "}\n"
    "Multiboot 2 header tag {\n"
    "  u16 type: 4 (flags)\n"
    "  u16 flags: 0x0 ()\n"
    "  u32 size: 12\n"
    "  u32 console_flags: 0x1 (\n"
    "    REQUIRE_CONSOLE\n"
    "  )\n"
    "}\n"
    "Multiboot 2 header tag {\n"
    "  u16 type: 4 (flags)\n"
    "  u16 flags: 0x0 ()\n"
    "  u32 size: 12\n"
    "  u32 console_flags: 0x2 (\n"
    "    EGA_SUPPORT\n"
    "  )\n"
    "}\n"
    "Multiboot 2 header tag {\n"
    "  u16 type: 4 (flags)\n"
    "  u16 flags: 0x0 ()\n"
    "  u32 size: 12\n"
    "  u32 console_flags: 0x3 (\n"
    "    REQUIRE_CONSOLE |\n"
    "    EGA_SUPPORT\n"
    "  )\n"
    "}\n"
    "Multiboot 2 header tag {\n"
    "  u16 type: 1 (information request)\n"
    "  u16 flags: 0x1 (\n"
    "    OPTIONAL\n"
    "  )\n"
    "  u32 size: 12\n"
    "  u32 mbi_tag_types[]: [\n"
    "    0 (none)\n"
    "  ]\n"
    "}\n"
    "Multiboot 2 header tag {\n"
    "  u16 type: 0 (none)\n"
    "  u16 flags: 0x0 ()\n"
    "  u32 size: 8\n"
    "}\n";

static const char output2[] =
    "Multiboot 2 header {\n"
    "  u32 magic: 0xe85250d6\n"
    "  u32 arch: 0 (i386)\n"
    "  u32 size: 272\n"
    "  u32 checksum: 0x17adae1a\n"
    "}\n"
    "Multiboot 2 header tag {\n"
    "  u16 type: 1 (information request)\n"
    "  u16 flags: 0x0 ()\n"
    "  u32 size: 96\n"
    "  u32 mbi_tag_types[]: [\n"
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
    "  ]\n"
    "}\n"
    "Multiboot 2 header tag {\n"
    "  u16 type: 2 (address)\n"
    "  u16 flags: 0x0 ()\n"
    "  u32 size: 24\n"
    "  u32 header_addr: 0xcafebabe\n"
    "  u32 load_addr: 0xdeadbeaf\n"
    "  u32 load_end_addr: 0xdeadbabe\n"
    "  u32 bss_end_addr: 0xcafebeaf\n"
    "}\n"
    "Multiboot 2 header tag {\n"
    "  u16 type: 3 (entry address)\n"
    "  u16 flags: 0x0 ()\n"
    "  u32 size: 12\n"
    "  u32 entry_addr: 0xcafebabe\n"
    "}\n"
    "Multiboot 2 header tag {\n"
    "  u16 type: 4 (flags)\n"
    "  u16 flags: 0x0 ()\n"
    "  u32 size: 12\n"
    "  u32 console_flags: 0x0 ()\n"
    "}\n"
    "Multiboot 2 header tag {\n"
    "  u16 type: 5 (framebuffer)\n"
    "  u16 flags: 0x0 ()\n"
    "  u32 size: 20\n"
    "  u32 width: 80\n"
    "  u32 height: 25\n"
    "  u32 depth: 8\n"
    "}\n"
    "Multiboot 2 header tag {\n"
    "  u16 type: 6 (module alignment)\n"
    "  u16 flags: 0x0 ()\n"
    "  u32 size: 8\n"
    "}\n"
    "Multiboot 2 header tag {\n"
    "  u16 type: 7 (EFI boot services)\n"
    "  u16 flags: 0x0 ()\n"
    "  u32 size: 8\n"
    "}\n"
    "Multiboot 2 header tag {\n"
    "  u16 type: 8 (EFI i386 entry address)\n"
    "  u16 flags: 0x0 ()\n"
    "  u32 size: 12\n"
    "  u32 entry_addr: 0xcafebabe\n"
    "}\n"
    "Multiboot 2 header tag {\n"
    "  u16 type: 9 (EFI amd64 entry address)\n"
    "  u16 flags: 0x0 ()\n"
    "  u32 size: 12\n"
    "  u32 entry_addr: 0xdeadbeaf\n"
    "}\n"
    "Multiboot 2 header tag {\n"
    "  u16 type: 10 (relocatable header)\n"
    "  u16 flags: 0x0 ()\n"
    "  u32 size: 24\n"
    "  u32 min_addr: 0xcafebabe\n"
    "  u32 max_addr: 0xdeadbeaf\n"
    "  u32 align: 8\n"
    "  u32 preference: 1 (lowest)\n"
    "}\n"
    "Multiboot 2 header tag {\n"
    "  u16 type: 0 (none)\n"
    "  u16 flags: 0x0 ()\n"
    "  u32 size: 8\n"
    "}\n";

void test_main()
{
    {
        FILE *const fd = popen("./multiboot2_header_print0", "r");
        assert(fd != NULL);

        for (const char *ch = output0; *ch; ++ch) {
            assert(fgetc(fd) == *ch);
        }

        const int status = pclose(fd);
        assert(status == 0);
    }

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
