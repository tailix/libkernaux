#include <stdarg.h>
#include <stdint.h>

#include <kernaux/drivers/console.h>
#include <kernaux/drivers/shutdown.h>
#include <kernaux/multiboot2.h>

extern const struct KernAux_Multiboot2_Header multiboot2_header;

static void panic(const char *str);

void main(
    const uint32_t multiboot2_info_magic,
    const struct KernAux_Multiboot2_Info *const multiboot2_info
) {
    if (!KernAux_Multiboot2_Header_is_valid(&multiboot2_header)) {
        panic("Multiboot 2 header is invalid");
    } else {
        kernaux_drivers_console_printf("Multiboot 2 header is valid\n");
    }

    KernAux_Multiboot2_Header_print(
        &multiboot2_header,
        kernaux_drivers_console_printf
    );

    if (multiboot2_info_magic != KERNAUX_MULTIBOOT2_INFO_MAGIC) {
        panic("Multiboot 2 info magic number is invalid");
    } else {
        kernaux_drivers_console_printf(
            "Multiboot 2 info magic number is valid\n"
        );
    }

    if (!KernAux_Multiboot2_Info_is_valid(multiboot2_info)) {
        panic("Multiboot 2 info is invalid");
    } else {
        kernaux_drivers_console_printf("Multiboot 2 info is valid\n");
    }

    KernAux_Multiboot2_Info_print(
        multiboot2_info,
        kernaux_drivers_console_printf
    );
}

void panic(const char *const str)
{
    kernaux_drivers_console_printf("panic: %s\n", str);
    kernaux_drivers_shutdown_poweroff();
}
