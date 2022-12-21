#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "../assert.h"

#include <kernaux/multiboot2.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

bool KernAux_Multiboot2_Info_is_valid(
    const struct KernAux_Multiboot2_Info *const multiboot2_info
) {
    KERNAUX_NOTNULL(multiboot2_info);

    if (multiboot2_info->total_size <
        sizeof(struct KernAux_Multiboot2_Info) +
        sizeof(struct KernAux_Multiboot2_ITag_None))
    {
        return false;
    }

    if (multiboot2_info->total_size % KERNAUX_MULTIBOOT2_TAG_ALIGN != 0) {
        return false;
    }

    const struct KernAux_Multiboot2_ITagBase *tag_base =
        (struct KernAux_Multiboot2_ITagBase*)
        KERNAUX_MULTIBOOT2_DATA(multiboot2_info);

    const struct KernAux_Multiboot2_ITagBase *none_tag_base = NULL;

    while (tag_base <
           (struct KernAux_Multiboot2_ITagBase*)
           ((uint8_t*)multiboot2_info + multiboot2_info->total_size))
    {
        if (!KernAux_Multiboot2_ITagBase_is_valid(tag_base)) return false;

        if (tag_base->type == KERNAUX_MULTIBOOT2_ITAG_NONE &&
            none_tag_base == NULL
        ) {
            none_tag_base = tag_base;
        }

        tag_base = KERNAUX_MULTIBOOT2_ITAG_NEXT(tag_base);
    }

    if (tag_base !=
        (struct KernAux_Multiboot2_ITagBase*)
        ((uint8_t*)multiboot2_info + multiboot2_info->total_size))
    {
        return false;
    }

    if (none_tag_base !=
        (struct KernAux_Multiboot2_ITagBase*)
        ((uint8_t*)tag_base -
         sizeof(struct KernAux_Multiboot2_ITag_None)))
    {
        return false;
    }

    return true;
}

bool KernAux_Multiboot2_ITagBase_is_valid(
    const struct KernAux_Multiboot2_ITagBase *const tag_base
) {
    KERNAUX_NOTNULL(tag_base);

    switch (tag_base->type) {
    case KERNAUX_MULTIBOOT2_ITAG_NONE:
        return KernAux_Multiboot2_ITag_None_is_valid(
            (struct KernAux_Multiboot2_ITag_None*)tag_base
        );
    case KERNAUX_MULTIBOOT2_ITAG_BOOT_CMD_LINE:
        return KernAux_Multiboot2_ITag_BootCmdLine_is_valid(
            (struct KernAux_Multiboot2_ITag_BootCmdLine*)tag_base
        );
    case KERNAUX_MULTIBOOT2_ITAG_BOOT_LOADER_NAME:
        return KernAux_Multiboot2_ITag_BootLoaderName_is_valid(
            (struct KernAux_Multiboot2_ITag_BootLoaderName*)tag_base
        );
    case KERNAUX_MULTIBOOT2_ITAG_MODULE:
        return KernAux_Multiboot2_ITag_Module_is_valid(
            (struct KernAux_Multiboot2_ITag_Module*)tag_base
        );
    case KERNAUX_MULTIBOOT2_ITAG_BASIC_MEMORY_INFO:
        return KernAux_Multiboot2_ITag_BasicMemoryInfo_is_valid(
            (struct KernAux_Multiboot2_ITag_BasicMemoryInfo*)tag_base
        );
    case KERNAUX_MULTIBOOT2_ITAG_BIOS_BOOT_DEVICE:
        return KernAux_Multiboot2_ITag_BIOSBootDevice_is_valid(
            (struct KernAux_Multiboot2_ITag_BIOSBootDevice*)tag_base
        );
    case KERNAUX_MULTIBOOT2_ITAG_MEMORY_MAP:
        return KernAux_Multiboot2_ITag_MemoryMap_is_valid(
            (struct KernAux_Multiboot2_ITag_MemoryMap*)tag_base
        );
    case KERNAUX_MULTIBOOT2_ITAG_VBE_INFO:
        return KernAux_Multiboot2_ITag_VBEInfo_is_valid(
            (struct KernAux_Multiboot2_ITag_VBEInfo*)tag_base
        );
    case KERNAUX_MULTIBOOT2_ITAG_FRAMEBUFFER_INFO:
        return KernAux_Multiboot2_ITag_FramebufferInfo_is_valid(
            (struct KernAux_Multiboot2_ITag_FramebufferInfo*)tag_base
        );
    case KERNAUX_MULTIBOOT2_ITAG_ELF_SYMBOLS:
        return KernAux_Multiboot2_ITag_ELFSymbols_is_valid(
            (struct KernAux_Multiboot2_ITag_ELFSymbols*)tag_base
        );
    case KERNAUX_MULTIBOOT2_ITAG_APM_TABLE:
        return KernAux_Multiboot2_ITag_APMTable_is_valid(
            (struct KernAux_Multiboot2_ITag_APMTable*)tag_base
        );
    case KERNAUX_MULTIBOOT2_ITAG_EFI_32BIT_SYSTEM_TABLE_PTR:
        return KernAux_Multiboot2_ITag_EFI32bitSystemTablePtr_is_valid(
            (struct KernAux_Multiboot2_ITag_EFI32bitSystemTablePtr*)tag_base
        );
    case KERNAUX_MULTIBOOT2_ITAG_EFI_64BIT_SYSTEM_TABLE_PTR:
        return KernAux_Multiboot2_ITag_EFI64bitSystemTablePtr_is_valid(
            (struct KernAux_Multiboot2_ITag_EFI64bitSystemTablePtr*)tag_base
        );
    case KERNAUX_MULTIBOOT2_ITAG_SMBIOS_TABLES:
        return KernAux_Multiboot2_ITag_SMBIOSTables_is_valid(
            (struct KernAux_Multiboot2_ITag_SMBIOSTables*)tag_base
        );
    case KERNAUX_MULTIBOOT2_ITAG_ACPI_OLD_RSDP:
        return KernAux_Multiboot2_ITag_ACPIOldRSDP_is_valid(
            (struct KernAux_Multiboot2_ITag_ACPIOldRSDP*)tag_base
        );
    case KERNAUX_MULTIBOOT2_ITAG_ACPI_NEW_RSDP:
        return KernAux_Multiboot2_ITag_ACPINewRSDP_is_valid(
            (struct KernAux_Multiboot2_ITag_ACPINewRSDP*)tag_base
        );
    case KERNAUX_MULTIBOOT2_ITAG_NETWORKING_INFO:
        return KernAux_Multiboot2_ITag_NetworkingInfo_is_valid(
            (struct KernAux_Multiboot2_ITag_NetworkingInfo*)tag_base
        );
    case KERNAUX_MULTIBOOT2_ITAG_EFI_MEMORY_MAP:
        return KernAux_Multiboot2_ITag_EFIMemoryMap_is_valid(
            (struct KernAux_Multiboot2_ITag_EFIMemoryMap*)tag_base
        );
    case KERNAUX_MULTIBOOT2_ITAG_EFI_BOOT_SERVICES_NOT_TERMINATED:
        return KernAux_Multiboot2_ITag_EFIBootServicesNotTerminated_is_valid(
            (struct KernAux_Multiboot2_ITag_EFIBootServicesNotTerminated*)
            tag_base
        );
    case KERNAUX_MULTIBOOT2_ITAG_EFI_32BIT_IMAGE_HANDLE_PTR:
        return KernAux_Multiboot2_ITag_EFI32bitImageHandlePtr_is_valid(
            (struct KernAux_Multiboot2_ITag_EFI32bitImageHandlePtr*)tag_base
        );
    case KERNAUX_MULTIBOOT2_ITAG_EFI_64BIT_IMAGE_HANDLE_PTR:
        return KernAux_Multiboot2_ITag_EFI64bitImageHandlePtr_is_valid(
            (struct KernAux_Multiboot2_ITag_EFI64bitImageHandlePtr*)tag_base
        );
    case KERNAUX_MULTIBOOT2_ITAG_IMAGE_LOAD_BASE_PHYS_ADDR:
        return KernAux_Multiboot2_ITag_ImageLoadBasePhysAddr_is_valid(
            (struct KernAux_Multiboot2_ITag_ImageLoadBasePhysAddr*)tag_base
        );
    default:
        return false;
    }
}

bool KernAux_Multiboot2_ITag_None_is_valid(
    const struct KernAux_Multiboot2_ITag_None *const tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_ITAG_NONE &&
        tag->base.size == 8
    );
}

bool KernAux_Multiboot2_ITag_BootCmdLine_is_valid(
    const struct KernAux_Multiboot2_ITag_BootCmdLine *const tag
) {
    KERNAUX_NOTNULL(tag);

    size_t index = 1;

    for (
        const char *ptr = (char*)KERNAUX_MULTIBOOT2_DATA(tag);
        *ptr && index < tag->base.size;
        ++ptr
    ) {
        ++index;
    }

    return (
        tag->base.type == KERNAUX_MULTIBOOT2_ITAG_BOOT_CMD_LINE &&
        tag->base.size == 8 + index
    );
}

bool KernAux_Multiboot2_ITag_BootLoaderName_is_valid(
    const struct KernAux_Multiboot2_ITag_BootLoaderName *const tag
) {
    KERNAUX_NOTNULL(tag);

    size_t index = 1;

    for (
        const char *ptr = (char*)KERNAUX_MULTIBOOT2_DATA(tag);
        *ptr && index < tag->base.size;
        ++ptr
    ) {
        ++index;
    }

    return (
        tag->base.type == KERNAUX_MULTIBOOT2_ITAG_BOOT_LOADER_NAME &&
        tag->base.size == 8 + index
    );
}

bool KernAux_Multiboot2_ITag_Module_is_valid(
    const struct KernAux_Multiboot2_ITag_Module *const tag
) {
    KERNAUX_NOTNULL(tag);

    size_t index = 1;

    for (
        const char *ptr = (char*)KERNAUX_MULTIBOOT2_DATA(tag);
        *ptr && index < tag->base.size;
        ++ptr
    ) {
        ++index;
    }

    return (
        tag->base.type == KERNAUX_MULTIBOOT2_ITAG_MODULE &&
        tag->base.size == 16 + index &&
        tag->mod_start < tag->mod_end
    );
}

bool KernAux_Multiboot2_ITag_BasicMemoryInfo_is_valid(
    const struct KernAux_Multiboot2_ITag_BasicMemoryInfo *const tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_ITAG_BASIC_MEMORY_INFO &&
        tag->base.size == 16
    );
}

bool KernAux_Multiboot2_ITag_BIOSBootDevice_is_valid(
    const struct KernAux_Multiboot2_ITag_BIOSBootDevice *const tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_ITAG_BIOS_BOOT_DEVICE &&
        tag->base.size == 20
    );
}

bool KernAux_Multiboot2_ITag_MemoryMap_is_valid(
    const struct KernAux_Multiboot2_ITag_MemoryMap *const tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_ITAG_MEMORY_MAP &&
        tag->base.size >= 16 &&
        tag->entry_size > 0 &&
        tag->entry_size % 8 == 0 &&
        (tag->base.size - 16) % tag->entry_size == 0
    );
}

bool KernAux_Multiboot2_ITag_VBEInfo_is_valid(
    const struct KernAux_Multiboot2_ITag_VBEInfo *const tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_ITAG_VBE_INFO &&
        tag->base.size == 784
    );
}

bool KernAux_Multiboot2_ITag_FramebufferInfo_is_valid(
    const struct KernAux_Multiboot2_ITag_FramebufferInfo *const tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_ITAG_FRAMEBUFFER_INFO &&
        tag->base.size >= 32
    );
}

bool KernAux_Multiboot2_ITag_ELFSymbols_is_valid(
    const struct KernAux_Multiboot2_ITag_ELFSymbols *const tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_ITAG_ELF_SYMBOLS &&
        tag->base.size >= 20 &&
        (
            tag->entsize == 0 ||
            (tag->base.size - 20) % tag->entsize == 0
        )
    );
}

bool KernAux_Multiboot2_ITag_APMTable_is_valid(
    const struct KernAux_Multiboot2_ITag_APMTable *const tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_ITAG_APM_TABLE &&
        tag->base.size == 28
    );
}

bool KernAux_Multiboot2_ITag_EFI32bitSystemTablePtr_is_valid(
    const struct KernAux_Multiboot2_ITag_EFI32bitSystemTablePtr *const tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_ITAG_EFI_32BIT_SYSTEM_TABLE_PTR &&
        tag->base.size == 12
    );
}

bool KernAux_Multiboot2_ITag_EFI64bitSystemTablePtr_is_valid(
    const struct KernAux_Multiboot2_ITag_EFI64bitSystemTablePtr *const tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_ITAG_EFI_64BIT_SYSTEM_TABLE_PTR &&
        tag->base.size == 16
    );
}

bool KernAux_Multiboot2_ITag_SMBIOSTables_is_valid(
    const struct KernAux_Multiboot2_ITag_SMBIOSTables *const tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_ITAG_SMBIOS_TABLES &&
        tag->base.size >= 16
    );
}

bool KernAux_Multiboot2_ITag_ACPIOldRSDP_is_valid(
    const struct KernAux_Multiboot2_ITag_ACPIOldRSDP *const tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_ITAG_ACPI_OLD_RSDP &&
        tag->base.size >= 8
    );
}

bool KernAux_Multiboot2_ITag_ACPINewRSDP_is_valid(
    const struct KernAux_Multiboot2_ITag_ACPINewRSDP *const tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_ITAG_ACPI_NEW_RSDP &&
        tag->base.size >= 8
    );
}

bool KernAux_Multiboot2_ITag_NetworkingInfo_is_valid(
    const struct KernAux_Multiboot2_ITag_NetworkingInfo *const tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_ITAG_NETWORKING_INFO &&
        tag->base.size >= 8
    );
}

bool KernAux_Multiboot2_ITag_EFIMemoryMap_is_valid(
    const struct KernAux_Multiboot2_ITag_EFIMemoryMap *const tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_ITAG_EFI_MEMORY_MAP &&
        tag->base.size >= 16
    );
}

bool KernAux_Multiboot2_ITag_EFIBootServicesNotTerminated_is_valid(
    const struct KernAux_Multiboot2_ITag_EFIBootServicesNotTerminated *const tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type ==
            KERNAUX_MULTIBOOT2_ITAG_EFI_BOOT_SERVICES_NOT_TERMINATED &&
        tag->base.size == 8
    );
}

bool KernAux_Multiboot2_ITag_EFI32bitImageHandlePtr_is_valid(
    const struct KernAux_Multiboot2_ITag_EFI32bitImageHandlePtr *const tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_ITAG_EFI_32BIT_IMAGE_HANDLE_PTR &&
        tag->base.size == 12
    );
}

bool KernAux_Multiboot2_ITag_EFI64bitImageHandlePtr_is_valid(
    const struct KernAux_Multiboot2_ITag_EFI64bitImageHandlePtr *const tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_ITAG_EFI_64BIT_IMAGE_HANDLE_PTR &&
        tag->base.size == 16
    );
}

bool KernAux_Multiboot2_ITag_ImageLoadBasePhysAddr_is_valid(
    const struct KernAux_Multiboot2_ITag_ImageLoadBasePhysAddr *const tag
) {
    KERNAUX_NOTNULL(tag);
    return (
        tag->base.type == KERNAUX_MULTIBOOT2_ITAG_IMAGE_LOAD_BASE_PHYS_ADDR &&
        tag->base.size == 12
    );
}
