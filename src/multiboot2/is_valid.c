#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/multiboot2.h>

#include <stddef.h>

bool KernAux_Multiboot2_is_valid(
    const struct KernAux_Multiboot2 *const multiboot2
) {
    if (multiboot2->total_size <= 8) return false;

    const struct KernAux_Multiboot2_TagBase *tag_base =
        (struct KernAux_Multiboot2_TagBase*)multiboot2->data;

    const struct KernAux_Multiboot2_TagBase *none_tag_base = NULL;

    while (tag_base <
           (struct KernAux_Multiboot2_TagBase*)
           ((unsigned char*)multiboot2 + multiboot2->total_size))
    {
        if (!KernAux_Multiboot2_TagBase_is_valid(tag_base)) return false;

        if (tag_base->type == KERNAUX_MULTIBOOT2_TAGTYPE_NONE &&
            none_tag_base == NULL
        ) {
            none_tag_base = tag_base;
        }

        tag_base = (struct KernAux_Multiboot2_TagBase*)(
            (unsigned char*)tag_base + ((tag_base->size + 7) & ~7)
        );
    }

    if (tag_base !=
        (struct KernAux_Multiboot2_TagBase*)
        ((unsigned char*)multiboot2 + multiboot2->total_size))
    {
        return false;
    }

    if (none_tag_base !=
        (struct KernAux_Multiboot2_TagBase*)
        ((unsigned char*)tag_base - sizeof(struct KernAux_Multiboot2_Tag_None)))
    {
        return false;
    }

    return true;
}

bool KernAux_Multiboot2_TagBase_is_valid(
    const struct KernAux_Multiboot2_TagBase *const tag_base
) {
    switch (tag_base->type) {
    case KERNAUX_MULTIBOOT2_TAGTYPE_NONE:
        return KernAux_Multiboot2_Tag_None_is_valid(
            (struct KernAux_Multiboot2_Tag_None*)tag_base
        );
    case KERNAUX_MULTIBOOT2_TAGTYPE_BOOT_CMD_LINE:
        return KernAux_Multiboot2_Tag_BootCmdLine_is_valid(
            (struct KernAux_Multiboot2_Tag_BootCmdLine*)tag_base
        );
    case KERNAUX_MULTIBOOT2_TAGTYPE_BOOT_LOADER_NAME:
        return KernAux_Multiboot2_Tag_BootLoaderName_is_valid(
            (struct KernAux_Multiboot2_Tag_BootLoaderName*)tag_base
        );
    case KERNAUX_MULTIBOOT2_TAGTYPE_MODULE:
        return KernAux_Multiboot2_Tag_Module_is_valid(
            (struct KernAux_Multiboot2_Tag_Module*)tag_base
        );
    case KERNAUX_MULTIBOOT2_TAGTYPE_BASIC_MEMORY_INFO:
        return KernAux_Multiboot2_Tag_BasicMemoryInfo_is_valid(
            (struct KernAux_Multiboot2_Tag_BasicMemoryInfo*)tag_base
        );
    case KERNAUX_MULTIBOOT2_TAGTYPE_BIOS_BOOT_DEVICE:
        return KernAux_Multiboot2_Tag_BIOSBootDevice_is_valid(
            (struct KernAux_Multiboot2_Tag_BIOSBootDevice*)tag_base
        );
    case KERNAUX_MULTIBOOT2_TAGTYPE_MEMORY_MAP:
        return KernAux_Multiboot2_Tag_MemoryMap_is_valid(
            (struct KernAux_Multiboot2_Tag_MemoryMap*)tag_base
        );
    case KERNAUX_MULTIBOOT2_TAGTYPE_VBE_INFO:
        return KernAux_Multiboot2_Tag_VBEInfo_is_valid(
            (struct KernAux_Multiboot2_Tag_VBEInfo*)tag_base
        );
    case KERNAUX_MULTIBOOT2_TAGTYPE_FRAMEBUFFER_INFO:
        return KernAux_Multiboot2_Tag_FramebufferInfo_is_valid(
            (struct KernAux_Multiboot2_Tag_FramebufferInfo*)tag_base
        );
    case KERNAUX_MULTIBOOT2_TAGTYPE_ELF_SYMBOLS:
        return KernAux_Multiboot2_Tag_ELFSymbols_is_valid(
            (struct KernAux_Multiboot2_Tag_ELFSymbols*)tag_base
        );
    case KERNAUX_MULTIBOOT2_TAGTYPE_APM_TABLE:
        return KernAux_Multiboot2_Tag_APMTable_is_valid(
            (struct KernAux_Multiboot2_Tag_APMTable*)tag_base
        );
    case KERNAUX_MULTIBOOT2_TAGTYPE_EFI_32BIT_SYSTEM_TABLE_PTR:
        return KernAux_Multiboot2_Tag_EFI32bitSystemTablePtr_is_valid(
            (struct KernAux_Multiboot2_Tag_EFI32bitSystemTablePtr*)tag_base
        );
    case KERNAUX_MULTIBOOT2_TAGTYPE_EFI_64BIT_SYSTEM_TABLE_PTR:
        return KernAux_Multiboot2_Tag_EFI64bitSystemTablePtr_is_valid(
            (struct KernAux_Multiboot2_Tag_EFI64bitSystemTablePtr*)tag_base
        );
    case KERNAUX_MULTIBOOT2_TAGTYPE_SMBIOS_TABLES:
        return KernAux_Multiboot2_Tag_SMBIOSTables_is_valid(
            (struct KernAux_Multiboot2_Tag_SMBIOSTables*)tag_base
        );
    case KERNAUX_MULTIBOOT2_TAGTYPE_ACPI_OLD_RSDP:
        return KernAux_Multiboot2_Tag_ACPIOldRSDP_is_valid(
            (struct KernAux_Multiboot2_Tag_ACPIOldRSDP*)tag_base
        );
    case KERNAUX_MULTIBOOT2_TAGTYPE_ACPI_NEW_RSDP:
        return KernAux_Multiboot2_Tag_ACPINewRSDP_is_valid(
            (struct KernAux_Multiboot2_Tag_ACPINewRSDP*)tag_base
        );
    case KERNAUX_MULTIBOOT2_TAGTYPE_NETWORKING_INFO:
        return KernAux_Multiboot2_Tag_NetworkingInfo_is_valid(
            (struct KernAux_Multiboot2_Tag_NetworkingInfo*)tag_base
        );
    case KERNAUX_MULTIBOOT2_TAGTYPE_EFI_MEMORY_MAP:
        return KernAux_Multiboot2_Tag_EFIMemoryMap_is_valid(
            (struct KernAux_Multiboot2_Tag_EFIMemoryMap*)tag_base
        );
    case KERNAUX_MULTIBOOT2_TAGTYPE_EFI_BOOT_SERVICES_NOT_TERMINATED:
        return KernAux_Multiboot2_Tag_EFIBootServicesNotTerminated_is_valid(
            (struct KernAux_Multiboot2_Tag_EFIBootServicesNotTerminated*)tag_base
        );
    case KERNAUX_MULTIBOOT2_TAGTYPE_EFI_32BIT_IMAGE_HANDLE_PTR:
        return KernAux_Multiboot2_Tag_EFI32bitImageHandlePtr_is_valid(
            (struct KernAux_Multiboot2_Tag_EFI32bitImageHandlePtr*)tag_base
        );
    case KERNAUX_MULTIBOOT2_TAGTYPE_EFI_64BIT_IMAGE_HANDLE_PTR:
        return KernAux_Multiboot2_Tag_EFI64bitImageHandlePtr_is_valid(
            (struct KernAux_Multiboot2_Tag_EFI64bitImageHandlePtr*)tag_base
        );
    case KERNAUX_MULTIBOOT2_TAGTYPE_IMAGE_LOAD_BASE_PHYS_ADDR:
        return KernAux_Multiboot2_Tag_ImageLoadBasePhysAddr_is_valid(
            (struct KernAux_Multiboot2_Tag_ImageLoadBasePhysAddr*)tag_base
        );
    default:
        return false;
    }
}

bool KernAux_Multiboot2_Tag_None_is_valid(
    const struct KernAux_Multiboot2_Tag_None *const tag
) {
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_TAGTYPE_NONE &&
        tag->base.size == 8
    );
}

bool KernAux_Multiboot2_Tag_BootCmdLine_is_valid(
    const struct KernAux_Multiboot2_Tag_BootCmdLine *const tag
) {
    size_t index = 1;

    for (
        const char *ptr = tag->cmdline;
        *ptr && index < tag->base.size;
        ++ptr
    ) {
        ++index;
    }

    return (
        tag->base.type == KERNAUX_MULTIBOOT2_TAGTYPE_BOOT_CMD_LINE &&
        tag->base.size == 8 + index
    );
}

bool KernAux_Multiboot2_Tag_BootLoaderName_is_valid(
    const struct KernAux_Multiboot2_Tag_BootLoaderName *const tag
) {
    size_t index = 1;

    for (
        const char *ptr = tag->name;
        *ptr && index < tag->base.size;
        ++ptr
    ) {
        ++index;
    }

    return (
        tag->base.type == KERNAUX_MULTIBOOT2_TAGTYPE_BOOT_LOADER_NAME &&
        tag->base.size == 8 + index
    );
}

bool KernAux_Multiboot2_Tag_Module_is_valid(
    const struct KernAux_Multiboot2_Tag_Module *const tag
) {
    size_t index = 1;

    for (
        const char *ptr = tag->cmdline;
        *ptr && index < tag->base.size;
        ++ptr
    ) {
        ++index;
    }

    return (
        tag->base.type == KERNAUX_MULTIBOOT2_TAGTYPE_MODULE &&
        tag->base.size == 16 + index &&
        tag->mod_start < tag->mod_end
    );
}

bool KernAux_Multiboot2_Tag_BasicMemoryInfo_is_valid(
    const struct KernAux_Multiboot2_Tag_BasicMemoryInfo *const tag
) {
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_TAGTYPE_BASIC_MEMORY_INFO &&
        tag->base.size == 16
    );
}

bool KernAux_Multiboot2_Tag_BIOSBootDevice_is_valid(
    const struct KernAux_Multiboot2_Tag_BIOSBootDevice *const tag
) {
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_TAGTYPE_BIOS_BOOT_DEVICE &&
        tag->base.size == 20
    );
}

bool KernAux_Multiboot2_Tag_MemoryMap_is_valid(
    const struct KernAux_Multiboot2_Tag_MemoryMap *const tag
) {
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_TAGTYPE_MEMORY_MAP &&
        tag->base.size >= 16 &&
        tag->entry_size > 0 &&
        tag->entry_size % 8 == 0 &&
        (tag->base.size - 16) % tag->entry_size == 0
    );
}

bool KernAux_Multiboot2_Tag_VBEInfo_is_valid(
    const struct KernAux_Multiboot2_Tag_VBEInfo *const tag
) {
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_TAGTYPE_VBE_INFO &&
        tag->base.size == 784
    );
}

bool KernAux_Multiboot2_Tag_FramebufferInfo_is_valid(
    const struct KernAux_Multiboot2_Tag_FramebufferInfo *const tag
) {
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_TAGTYPE_FRAMEBUFFER_INFO &&
        tag->base.size >= 31
    );
}

bool KernAux_Multiboot2_Tag_ELFSymbols_is_valid(
    const struct KernAux_Multiboot2_Tag_ELFSymbols *const tag
) {
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_TAGTYPE_ELF_SYMBOLS &&
        tag->base.size >= 16 // &&
        // FIXME: division by zero in real-world data?
        // (tag->base.size - 16) % tag->ent_size == 0
    );
}

bool KernAux_Multiboot2_Tag_APMTable_is_valid(
    const struct KernAux_Multiboot2_Tag_APMTable *const tag
) {
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_TAGTYPE_APM_TABLE &&
        tag->base.size == 28
    );
}

bool KernAux_Multiboot2_Tag_EFI32bitSystemTablePtr_is_valid(
    const struct KernAux_Multiboot2_Tag_EFI32bitSystemTablePtr *const tag
) {
    return (
        tag->base.type ==
            KERNAUX_MULTIBOOT2_TAGTYPE_EFI_32BIT_SYSTEM_TABLE_PTR &&
        tag->base.size == 12
    );
}

bool KernAux_Multiboot2_Tag_EFI64bitSystemTablePtr_is_valid(
    const struct KernAux_Multiboot2_Tag_EFI64bitSystemTablePtr *const tag
) {
    return (
        tag->base.type ==
            KERNAUX_MULTIBOOT2_TAGTYPE_EFI_64BIT_SYSTEM_TABLE_PTR &&
        tag->base.size == 16
    );
}

bool KernAux_Multiboot2_Tag_SMBIOSTables_is_valid(
    const struct KernAux_Multiboot2_Tag_SMBIOSTables *const tag
) {
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_TAGTYPE_SMBIOS_TABLES &&
        tag->base.size >= 16
    );
}

bool KernAux_Multiboot2_Tag_ACPIOldRSDP_is_valid(
    const struct KernAux_Multiboot2_Tag_ACPIOldRSDP *const tag
) {
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_TAGTYPE_ACPI_OLD_RSDP &&
        tag->base.size >= 8
    );
}

bool KernAux_Multiboot2_Tag_ACPINewRSDP_is_valid(
    const struct KernAux_Multiboot2_Tag_ACPINewRSDP *const tag
) {
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_TAGTYPE_ACPI_NEW_RSDP &&
        tag->base.size >= 8
    );
}

bool KernAux_Multiboot2_Tag_NetworkingInfo_is_valid(
    const struct KernAux_Multiboot2_Tag_NetworkingInfo *const tag
) {
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_TAGTYPE_NETWORKING_INFO &&
        tag->base.size >= 8
    );
}

bool KernAux_Multiboot2_Tag_EFIMemoryMap_is_valid(
    const struct KernAux_Multiboot2_Tag_EFIMemoryMap *const tag
) {
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_TAGTYPE_EFI_MEMORY_MAP &&
        tag->base.size >= 16
    );
}

bool KernAux_Multiboot2_Tag_EFIBootServicesNotTerminated_is_valid(
    const struct KernAux_Multiboot2_Tag_EFIBootServicesNotTerminated *const tag
) {
    return (
        tag->base.type ==
            KERNAUX_MULTIBOOT2_TAGTYPE_EFI_BOOT_SERVICES_NOT_TERMINATED &&
        tag->base.size == 8
    );
}

bool KernAux_Multiboot2_Tag_EFI32bitImageHandlePtr_is_valid(
    const struct KernAux_Multiboot2_Tag_EFI32bitImageHandlePtr *const tag
) {
    return (
        tag->base.type ==
            KERNAUX_MULTIBOOT2_TAGTYPE_EFI_32BIT_IMAGE_HANDLE_PTR &&
        tag->base.size == 12
    );
}

bool KernAux_Multiboot2_Tag_EFI64bitImageHandlePtr_is_valid(
    const struct KernAux_Multiboot2_Tag_EFI64bitImageHandlePtr *const tag
) {
    return (
        tag->base.type ==
            KERNAUX_MULTIBOOT2_TAGTYPE_EFI_64BIT_IMAGE_HANDLE_PTR &&
        tag->base.size == 16
    );
}

bool KernAux_Multiboot2_Tag_ImageLoadBasePhysAddr_is_valid(
    const struct KernAux_Multiboot2_Tag_ImageLoadBasePhysAddr *const tag
) {
    return (
        tag->base.type ==
            KERNAUX_MULTIBOOT2_TAGTYPE_IMAGE_LOAD_BASE_PHYS_ADDR &&
        tag->base.size == 12
    );
}
