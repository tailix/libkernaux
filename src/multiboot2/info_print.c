#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/multiboot2.h>

#include <stddef.h>

static const char *KernAux_Multiboot2_ITag_to_str(
    enum KernAux_Multiboot2_ITag tag_type
);

static void KernAux_Multiboot2_ITag_MemoryMap_print(
    const struct KernAux_Multiboot2_ITag_MemoryMap *tag,
    void (*printf)(const char *format, ...) __attribute__((format(printf, 1, 2)))
);

static void KernAux_Multiboot2_ITag_ELFSymbols_print(
    const struct KernAux_Multiboot2_ITag_ELFSymbols *tag,
    void (*printf)(const char *format, ...) __attribute__((format(printf, 1, 2)))
);

const char *KernAux_Multiboot2_ITag_to_str(
    enum KernAux_Multiboot2_ITag tag_type
) {
    switch (tag_type) {
    case KERNAUX_MULTIBOOT2_ITAG_NONE:
        return "none";
    case KERNAUX_MULTIBOOT2_ITAG_BOOT_CMD_LINE:
        return "boot cmd line";
    case KERNAUX_MULTIBOOT2_ITAG_BOOT_LOADER_NAME:
        return "boot loader name";
    case KERNAUX_MULTIBOOT2_ITAG_MODULE:
        return "module";
    case KERNAUX_MULTIBOOT2_ITAG_BASIC_MEMORY_INFO:
        return "basic memory info";
    case KERNAUX_MULTIBOOT2_ITAG_BIOS_BOOT_DEVICE:
        return "BIOS boot device";
    case KERNAUX_MULTIBOOT2_ITAG_MEMORY_MAP:
        return "memory map";
    case KERNAUX_MULTIBOOT2_ITAG_VBE_INFO:
        return "VBE info";
    case KERNAUX_MULTIBOOT2_ITAG_FRAMEBUFFER_INFO:
        return "framebuffer info";
    case KERNAUX_MULTIBOOT2_ITAG_ELF_SYMBOLS:
        return "ELF symbols";
    case KERNAUX_MULTIBOOT2_ITAG_APM_TABLE:
        return "APM table";
    case KERNAUX_MULTIBOOT2_ITAG_EFI_32BIT_SYSTEM_TABLE_PTR:
        return "EFI 32bit system table ptr";
    case KERNAUX_MULTIBOOT2_ITAG_EFI_64BIT_SYSTEM_TABLE_PTR:
        return "EFI 64bit system table ptr";
    case KERNAUX_MULTIBOOT2_ITAG_SMBIOS_TABLES:
        return "SMBIOS tables";
    case KERNAUX_MULTIBOOT2_ITAG_ACPI_OLD_RSDP:
        return "ACPI old RSDP";
    case KERNAUX_MULTIBOOT2_ITAG_ACPI_NEW_RSDP:
        return "ACPI new RSDP";
    case KERNAUX_MULTIBOOT2_ITAG_NETWORKING_INFO:
        return "networking info";
    case KERNAUX_MULTIBOOT2_ITAG_EFI_MEMORY_MAP:
        return "EFI memory map";
    case KERNAUX_MULTIBOOT2_ITAG_EFI_BOOT_SERVICES_NOT_TERMINATED:
        return "EFI boot services not terminated";
    case KERNAUX_MULTIBOOT2_ITAG_EFI_32BIT_IMAGE_HANDLE_PTR:
        return "EFI 32bit image handle ptr";
    case KERNAUX_MULTIBOOT2_ITAG_EFI_64BIT_IMAGE_HANDLE_PTR:
        return "EFI 64bit image handle ptr";
    case KERNAUX_MULTIBOOT2_ITAG_IMAGE_LOAD_BASE_PHYS_ADDR:
        return "image load base phys addr";
    default:
        return NULL;
    }
}

void KernAux_Multiboot2_Info_print(
    const struct KernAux_Multiboot2_Info *const multiboot2_info,
    void (*const printf)(const char *format, ...) __attribute__((format(printf, 1, 2)))
) {
    printf("Multiboot 2 info\n");
    printf("  size: %u\n", multiboot2_info->total_size);
    printf("  reserved1: %u\n", multiboot2_info->reserved1);

    const struct KernAux_Multiboot2_ITagBase *tag_base =
        (struct KernAux_Multiboot2_ITagBase*)
        KERNAUX_MULTIBOOT2_DATA(multiboot2_info);

    while (tag_base <
           (struct KernAux_Multiboot2_ITagBase*)
           ((unsigned char*)multiboot2_info + multiboot2_info->total_size))
    {
        if (!KernAux_Multiboot2_ITagBase_is_valid(tag_base)) return;

        KernAux_Multiboot2_ITagBase_print(tag_base, printf);

        tag_base = (struct KernAux_Multiboot2_ITagBase*)(
            KERNAUX_MULTIBOOT2_TAG_NEXT(tag_base)
        );
    }
}

void KernAux_Multiboot2_ITagBase_print(
    const struct KernAux_Multiboot2_ITagBase *const tag_base,
    void (*const printf)(const char *format, ...) __attribute__((format(printf, 1, 2)))
) {
    if (!KernAux_Multiboot2_ITagBase_is_valid(tag_base)) return;

    printf("Multiboot 2 tag\n");

    printf(
        "  type: %u (%s)\n",
        tag_base->type,
        KernAux_Multiboot2_ITag_to_str(tag_base->type)
    );

    printf("  size: %u\n", tag_base->size);

    switch (tag_base->type) {
    case KERNAUX_MULTIBOOT2_ITAG_NONE:
        break;
    case KERNAUX_MULTIBOOT2_ITAG_BOOT_CMD_LINE:
        printf(
            "  cmdline: %s\n",
            KERNAUX_MULTIBOOT2_DATA(
                (struct KernAux_Multiboot2_ITag_BootCmdLine*)tag_base
            )
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_BOOT_LOADER_NAME:
        printf(
            "  name: %s\n",
            KERNAUX_MULTIBOOT2_DATA(
                (struct KernAux_Multiboot2_ITag_BootLoaderName*)tag_base
            )
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_MODULE:
        {
            const struct KernAux_Multiboot2_ITag_Module *const tag_module =
                (struct KernAux_Multiboot2_ITag_Module*)tag_base;

            printf("  start: %u\n",   tag_module->mod_start);
            printf("  end: %u\n",     tag_module->mod_end);
            printf("  cmdline: %s\n", KERNAUX_MULTIBOOT2_DATA(tag_module));
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_BASIC_MEMORY_INFO:
        {
            const struct KernAux_Multiboot2_ITag_BasicMemoryInfo *const tag_bmi =
                (struct KernAux_Multiboot2_ITag_BasicMemoryInfo*)tag_base;

            printf("  mem lower: %u\n", tag_bmi->mem_lower);
            printf("  mem upper: %u\n", tag_bmi->mem_upper);
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_BIOS_BOOT_DEVICE:
        {
            const struct KernAux_Multiboot2_ITag_BIOSBootDevice *const tag_bbd =
                (struct KernAux_Multiboot2_ITag_BIOSBootDevice*)tag_base;

            printf("  bios dev: %u\n", tag_bbd->bios_dev);
            printf("  partition: %u\n", tag_bbd->partition);
            printf("  sub_partition: %u\n", tag_bbd->sub_partition);
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_MEMORY_MAP:
        KernAux_Multiboot2_ITag_MemoryMap_print(
            (struct KernAux_Multiboot2_ITag_MemoryMap*)tag_base,
            printf
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_VBE_INFO:
        {
            const struct KernAux_Multiboot2_ITag_VBEInfo *const tag_vbe =
                (struct KernAux_Multiboot2_ITag_VBEInfo*)tag_base;

            printf("  VBE mode: %hu\n",          tag_vbe->vbe_mode);
            printf("  VBE interface seg: %hu\n", tag_vbe->vbe_interface_seg);
            printf("  VBE interface off: %hu\n", tag_vbe->vbe_interface_off);
            printf("  VBE interface len: %hu\n", tag_vbe->vbe_interface_len);
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_FRAMEBUFFER_INFO:
        {
            const struct KernAux_Multiboot2_ITag_FramebufferInfo *const tag_fb =
                (struct KernAux_Multiboot2_ITag_FramebufferInfo*)tag_base;

            printf("  framebuffer addr: %llu\n", tag_fb->framebuffer_addr);
            printf("  framebuffer pitch: %u\n",  tag_fb->framebuffer_pitch);
            printf("  framebuffer width: %u\n",  tag_fb->framebuffer_width);
            printf("  framebuffer height: %u\n", tag_fb->framebuffer_height);
            printf("  framebuffer bpp: %u\n",    tag_fb->framebuffer_bpp);
            printf("  framebuffer type: %u\n",   tag_fb->framebuffer_type);
            printf("  reserved1: %u\n",          tag_fb->reserved1);
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_ELF_SYMBOLS:
        KernAux_Multiboot2_ITag_ELFSymbols_print(
            (struct KernAux_Multiboot2_ITag_ELFSymbols*)tag_base,
            printf
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_APM_TABLE:
        {
            const struct KernAux_Multiboot2_ITag_APMTable *const tag_apm =
                (struct KernAux_Multiboot2_ITag_APMTable*)tag_base;

            printf("  version: %hu\n",     tag_apm->version);
            printf("  cseg: %hu\n",        tag_apm->cseg);
            printf("  offset: %u\n",       tag_apm->offset);
            printf("  cseg 16: %hu\n",     tag_apm->cseg_16);
            printf("  dseg: %hu\n",        tag_apm->dseg);
            printf("  flags: %hu\n",       tag_apm->flags);
            printf("  cseg len: %hu\n",    tag_apm->cseg_len);
            printf("  cseg 16 len: %hu\n", tag_apm->cseg_16_len);
            printf("  dseg len: %hu\n",    tag_apm->dseg_len);
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

            printf("  major: %u\n", tag_smbios->major);
            printf("  minor: %u\n", tag_smbios->minor);

            printf(
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
        printf(
            "  load base addr: %u\n",
            ((struct KernAux_Multiboot2_ITag_ImageLoadBasePhysAddr*)tag_base)->
                load_base_addr
        );
        break;
    }
}

void KernAux_Multiboot2_ITag_MemoryMap_print(
    const struct KernAux_Multiboot2_ITag_MemoryMap *const tag,
    void (*printf)(const char *format, ...) __attribute__((format(printf, 1, 2)))
) {
    if (!KernAux_Multiboot2_ITag_MemoryMap_is_valid(tag)) {
        printf("  invalid!\n");
        return;
    }

    printf("  entry size: %u\n",    tag->entry_size);
    printf("  entry version: %u\n", tag->entry_version);

    printf("  entries:\n");

    const struct KernAux_Multiboot2_ITag_MemoryMap_EntryBase *const entries =
        (struct KernAux_Multiboot2_ITag_MemoryMap_EntryBase*)
        KERNAUX_MULTIBOOT2_DATA((struct KernAux_Multiboot2_ITag_MemoryMap*)tag);

    for (
        size_t index = 0;
        index < (tag->base.size - sizeof(*tag)) / tag->entry_size;
        ++index
    ) {
        printf("    entry %lu\n", index);
        printf("      base addr: %llu\n", entries[index].base_addr);
        printf("      length: %llu\n",    entries[index].length);
        printf("      type: %u\n",        entries[index].type);
        printf("      reserved1: %u\n",   entries[index].reserved1);
    }
}

void KernAux_Multiboot2_ITag_ELFSymbols_print(
    const struct KernAux_Multiboot2_ITag_ELFSymbols *const tag,
    void (*printf)(const char *format, ...) __attribute__((format(printf, 1, 2)))
) {
    if (!KernAux_Multiboot2_ITag_ELFSymbols_is_valid(tag)) {
        printf("  invalid!\n");
        return;
    }

    printf("  num: %hu\n",       tag->num);
    printf("  entsize: %hu\n",   tag->ent_size);
    printf("  shndx: %hu\n",     tag->shndx);
    printf("  reserved1: %hu\n", tag->reserved1);

    // TODO: implement this
}
