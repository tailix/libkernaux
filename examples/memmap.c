#define KERNAUX_ACCESS_PROTECTED

#include <kernaux/free_list.h>
#include <kernaux/generic/display.h>
#include <kernaux/macro.h>
#include <kernaux/memmap.h>

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

static char malloc_memory[8192];

static void my_putc(void *const display KERNAUX_UNUSED, const char c)
{
    putchar(c);
}

static void my_vprintf(
    void *const display KERNAUX_UNUSED,
    const char *const format,
    va_list va
) {
    vprintf(format, va);
}

static const struct KernAux_Display display = {
    .putc = my_putc,
    .vprintf = my_vprintf,
};

void example_main()
{
    struct KernAux_FreeList malloc = KernAux_FreeList_create(NULL);
    KernAux_FreeList_add_zone(&malloc, malloc_memory, sizeof(malloc_memory));

    KernAux_Memmap_Builder memmap_builder =
        KernAux_Memmap_Builder_new(&malloc.malloc);
    assert(memmap_builder);

    assert(KernAux_Memmap_Builder_add(memmap_builder, NULL,        0x0,        654336,    "available"));
    assert(KernAux_Memmap_Builder_add(memmap_builder, NULL,        0x9fc00,    1024,      "reserved"));
    assert(KernAux_Memmap_Builder_add(memmap_builder, NULL,        0xf0000,    65536,     "reserved"));
    KernAux_Memmap_Node kernel_node =
        KernAux_Memmap_Builder_add   (memmap_builder, NULL,        0x100000,   133038080, "available");
    assert(kernel_node);
    assert(KernAux_Memmap_Builder_add(memmap_builder, NULL,        0x7fe0000,  131072,    "reserved"));
    assert(KernAux_Memmap_Builder_add(memmap_builder, NULL,        0xfffc0000, 262144,    "reserved"));

    assert(KernAux_Memmap_Builder_add(memmap_builder, kernel_node, 0x400000,   8192,      "kernel code"));
    assert(KernAux_Memmap_Builder_add(memmap_builder, kernel_node, 0x402000,   4096,      "kernel data"));

    KernAux_Memmap memmap =
        KernAux_Memmap_Builder_finish_and_free(memmap_builder);
    assert(memmap);

    KernAux_Memmap_print(memmap, &display);

    KERNAUX_MEMMAP_FREE(memmap);
}
