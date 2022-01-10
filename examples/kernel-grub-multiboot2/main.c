#include <stdarg.h>
#include <stdint.h>

#include <kernaux/asm/i386.h>
#include <kernaux/drivers/console.h>
#include <kernaux/multiboot2.h>

void halt();

static void panic(const char *str);

void main(
    const uint32_t multiboot2_magic,
    const struct KernAux_Multiboot2 *const multiboot2_info
) {
    if (multiboot2_magic != KERNAUX_MULTIBOOT2_MAGIC) {
        panic("Multiboot 2 magic number is invalid");
    }

    if (!KernAux_Multiboot2_is_valid(multiboot2_info)) {
        panic("Multiboot 2 info is invalid");
    }

    KernAux_Multiboot2_print(multiboot2_info, kernaux_console_printf);
}

void halt()
{
    panic("Kernel main function returned");
}

void panic(const char *const str)
{
    kernaux_console_printf("panic: %s\n", str);
    kernaux_asm_i386_hang();
}
