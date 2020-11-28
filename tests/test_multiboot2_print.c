#include <assert.h>

#define __USE_POSIX2
#include <stdio.h>

static const char output[] =
    "Multiboot 2 info\n"
    "  size: 864\n"
    "  reserved1: 0\n"
    "Multiboot 2 tag\n"
    "  type: 21 (image load base phys addr)\n"
    "  size: 12\n"
    "  load base addr: 4194304\n"
    "Multiboot 2 tag\n"
    "  type: 1 (boot cmd line)\n"
    "  size: 21\n"
    "  cmdline: hello kernel\n"
    "Multiboot 2 tag\n"
    "  type: 2 (boot loader name)\n"
    "  size: 30\n"
    "  name: GRUB 2.02-2ubuntu8.20\n"
    "Multiboot 2 tag\n"
    "  type: 10 (APM table)\n"
    "  size: 28\n"
    "Multiboot 2 tag\n"
    "  type: 3 (module)\n"
    "  size: 29\n"
    "  start: 1056768\n"
    "  end: 1061532\n"
    "  cmdline: hello module\n"
    "Multiboot 2 tag\n"
    "  type: 3 (module)\n"
    "  size: 17\n"
    "  start: 1064960\n"
    "  end: 1069652\n"
    "  cmdline: \n"
    "Multiboot 2 tag\n"
    "  type: 6 (memory map)\n"
    "  size: 160\n"
    "Multiboot 2 tag\n"
    "  type: 9 (ELF symbols)\n"
    "  size: 420\n"
    "Multiboot 2 tag\n"
    "  type: 4 (basic memory info)\n"
    "  size: 16\n"
    "  mem lower: 639\n"
    "  mem upper: 129920\n"
    "Multiboot 2 tag\n"
    "  type: 5 (BIOS boot device)\n"
    "  size: 20\n"
    "  bios dev: 224\n"
    "  partition: 4294967295\n"
    "  sub_partition: 4294967295\n"
    "Multiboot 2 tag\n"
    "  type: 8 (framebuffer info)\n"
    "  size: 32\n"
    "  framebuffer addr: 753664\n"
    "  framebuffer pitch: 160\n"
    "  framebuffer width: 80\n"
    "  framebuffer height: 25\n"
    "  framebuffer bpp: 16\n"
    "  framebuffer type: 2\n"
    "Multiboot 2 tag\n"
    "  type: 14 (ACPI old RSDP)\n"
    "  size: 28\n"
    "Multiboot 2 tag\n"
    "  type: 0 (none)\n"
    "  size: 8\n";

int main()
{
    FILE *const fd = popen("tests/multiboot2_print", "r");
    assert(fd != NULL);

    for (const char *ch = output; *ch; ++ch) {
        assert(fgetc(fd) == *ch);
    }

    const int status = pclose(fd);
    assert(status == 0);

    return 0;
}
