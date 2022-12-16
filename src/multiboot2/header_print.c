#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/generic/display.h>
#include <kernaux/macro.h>
#include <kernaux/multiboot2.h>

#include <stddef.h>
#include <stdint.h>

#define PRINTLN(s) do { KernAux_Display_println(display, s); } while (0)

#define PRINTF(format, ...) \
    do { KernAux_Display_printf(display, format, __VA_ARGS__); } while (0)
#define PRINTLNF(format, ...) \
    do { KernAux_Display_printlnf(display, format, __VA_ARGS__); } while (0)

#define HEADER(Type) do { \
    KERNAUX_ASSERT(tag);                                                       \
    KERNAUX_ASSERT(display);                                                   \
                                                                               \
    if (!KernAux_Multiboot2_HTag_##Type##_is_valid(tag)) return;               \
                                                                               \
    KERNAUX_CAST_CONST(unsigned long, flags, tag->base.flags);                 \
    KERNAUX_CAST_CONST(unsigned long, size,  tag->base.size);                  \
                                                                               \
    PRINTLN("Multiboot 2 header tag");                                         \
    PRINTLNF("  type: %u (%s)",                                                \
        tag->base.type,                                                        \
        KernAux_Multiboot2_HTag_to_str(tag->base.type)                         \
    );                                                                         \
    PRINTLNF("  flags: %lu", flags);                                           \
    PRINTLNF("  size: %lu", size);                                             \
} while (0)

void KernAux_Multiboot2_Header_print(
    const struct KernAux_Multiboot2_Header *const multiboot2_header,
    const KernAux_Display display
) {
    KERNAUX_ASSERT(multiboot2_header);
    KERNAUX_ASSERT(display);

    KERNAUX_CAST_CONST(unsigned long, magic,      multiboot2_header->magic);
    KERNAUX_CAST_CONST(unsigned long, total_size, multiboot2_header->total_size);
    KERNAUX_CAST_CONST(unsigned long, checksum,   multiboot2_header->checksum);

    PRINTLN("Multiboot 2 header");
    PRINTLNF("  magic: %lu", magic);
    PRINTLNF("  arch: %u (%s)",
        multiboot2_header->arch,
        KernAux_Multiboot2_Header_Arch_to_str(multiboot2_header->arch)
    );
    PRINTLNF("  size: %lu", total_size);
    PRINTLNF("  checksum: %lu", checksum);

    const struct KernAux_Multiboot2_HTagBase *tag_base =
        (struct KernAux_Multiboot2_HTagBase*)
        KERNAUX_MULTIBOOT2_DATA(multiboot2_header);

    while (tag_base <
           (struct KernAux_Multiboot2_HTagBase*)
           ((uint8_t*)multiboot2_header + multiboot2_header->total_size))
    {
        if (!KernAux_Multiboot2_HTagBase_is_valid(tag_base)) return;
        KernAux_Multiboot2_HTagBase_print(tag_base, display);
        tag_base = KERNAUX_MULTIBOOT2_HTAG_NEXT(tag_base);
    }
}

void KernAux_Multiboot2_HTagBase_print(
    const struct KernAux_Multiboot2_HTagBase *const tag_base,
    const KernAux_Display display
) {
    KERNAUX_ASSERT(tag_base);
    KERNAUX_ASSERT(display);

    switch (tag_base->type) {
    case KERNAUX_MULTIBOOT2_HTAG_NONE:
        KernAux_Multiboot2_HTag_None_print(
            (struct KernAux_Multiboot2_HTag_None*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_HTAG_INFO_REQ:
        KernAux_Multiboot2_HTag_InfoReq_print(
            (struct KernAux_Multiboot2_HTag_InfoReq*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_HTAG_ADDR:
        KernAux_Multiboot2_HTag_Addr_print(
            (struct KernAux_Multiboot2_HTag_Addr*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_HTAG_ENTRY_ADDR:
        KernAux_Multiboot2_HTag_EntryAddr_print(
            (struct KernAux_Multiboot2_HTag_EntryAddr*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_HTAG_FLAGS:
        KernAux_Multiboot2_HTag_Flags_print(
            (struct KernAux_Multiboot2_HTag_Flags*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_HTAG_FRAMEBUFFER:
        KernAux_Multiboot2_HTag_Framebuffer_print(
            (struct KernAux_Multiboot2_HTag_Framebuffer*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_HTAG_MODULE_ALIGN:
        KernAux_Multiboot2_HTag_ModuleAlign_print(
            (struct KernAux_Multiboot2_HTag_ModuleAlign*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_HTAG_EFI_BOOT_SERVICES:
        KernAux_Multiboot2_HTag_EFIBootServices_print(
            (struct KernAux_Multiboot2_HTag_EFIBootServices*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_HTAG_EFI_I386_ENTRY_ADDR:
        KernAux_Multiboot2_HTag_EFII386EntryAddr_print(
            (struct KernAux_Multiboot2_HTag_EFII386EntryAddr*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_HTAG_EFI_AMD64_ENTRY_ADDR:
        KernAux_Multiboot2_HTag_EFIAmd64EntryAddr_print(
            (struct KernAux_Multiboot2_HTag_EFIAmd64EntryAddr*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_HTAG_RELOCATABLE_HEADER:
        KernAux_Multiboot2_HTag_RelocatableHeader_print(
            (struct KernAux_Multiboot2_HTag_RelocatableHeader*)tag_base,
            display
        );
        break;
    }
}

void KernAux_Multiboot2_HTag_None_print(
    const struct KernAux_Multiboot2_HTag_None *const tag,
    const KernAux_Display display
) {
    HEADER(None);
}

void KernAux_Multiboot2_HTag_InfoReq_print(
    const struct KernAux_Multiboot2_HTag_InfoReq *const tag,
    const KernAux_Display display
) {
    HEADER(InfoReq);

    // Print data:

    PRINTLN("  mbi_tag_types:");

    const uint32_t *const mbi_tag_types =
        (const uint32_t*)KERNAUX_MULTIBOOT2_DATA(tag);

    for (
        size_t index = 0;
        index < (tag->base.size - sizeof(*tag)) / sizeof(uint32_t);
        ++index
    ) {
        KERNAUX_CAST_CONST(unsigned long, type, mbi_tag_types[index]);

        PRINTLNF("    %lu (%s)",
            type,
            KernAux_Multiboot2_ITag_to_str(type)
        );
    }
}

void KernAux_Multiboot2_HTag_Addr_print(
    const struct KernAux_Multiboot2_HTag_Addr *const tag,
    const KernAux_Display display
) {
    HEADER(Addr);

    KERNAUX_CAST_CONST(unsigned long, header_addr,   tag->header_addr);
    KERNAUX_CAST_CONST(unsigned long, load_addr,     tag->load_addr);
    KERNAUX_CAST_CONST(unsigned long, load_end_addr, tag->load_end_addr);
    KERNAUX_CAST_CONST(unsigned long, bss_end_addr,  tag->bss_end_addr);

    PRINTLNF("  header addr: %lu",   header_addr);
    PRINTLNF("  load addr: %lu",     load_addr);
    PRINTLNF("  load end addr: %lu", load_end_addr);
    PRINTLNF("  bss end addr: %lu",  bss_end_addr);
}

void KernAux_Multiboot2_HTag_EntryAddr_print(
    const struct KernAux_Multiboot2_HTag_EntryAddr *const tag,
    const KernAux_Display display
) {
    HEADER(EntryAddr);

    KERNAUX_CAST_CONST(unsigned long, entry_addr, tag->entry_addr);

    PRINTLNF("  entry addr: %lu", entry_addr);
}

void KernAux_Multiboot2_HTag_Flags_print(
    const struct KernAux_Multiboot2_HTag_Flags *const tag,
    const KernAux_Display display
) {
    HEADER(Flags);

    KERNAUX_CAST_CONST(unsigned long, console_flags, tag->console_flags);

    PRINTF("  console flags: %lu (", console_flags);

    static const struct {
        uint32_t number;
        const char *name;
    } flags[] = {
        {
            .number = KERNAUX_MULTIBOOT2_HTAG_FLAGS_REQUIRE_CONSOLE,
            .name = "REQUIRE_CONSOLE",
        },
        {
            .number = KERNAUX_MULTIBOOT2_HTAG_FLAGS_EGA_SUPPORT,
            .name = "EGA_SUPPORT",
        }
    };

    bool is_first = true;
    for (size_t index = 0; index < sizeof(flags) / sizeof(flags[0]); ++index) {
        if (tag->console_flags & flags[index].number) {
            if (is_first) {
                PRINTLN("");
            } else {
                PRINTLN(" |");
            }
            PRINTF("    %s", flags[index].name);
            is_first = false;
        }
    }
    if (is_first) {
        PRINTLN(")");
    } else {
        PRINTLN("");
        PRINTLN("  )");
    }
}

void KernAux_Multiboot2_HTag_Framebuffer_print(
    const struct KernAux_Multiboot2_HTag_Framebuffer *const tag,
    const KernAux_Display display
) {
    HEADER(Framebuffer);

    // TODO: print
}

void KernAux_Multiboot2_HTag_ModuleAlign_print(
    const struct KernAux_Multiboot2_HTag_ModuleAlign *const tag,
    const KernAux_Display display
) {
    HEADER(ModuleAlign);
}

void KernAux_Multiboot2_HTag_EFIBootServices_print(
    const struct KernAux_Multiboot2_HTag_EFIBootServices *const tag,
    const KernAux_Display display
) {
    HEADER(EFIBootServices);
}

void KernAux_Multiboot2_HTag_EFII386EntryAddr_print(
    const struct KernAux_Multiboot2_HTag_EFII386EntryAddr *const tag,
    const KernAux_Display display
) {
    HEADER(EFII386EntryAddr);

    // TODO: print
}

void KernAux_Multiboot2_HTag_EFIAmd64EntryAddr_print(
    const struct KernAux_Multiboot2_HTag_EFIAmd64EntryAddr *const tag,
    const KernAux_Display display
) {
    HEADER(EFIAmd64EntryAddr);

    // TODO: print
}

void KernAux_Multiboot2_HTag_RelocatableHeader_print(
    const struct KernAux_Multiboot2_HTag_RelocatableHeader *const tag,
    const KernAux_Display display
) {
    HEADER(RelocatableHeader);

    // TODO: print
}
