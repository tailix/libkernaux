#include <stdarg.h>
#include <stdint.h>

#include <kernaux/asm/i386.h>
#include <kernaux/console.h>
#include <kernaux/multiboot2.h>

void poweroff();

static void panic(const char *str);

void main(
    const uint32_t multiboot2_magic,
    const struct KernAux_Multiboot2_Info *const multiboot2_info
) {
    if (multiboot2_magic != KERNAUX_MULTIBOOT2_MAGIC) {
        panic("Multiboot 2 magic number is invalid");
    } else {
        kernaux_console_printf("Multiboot 2 magic number is valid\n");
    }

    if (!KernAux_Multiboot2_Info_is_valid(multiboot2_info)) {
        panic("Multiboot 2 info is invalid");
    } else {
        kernaux_console_printf("Multiboot 2 info is valid\n");
    }

    KernAux_Multiboot2_Info_print(multiboot2_info, kernaux_console_printf);
}

void poweroff()
{
    kernaux_asm_i386_outportw(0x604, 0x2000);
}

void panic(const char *const str)
{
    kernaux_console_printf("panic: %s\n", str);
    kernaux_asm_i386_hang();
}
