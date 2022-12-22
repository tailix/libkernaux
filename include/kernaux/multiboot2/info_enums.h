#ifndef KERNAUX_INCLUDED_MULTIBOOT2_INFO_ENUMS
#define KERNAUX_INCLUDED_MULTIBOOT2_INFO_ENUMS

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/multiboot2.h>

#include <stdint.h>

#define KERNAUX_MULTIBOOT2_ITAG_NONE                             0
#define KERNAUX_MULTIBOOT2_ITAG_BOOT_CMD_LINE                    1
#define KERNAUX_MULTIBOOT2_ITAG_BOOT_LOADER_NAME                 2
#define KERNAUX_MULTIBOOT2_ITAG_MODULE                           3
#define KERNAUX_MULTIBOOT2_ITAG_BASIC_MEMORY_INFO                4
#define KERNAUX_MULTIBOOT2_ITAG_BIOS_BOOT_DEVICE                 5
#define KERNAUX_MULTIBOOT2_ITAG_MEMORY_MAP                       6
#define KERNAUX_MULTIBOOT2_ITAG_VBE_INFO                         7
#define KERNAUX_MULTIBOOT2_ITAG_FRAMEBUFFER_INFO                 8
#define KERNAUX_MULTIBOOT2_ITAG_ELF_SYMBOLS                      9
#define KERNAUX_MULTIBOOT2_ITAG_APM_TABLE                        10
#define KERNAUX_MULTIBOOT2_ITAG_EFI_32BIT_SYSTEM_TABLE_PTR       11
#define KERNAUX_MULTIBOOT2_ITAG_EFI_64BIT_SYSTEM_TABLE_PTR       12
#define KERNAUX_MULTIBOOT2_ITAG_SMBIOS_TABLES                    13
#define KERNAUX_MULTIBOOT2_ITAG_ACPI_OLD_RSDP                    14
#define KERNAUX_MULTIBOOT2_ITAG_ACPI_NEW_RSDP                    15
#define KERNAUX_MULTIBOOT2_ITAG_NETWORKING_INFO                  16
#define KERNAUX_MULTIBOOT2_ITAG_EFI_MEMORY_MAP                   17
#define KERNAUX_MULTIBOOT2_ITAG_EFI_BOOT_SERVICES_NOT_TERMINATED 18
#define KERNAUX_MULTIBOOT2_ITAG_EFI_32BIT_IMAGE_HANDLE_PTR       19
#define KERNAUX_MULTIBOOT2_ITAG_EFI_64BIT_IMAGE_HANDLE_PTR       20
#define KERNAUX_MULTIBOOT2_ITAG_IMAGE_LOAD_BASE_PHYS_ADDR        21

#define KERNAUX_MULTIBOOT2_MEMMAP_AVAILABLE        1
#define KERNAUX_MULTIBOOT2_MEMMAP_RESERVED         2
#define KERNAUX_MULTIBOOT2_MEMMAP_ACPI_RECLAIMABLE 3
#define KERNAUX_MULTIBOOT2_MEMMAP_NVS              4
#define KERNAUX_MULTIBOOT2_MEMMAP_BADRAM           5

const char *KernAux_Multiboot2_ITag_to_str(uint32_t tag_type);
const char*
KernAux_Multiboot2_ITag_MemoryMap_EntryBase_Type_to_str(uint32_t type);

#ifdef __cplusplus
}
#endif

#endif
