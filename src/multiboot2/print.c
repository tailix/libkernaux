#include <kernaux/multiboot2.h>

static const char *KernAux_Multiboot2_TagType_to_str(
    enum KernAux_Multiboot2_TagType tag_type
);

const char *KernAux_Multiboot2_TagType_to_str(
    enum KernAux_Multiboot2_TagType tag_type
) {
    switch (tag_type) {
    case KERNAUX_MULTIBOOT2_TAGTYPE_NONE:
        return "none";
    case KERNAUX_MULTIBOOT2_TAGTYPE_BOOT_CMD_LINE:
        return "boot cmd line";
    case KERNAUX_MULTIBOOT2_TAGTYPE_BOOT_LOADER_NAME:
        return "boot loader name";
    case KERNAUX_MULTIBOOT2_TAGTYPE_MODULE:
        return "module";
    case KERNAUX_MULTIBOOT2_TAGTYPE_BASIC_MEMORY_INFO:
        return "basic memory info";
    case KERNAUX_MULTIBOOT2_TAGTYPE_BIOS_BOOT_DEVICE:
        return "BIOS boot device";
    case KERNAUX_MULTIBOOT2_TAGTYPE_MEMORY_MAP:
        return "memory map";
    case KERNAUX_MULTIBOOT2_TAGTYPE_VBE_INFO:
        return "VBE info";
    case KERNAUX_MULTIBOOT2_TAGTYPE_FRAMEBUFFER_INFO:
        return "framebuffer info";
    case KERNAUX_MULTIBOOT2_TAGTYPE_ELF_SYMBOLS:
        return "ELF symbols";
    case KERNAUX_MULTIBOOT2_TAGTYPE_APM_TABLE:
        return "APM table";
    case KERNAUX_MULTIBOOT2_TAGTYPE_EFI_32BIT_SYSTEM_TABLE_PTR:
        return "EFI 32bit system table ptr";
    case KERNAUX_MULTIBOOT2_TAGTYPE_EFI_64BIT_SYSTEM_TABLE_PTR:
        return "EFI 64bit system table ptr";
    case KERNAUX_MULTIBOOT2_TAGTYPE_SMBIOS_TABLES:
        return "SMBIOS tables";
    case KERNAUX_MULTIBOOT2_TAGTYPE_ACPI_OLD_RSDP:
        return "ACPI old RSDP";
    case KERNAUX_MULTIBOOT2_TAGTYPE_ACPI_NEW_RSDP:
        return "ACPI new RSDP";
    case KERNAUX_MULTIBOOT2_TAGTYPE_NETWORKING_INFO:
        return "networking info";
    case KERNAUX_MULTIBOOT2_TAGTYPE_EFI_MEMORY_MAP:
        return "EFI memory map";
    case KERNAUX_MULTIBOOT2_TAGTYPE_EFI_BOOT_SERVICES_NOT_TERMINATED:
        return "EFI boot services not terminated";
    case KERNAUX_MULTIBOOT2_TAGTYPE_EFI_32BIT_IMAGE_HANDLE_PTR:
        return "EFI 32bit image handle ptr";
    case KERNAUX_MULTIBOOT2_TAGTYPE_EFI_64BIT_IMAGE_HANDLE_PTR:
        return "EFI 64bit image handle ptr";
    case KERNAUX_MULTIBOOT2_TAGTYPE_IMAGE_LOAD_BASE_PHYS_ADDR:
        return "image load base phys addr";
    default:
        return 0;
    }
}

void KernAux_Multiboot2_print(
    const struct KernAux_Multiboot2 *const multiboot2,
    void (*const print)(const char *format, ...)
) {
    print("Multiboot 2 info\n");
    print("  size: %u\n", multiboot2->total_size);
    print("  reserved1: %u\n", multiboot2->reserved1);

    if (multiboot2->total_size <= 8) {
        return;
    }

    const struct KernAux_Multiboot2_TagBase *tag_base =
        (struct KernAux_Multiboot2_TagBase*)multiboot2->data;

    while ((void*)tag_base < (void*)multiboot2 + multiboot2->total_size) {
        if (!KernAux_Multiboot2_TagBase_is_valid(tag_base)) {
            return;
        }

        KernAux_Multiboot2_TagBase_print(tag_base, print);

        tag_base = (struct KernAux_Multiboot2_TagBase*)(
            (void*)tag_base + ((tag_base->size + 7) & ~7)
        );
    }
}

void KernAux_Multiboot2_TagBase_print(
    const struct KernAux_Multiboot2_TagBase *const tag_base,
    void (*const print)(const char *format, ...)
) {
    if (!KernAux_Multiboot2_TagBase_is_valid(tag_base)) {
        return;
    }

    print("Multiboot 2 tag\n");

    print(
        "  type: %u (%s)\n",
        tag_base->type,
        KernAux_Multiboot2_TagType_to_str(tag_base->type)
    );

    print("  size: %u\n", tag_base->size);

    switch (tag_base->type) {
    case KERNAUX_MULTIBOOT2_TAGTYPE_BOOT_CMD_LINE:
        print(
            "  cmdline: %s\n",
            ((struct KernAux_Multiboot2_Tag_BootCmdLine*)tag_base)->cmdline
        );
        break;
    case KERNAUX_MULTIBOOT2_TAGTYPE_BOOT_LOADER_NAME:
        print(
            "  name: %s\n",
            ((struct KernAux_Multiboot2_Tag_BootLoaderName*)tag_base)->name
        );
        break;
    case KERNAUX_MULTIBOOT2_TAGTYPE_MODULE:
        {
            const struct KernAux_Multiboot2_Tag_Module *const tag_module =
                (struct KernAux_Multiboot2_Tag_Module*)tag_base;

            print("  start: %u\n",   tag_module->mod_start);
            print("  end: %u\n",     tag_module->mod_end);
            print("  cmdline: %s\n", tag_module->cmdline);
        }
        break;
    case KERNAUX_MULTIBOOT2_TAGTYPE_BASIC_MEMORY_INFO:
        {
            const struct KernAux_Multiboot2_Tag_BasicMemoryInfo *const tag_bmi =
                (struct KernAux_Multiboot2_Tag_BasicMemoryInfo*)tag_base;

            print("  mem lower: %u\n", tag_bmi->mem_lower);
            print("  mem upper: %u\n", tag_bmi->mem_upper);
        }
        break;
    case KERNAUX_MULTIBOOT2_TAGTYPE_BIOS_BOOT_DEVICE:
        {
            const struct KernAux_Multiboot2_Tag_BIOSBootDevice *const tag_bbd =
                (struct KernAux_Multiboot2_Tag_BIOSBootDevice*)tag_base;

            print("  bios dev: %u\n", tag_bbd->bios_dev);
            print("  partition: %u\n", tag_bbd->partition);
            print("  sub_partition: %u\n", tag_bbd->sub_partition);
        }
        break;
    case KERNAUX_MULTIBOOT2_TAGTYPE_IMAGE_LOAD_BASE_PHYS_ADDR:
        print(
            "  load base addr: %u\n",
            ((struct KernAux_Multiboot2_Tag_ImageLoadBasePhysAddr*)tag_base)->
                load_base_addr
        );
        break;
    }
}
