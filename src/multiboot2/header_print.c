#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "../assert.h"

#include <kernaux/generic/display.h>
#include <kernaux/macro.h>
#include <kernaux/multiboot2.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define PRINT(s)   do { KernAux_Display_print  (display, s); } while (0)
#define PRINTLN(s) do { KernAux_Display_println(display, s); } while (0)

#define PRINTF(format, ...) \
    do { KernAux_Display_printf  (display, format, __VA_ARGS__); } while (0)
#define PRINTLNF(format, ...) \
    do { KernAux_Display_printlnf(display, format, __VA_ARGS__); } while (0)

#define HEADER(Type) do { \
    KERNAUX_NOTNULL(tag);                                      \
    KERNAUX_NOTNULL(display);                                  \
                                                               \
    if (!KernAux_Multiboot2_HTag_##Type##_is_valid(tag)) {     \
        PRINTLN("Multiboot 2 header tag // invalid!");         \
    }                                                          \
                                                               \
    KERNAUX_CAST_CONST(unsigned long, type, tag->base.type);   \
    KERNAUX_CAST_CONST(unsigned long, size, tag->base.size);   \
                                                               \
    PRINTLN ("Multiboot 2 header tag {");                      \
    PRINTLNF("  u16 type: %lu (%s)",                           \
        type,                                                  \
        KernAux_Multiboot2_HTag_to_str(tag->base.type)         \
    );                                                         \
    PRINT   ("  u16 flags: ");                                 \
    KernAux_Multiboot2_HTagBase_Flags_print(                   \
        tag->base.flags,                                       \
        display,                                               \
        2,                                                     \
        2,                                                     \
        false                                                  \
    );                                                         \
    PRINTLNF("  u32 size: %lu", size);                         \
} while (0)

#define FOOTER do { PRINTLN("}"); } while (0)

#define INDENT do { \
    for (unsigned index = 0; index < basic_indentation; ++index) PRINT(" "); \
} while (0)

#define INDENT_MORE do { \
    for (unsigned index = 0; index < indentation_delta; ++index) PRINT(" "); \
} while (0)

static const struct {
    uint32_t number;
    const char *name;
} base_flag_names[] = {
    {
        .number = KERNAUX_MULTIBOOT2_HTAG_BASE_FLAG_OPTIONAL,
        .name = "OPTIONAL",
    },
};

static const struct {
    uint32_t number;
    const char *name;
} console_flag_names[] = {
    {
        .number = KERNAUX_MULTIBOOT2_HTAG_FLAGS_REQUIRE_CONSOLE,
        .name = "REQUIRE_CONSOLE",
    },
    {
        .number = KERNAUX_MULTIBOOT2_HTAG_FLAGS_EGA_SUPPORT,
        .name = "EGA_SUPPORT",
    }
};

static void KernAux_Multiboot2_HTagBase_Flags_print(
    uint16_t flags,
    KernAux_Display display,
    unsigned basic_indentation,
    unsigned indentation_delta,
    bool indent_first
);

static void KernAux_Multiboot2_HTag_Flags_ConsoleFlags_print(
    uint32_t console_flags,
    KernAux_Display display,
    unsigned basic_indentation,
    unsigned indentation_delta,
    bool indent_first
);

void KernAux_Multiboot2_Header_print(
    const struct KernAux_Multiboot2_Header *const multiboot2_header,
    const KernAux_Display display
) {
    KERNAUX_NOTNULL(multiboot2_header);
    KERNAUX_NOTNULL(display);

    KERNAUX_CAST_CONST(unsigned long, magic,      multiboot2_header->magic);
    KERNAUX_CAST_CONST(unsigned long, arch,       multiboot2_header->arch);
    KERNAUX_CAST_CONST(unsigned long, total_size, multiboot2_header->total_size);
    KERNAUX_CAST_CONST(unsigned long, checksum,   multiboot2_header->checksum);

    PRINTLN("Multiboot 2 header {");
    PRINTLNF("  u32 magic: 0x%lx", magic);
    PRINTLNF("  u32 arch: %lu (%s)",
        arch,
        KernAux_Multiboot2_Header_Arch_to_str(multiboot2_header->arch)
    );
    PRINTLNF("  u32 size: %lu", total_size);
    PRINTLNF("  u32 checksum: 0x%lx", checksum);
    PRINTLN("}");

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
    KERNAUX_NOTNULL(tag_base);
    KERNAUX_NOTNULL(display);

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
    FOOTER;
}

void KernAux_Multiboot2_HTag_InfoReq_print(
    const struct KernAux_Multiboot2_HTag_InfoReq *const tag,
    const KernAux_Display display
) {
    HEADER(InfoReq);

    // Print data:

    if ((tag->base.size - sizeof(*tag)) / sizeof(uint32_t) == 0) {
        PRINTLN("  u32 mbi_tag_types[]: []");
    } else {
        PRINTLN("  u32 mbi_tag_types[]: [");

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

        PRINTLN("  ]");
    }

    FOOTER;
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

    PRINTLNF("  u32 header_addr: 0x%lx",   header_addr);
    PRINTLNF("  u32 load_addr: 0x%lx",     load_addr);
    PRINTLNF("  u32 load_end_addr: 0x%lx", load_end_addr);
    PRINTLNF("  u32 bss_end_addr: 0x%lx",  bss_end_addr);

    FOOTER;
}

void KernAux_Multiboot2_HTag_EntryAddr_print(
    const struct KernAux_Multiboot2_HTag_EntryAddr *const tag,
    const KernAux_Display display
) {
    HEADER(EntryAddr);

    KERNAUX_CAST_CONST(unsigned long, entry_addr, tag->entry_addr);

    PRINTLNF("  u32 entry_addr: 0x%lx", entry_addr);

    FOOTER;
}

void KernAux_Multiboot2_HTag_Flags_print(
    const struct KernAux_Multiboot2_HTag_Flags *const tag,
    const KernAux_Display display
) {
    HEADER(Flags);

    PRINT("  u32 console_flags: ");
    KernAux_Multiboot2_HTag_Flags_ConsoleFlags_print(
        tag->console_flags,
        display,
        2,
        2,
        false
    );

    FOOTER;
}

void KernAux_Multiboot2_HTag_Framebuffer_print(
    const struct KernAux_Multiboot2_HTag_Framebuffer *const tag,
    const KernAux_Display display
) {
    HEADER(Framebuffer);

    KERNAUX_CAST_CONST(unsigned long, width,  tag->width);
    KERNAUX_CAST_CONST(unsigned long, height, tag->height);
    KERNAUX_CAST_CONST(unsigned long, depth,  tag->depth);

    PRINTLNF("  u32 width: %lu",  width);
    PRINTLNF("  u32 height: %lu", height);
    PRINTLNF("  u32 depth: %lu",  depth);

    FOOTER;
}

void KernAux_Multiboot2_HTag_ModuleAlign_print(
    const struct KernAux_Multiboot2_HTag_ModuleAlign *const tag,
    const KernAux_Display display
) {
    HEADER(ModuleAlign);

    FOOTER;
}

void KernAux_Multiboot2_HTag_EFIBootServices_print(
    const struct KernAux_Multiboot2_HTag_EFIBootServices *const tag,
    const KernAux_Display display
) {
    HEADER(EFIBootServices);

    FOOTER;
}

void KernAux_Multiboot2_HTag_EFII386EntryAddr_print(
    const struct KernAux_Multiboot2_HTag_EFII386EntryAddr *const tag,
    const KernAux_Display display
) {
    HEADER(EFII386EntryAddr);

    KERNAUX_CAST_CONST(unsigned long, entry_addr, tag->entry_addr);

    PRINTLNF("  u32 entry_addr: 0x%lx", entry_addr);

    FOOTER;
}

void KernAux_Multiboot2_HTag_EFIAmd64EntryAddr_print(
    const struct KernAux_Multiboot2_HTag_EFIAmd64EntryAddr *const tag,
    const KernAux_Display display
) {
    HEADER(EFIAmd64EntryAddr);

    KERNAUX_CAST_CONST(unsigned long, entry_addr, tag->entry_addr);

    PRINTLNF("  u32 entry_addr: 0x%lx", entry_addr);

    FOOTER;
}

void KernAux_Multiboot2_HTag_RelocatableHeader_print(
    const struct KernAux_Multiboot2_HTag_RelocatableHeader *const tag,
    const KernAux_Display display
) {
    HEADER(RelocatableHeader);

    KERNAUX_CAST_CONST(unsigned long, min_addr,   tag->min_addr);
    KERNAUX_CAST_CONST(unsigned long, max_addr,   tag->max_addr);
    KERNAUX_CAST_CONST(unsigned long, align,      tag->align);
    KERNAUX_CAST_CONST(unsigned long, preference, tag->preference);

    PRINTLNF("  u32 min_addr: 0x%lx", min_addr);
    PRINTLNF("  u32 max_addr: 0x%lx", max_addr);
    PRINTLNF("  u32 align: %lu",      align);
    PRINTLNF("  u32 preference: %lu (%s)",
        preference,
        KernAux_Multiboot2_HTag_RelocatableHeader_Preference_to_str(
            tag->preference
        )
    );

    FOOTER;
}

void KernAux_Multiboot2_HTagBase_Flags_print(
    const uint16_t flags,
    const KernAux_Display display,
    const unsigned basic_indentation,
    const unsigned indentation_delta,
    const bool indent_first
) {
    KERNAUX_CAST_CONST(unsigned long, flags_ul, flags);

    if (indent_first) INDENT;
    PRINTF("0x%lx (", flags_ul);

    bool is_first = true;

    for (
        size_t index = 0;
        index < sizeof(base_flag_names) / sizeof(base_flag_names[0]);
        ++index
    ) {
        if (flags & base_flag_names[index].number) {
            if (is_first) {
                PRINTLN("");
            } else {
                PRINTLN(" |");
            }

            INDENT;
            INDENT_MORE;
            PRINTF("%s", base_flag_names[index].name);
            is_first = false;
        }
    }

    if (is_first) {
        PRINTLN(")");
    } else {
        PRINTLN("");
        INDENT;
        PRINTLN(")");
    }
}

void KernAux_Multiboot2_HTag_Flags_ConsoleFlags_print(
    const uint32_t console_flags,
    const KernAux_Display display,
    const unsigned basic_indentation,
    const unsigned indentation_delta,
    const bool indent_first
) {
    KERNAUX_CAST_CONST(unsigned long, console_flags_ul, console_flags);

    if (indent_first) INDENT;
    PRINTF("0x%lx (", console_flags_ul);

    bool is_first = true;

    for (
        size_t index = 0;
        index < sizeof(console_flag_names) / sizeof(console_flag_names[0]);
        ++index
    ) {
        if (console_flags & console_flag_names[index].number) {
            if (is_first) {
                PRINTLN("");
            } else {
                PRINTLN(" |");
            }

            INDENT;
            INDENT_MORE;
            PRINTF("%s", console_flag_names[index].name);
            is_first = false;
        }
    }

    if (is_first) {
        PRINTLN(")");
    } else {
        PRINTLN("");
        INDENT;
        PRINTLN(")");
    }
}
