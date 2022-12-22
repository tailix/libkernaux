#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/multiboot2.h>

#include <stddef.h>
#include <stdint.h>

const char *KernAux_Multiboot2_ITag_to_str(const uint32_t tag_type)
{
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

const char*
KernAux_Multiboot2_ITag_MemoryMap_EntryBase_Type_to_str(const uint32_t type)
{
    switch (type) {
    case KERNAUX_MULTIBOOT2_MEMMAP_AVAILABLE:
        return "available";
    case KERNAUX_MULTIBOOT2_MEMMAP_RESERVED:
        return "reserved";
    case KERNAUX_MULTIBOOT2_MEMMAP_ACPI_RECLAIMABLE:
        return "ACPI reclaimable";
    case KERNAUX_MULTIBOOT2_MEMMAP_NVS:
        return "ACPI Non-Volatile Storage";
    case KERNAUX_MULTIBOOT2_MEMMAP_BADRAM:
        return "bad RAM";
    default:
        return NULL;
    }
}
