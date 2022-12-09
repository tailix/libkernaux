#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/multiboot2.h>

#include <stddef.h>
#include <stdint.h>

#define DISPLAY(func, ...) KernAux_Display_##func(display, __VA_ARGS__)

void KernAux_Multiboot2_Info_print(
    const struct KernAux_Multiboot2_Info *const multiboot2_info,
    const KernAux_Display display
) {
    KERNAUX_ASSERT(multiboot2_info);
    KERNAUX_ASSERT(display);

    DISPLAY(printlnf, "Multiboot 2 info");
    DISPLAY(printlnf, "  size: %u", multiboot2_info->total_size);
    DISPLAY(printlnf, "  reserved1: %u", multiboot2_info->reserved1);

    const struct KernAux_Multiboot2_ITagBase *tag_base =
        (struct KernAux_Multiboot2_ITagBase*)
        KERNAUX_MULTIBOOT2_DATA(multiboot2_info);

    while (tag_base <
           (struct KernAux_Multiboot2_ITagBase*)
           ((uint8_t*)multiboot2_info + multiboot2_info->total_size))
    {
        if (!KernAux_Multiboot2_ITagBase_is_valid(tag_base)) return;

        KernAux_Multiboot2_ITagBase_print(tag_base, display);

        tag_base = KERNAUX_MULTIBOOT2_ITAG_NEXT(tag_base);
    }
}

void KernAux_Multiboot2_ITagBase_print(
    const struct KernAux_Multiboot2_ITagBase *const tag_base,
    const KernAux_Display display
) {
    KERNAUX_ASSERT(tag_base);
    KERNAUX_ASSERT(display);

    if (!KernAux_Multiboot2_ITagBase_is_valid(tag_base)) return;

    DISPLAY(println, "Multiboot 2 info tag");

    DISPLAY(
        printlnf,
        "  type: %u (%s)",
        tag_base->type,
        KernAux_Multiboot2_ITag_to_str(tag_base->type)
    );

    DISPLAY(printlnf, "  size: %u", tag_base->size);

    switch (tag_base->type) {
    case KERNAUX_MULTIBOOT2_ITAG_NONE:
        break;
    case KERNAUX_MULTIBOOT2_ITAG_BOOT_CMD_LINE:
        KernAux_Multiboot2_ITag_BootCmdLine_print(
            (struct KernAux_Multiboot2_ITag_BootCmdLine*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_BOOT_LOADER_NAME:
        KernAux_Multiboot2_ITag_BootLoaderName_print(
            (struct KernAux_Multiboot2_ITag_BootLoaderName*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_MODULE:
        {
            const struct KernAux_Multiboot2_ITag_Module *const tag_module =
                (struct KernAux_Multiboot2_ITag_Module*)tag_base;

            DISPLAY(printlnf, "  start: %u",   tag_module->mod_start);
            DISPLAY(printlnf, "  end: %u",     tag_module->mod_end);
            DISPLAY(printlnf, "  cmdline: %s", KERNAUX_MULTIBOOT2_DATA(tag_module));
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_BASIC_MEMORY_INFO:
        {
            const struct KernAux_Multiboot2_ITag_BasicMemoryInfo *const tag_bmi =
                (struct KernAux_Multiboot2_ITag_BasicMemoryInfo*)tag_base;

            DISPLAY(printlnf, "  mem lower: %u", tag_bmi->mem_lower);
            DISPLAY(printlnf, "  mem upper: %u", tag_bmi->mem_upper);
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_BIOS_BOOT_DEVICE:
        {
            const struct KernAux_Multiboot2_ITag_BIOSBootDevice *const tag_bbd =
                (struct KernAux_Multiboot2_ITag_BIOSBootDevice*)tag_base;

            DISPLAY(printlnf, "  bios dev: %u", tag_bbd->bios_dev);
            DISPLAY(printlnf, "  partition: %u", tag_bbd->partition);
            DISPLAY(printlnf, "  sub_partition: %u", tag_bbd->sub_partition);
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_MEMORY_MAP:
        KernAux_Multiboot2_ITag_MemoryMap_print(
            (struct KernAux_Multiboot2_ITag_MemoryMap*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_VBE_INFO:
        {
            const struct KernAux_Multiboot2_ITag_VBEInfo *const tag_vbe =
                (struct KernAux_Multiboot2_ITag_VBEInfo*)tag_base;

            DISPLAY(printlnf, "  VBE mode: %hu",          tag_vbe->vbe_mode);
            DISPLAY(printlnf, "  VBE interface seg: %hu", tag_vbe->vbe_interface_seg);
            DISPLAY(printlnf, "  VBE interface off: %hu", tag_vbe->vbe_interface_off);
            DISPLAY(printlnf, "  VBE interface len: %hu", tag_vbe->vbe_interface_len);
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_FRAMEBUFFER_INFO:
        {
            const struct KernAux_Multiboot2_ITag_FramebufferInfo *const tag_fb =
                (struct KernAux_Multiboot2_ITag_FramebufferInfo*)tag_base;

            DISPLAY(printlnf, "  framebuffer addr: %llu", tag_fb->framebuffer_addr);
            DISPLAY(printlnf, "  framebuffer pitch: %u",  tag_fb->framebuffer_pitch);
            DISPLAY(printlnf, "  framebuffer width: %u",  tag_fb->framebuffer_width);
            DISPLAY(printlnf, "  framebuffer height: %u", tag_fb->framebuffer_height);
            DISPLAY(printlnf, "  framebuffer bpp: %u",    tag_fb->framebuffer_bpp);
            DISPLAY(printlnf, "  framebuffer type: %u",   tag_fb->framebuffer_type);
            DISPLAY(printlnf, "  reserved1: %u",          tag_fb->reserved1);
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_ELF_SYMBOLS:
        KernAux_Multiboot2_ITag_ELFSymbols_print(
            (struct KernAux_Multiboot2_ITag_ELFSymbols*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_APM_TABLE:
        {
            const struct KernAux_Multiboot2_ITag_APMTable *const tag_apm =
                (struct KernAux_Multiboot2_ITag_APMTable*)tag_base;

            DISPLAY(printlnf, "  version: %hu",     tag_apm->version);
            DISPLAY(printlnf, "  cseg: %hu",        tag_apm->cseg);
            DISPLAY(printlnf, "  offset: %u",       tag_apm->offset);
            DISPLAY(printlnf, "  cseg 16: %hu",     tag_apm->cseg_16);
            DISPLAY(printlnf, "  dseg: %hu",        tag_apm->dseg);
            DISPLAY(printlnf, "  flags: %hu",       tag_apm->flags);
            DISPLAY(printlnf, "  cseg len: %hu",    tag_apm->cseg_len);
            DISPLAY(printlnf, "  cseg 16 len: %hu", tag_apm->cseg_16_len);
            DISPLAY(printlnf, "  dseg len: %hu",    tag_apm->dseg_len);
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_EFI_32BIT_SYSTEM_TABLE_PTR:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_EFI_64BIT_SYSTEM_TABLE_PTR:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_SMBIOS_TABLES:
        {
            const struct KernAux_Multiboot2_ITag_SMBIOSTables *const tag_smbios =
                (struct KernAux_Multiboot2_ITag_SMBIOSTables*)tag_base;

            DISPLAY(printlnf, "  major: %u", tag_smbios->major);
            DISPLAY(printlnf, "  minor: %u", tag_smbios->minor);

            DISPLAY(
                printlnf,
                "  reserved1: {%u, %u, %u, %u, %u, %u}\n",
                tag_smbios->reserved1[0],
                tag_smbios->reserved1[1],
                tag_smbios->reserved1[2],
                tag_smbios->reserved1[3],
                tag_smbios->reserved1[4],
                tag_smbios->reserved1[5]
            );
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_ACPI_OLD_RSDP:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_ACPI_NEW_RSDP:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_NETWORKING_INFO:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_EFI_MEMORY_MAP:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_EFI_BOOT_SERVICES_NOT_TERMINATED:
        break;
    case KERNAUX_MULTIBOOT2_ITAG_EFI_32BIT_IMAGE_HANDLE_PTR:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_EFI_64BIT_IMAGE_HANDLE_PTR:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_IMAGE_LOAD_BASE_PHYS_ADDR:
        DISPLAY(
            printlnf,
            "  load base addr: %u",
            ((struct KernAux_Multiboot2_ITag_ImageLoadBasePhysAddr*)tag_base)->
                load_base_addr
        );
        break;
    }
}

void KernAux_Multiboot2_ITag_BootCmdLine_print(
    const struct KernAux_Multiboot2_ITag_BootCmdLine *const tag,
    const KernAux_Display display
) {
    KERNAUX_ASSERT(tag);
    KERNAUX_ASSERT(display);

    if (!KernAux_Multiboot2_ITag_BootCmdLine_is_valid(tag)) {
        DISPLAY(println, "  invalid!");
        return;
    }

    DISPLAY(printlnf, "  cmdline: %s\n", KERNAUX_MULTIBOOT2_DATA(tag));
}

void KernAux_Multiboot2_ITag_BootLoaderName_print(
    const struct KernAux_Multiboot2_ITag_BootLoaderName *const tag,
    const KernAux_Display display
) {
    KERNAUX_ASSERT(tag);
    KERNAUX_ASSERT(display);

    if (!KernAux_Multiboot2_ITag_BootLoaderName_is_valid(tag)) {
        DISPLAY(println, "  invalid!");
        return;
    }

    DISPLAY(printlnf, "  name: %s", KERNAUX_MULTIBOOT2_DATA(tag));
}

void KernAux_Multiboot2_ITag_MemoryMap_print(
    const struct KernAux_Multiboot2_ITag_MemoryMap *const tag,
    const KernAux_Display display
) {
    KERNAUX_ASSERT(tag);
    KERNAUX_ASSERT(display);

    if (!KernAux_Multiboot2_ITag_MemoryMap_is_valid(tag)) {
        DISPLAY(println, "  invalid!");
        return;
    }

    DISPLAY(printlnf, "  entry size: %u",    tag->entry_size);
    DISPLAY(printlnf, "  entry version: %u", tag->entry_version);
    DISPLAY(println, "  entries:");

    const struct KernAux_Multiboot2_ITag_MemoryMap_EntryBase *const entries =
        (struct KernAux_Multiboot2_ITag_MemoryMap_EntryBase*)
        KERNAUX_MULTIBOOT2_DATA((struct KernAux_Multiboot2_ITag_MemoryMap*)tag);

    for (
        size_t index = 0;
        index < (tag->base.size - sizeof(*tag)) / tag->entry_size;
        ++index
    ) {
        DISPLAY(printlnf, "    entry %lu", index);
        DISPLAY(printlnf, "      base addr: %llu", entries[index].base_addr);
        DISPLAY(printlnf, "      length: %llu",    entries[index].length);
        DISPLAY(printlnf, "      type: %u",        entries[index].type);
        DISPLAY(printlnf, "      reserved1: %u",   entries[index].reserved1);
    }
}

void KernAux_Multiboot2_ITag_ELFSymbols_print(
    const struct KernAux_Multiboot2_ITag_ELFSymbols *const tag,
    const KernAux_Display display
) {
    KERNAUX_ASSERT(tag);
    KERNAUX_ASSERT(display);

    if (!KernAux_Multiboot2_ITag_ELFSymbols_is_valid(tag)) {
        DISPLAY(println, "  invalid!");
        return;
    }

    DISPLAY(printlnf, "  num: %hu",       tag->num);
    DISPLAY(printlnf, "  entsize: %hu",   tag->ent_size);
    DISPLAY(printlnf, "  shndx: %hu",     tag->shndx);
    DISPLAY(printlnf, "  reserved1: %hu", tag->reserved1);

    // TODO: implement this
}
