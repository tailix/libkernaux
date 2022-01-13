#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/multiboot2.h>

#include <stddef.h>

void KernAux_Multiboot2_Header_print(
    const struct KernAux_Multiboot2_Header *const multiboot2_header,
    void (*const printf)(const char *format, ...) __attribute__((format(printf, 1, 2)))
) {
    printf("Multiboot 2 header\n");
    printf("  magic: %u\n", multiboot2_header->magic);
    printf("  arch: %u\n", multiboot2_header->arch);
    printf("  size: %u\n", multiboot2_header->total_size);
    printf("  checksum: %u\n", multiboot2_header->checksum);

    // TODO: write this
}
