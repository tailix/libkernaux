#ifndef KERNAUX_INCLUDED_MULTIBOOT2
#define KERNAUX_INCLUDED_MULTIBOOT2

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#define KERNAUX_MULTIBOOT2_MAGIC 0x36d76289

#define KERNAUX_MULTIBOOT2_DATA(ptr) (((uint8_t*)(ptr)) + sizeof(*(ptr)))

/***********************
 * Header common types *
 ***********************/

enum KernAux_Multiboot2_HTag {
    KERNAUX_MULTIBOOT2_HTAG_NONE = 0,
    KERNAUX_MULTIBOOT2_HTAG_INFO_REQ = 1,
    KERNAUX_MULTIBOOT2_HTAG_ADDR = 2,
    KERNAUX_MULTIBOOT2_HTAG_ENTRY_ADDR = 3,
    KERNAUX_MULTIBOOT2_HTAG_FLAGS = 4,
    KERNAUX_MULTIBOOT2_HTAG_FRAMEBUFFER = 5,
    KERNAUX_MULTIBOOT2_HTAG_MODULE_ALIGN = 6,
    KERNAUX_MULTIBOOT2_HTAG_EFI_BOOT_SERVICES = 7,
    KERNAUX_MULTIBOOT2_HTAG_EFI_I386_ENTRY_ADDR = 8,
    KERNAUX_MULTIBOOT2_HTAG_EFI_AMD64_ENTRY_ADDR = 9,
    KERNAUX_MULTIBOOT2_HTAG_RELOCATABLE_HEADER = 10,
};

struct KernAux_Multiboot2_Header {
    unsigned magic      : 32;
    unsigned arch       : 32;
    unsigned total_size : 32;
    unsigned checksum   : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_HTagBase {
    enum KernAux_Multiboot2_HTag type : 16;
    unsigned flags                    : 16;
    unsigned size                     : 32;
}
__attribute__((packed));

/****************************
 * Information common types *
 ****************************/

enum KernAux_Multiboot2_ITag {
    KERNAUX_MULTIBOOT2_ITAG_NONE = 0,
    KERNAUX_MULTIBOOT2_ITAG_BOOT_CMD_LINE = 1,
    KERNAUX_MULTIBOOT2_ITAG_BOOT_LOADER_NAME = 2,
    KERNAUX_MULTIBOOT2_ITAG_MODULE = 3,
    KERNAUX_MULTIBOOT2_ITAG_BASIC_MEMORY_INFO = 4,
    KERNAUX_MULTIBOOT2_ITAG_BIOS_BOOT_DEVICE = 5,
    KERNAUX_MULTIBOOT2_ITAG_MEMORY_MAP = 6,
    KERNAUX_MULTIBOOT2_ITAG_VBE_INFO = 7,
    KERNAUX_MULTIBOOT2_ITAG_FRAMEBUFFER_INFO = 8,
    KERNAUX_MULTIBOOT2_ITAG_ELF_SYMBOLS = 9,
    KERNAUX_MULTIBOOT2_ITAG_APM_TABLE = 10,
    KERNAUX_MULTIBOOT2_ITAG_EFI_32BIT_SYSTEM_TABLE_PTR = 11,
    KERNAUX_MULTIBOOT2_ITAG_EFI_64BIT_SYSTEM_TABLE_PTR = 12,
    KERNAUX_MULTIBOOT2_ITAG_SMBIOS_TABLES = 13,
    KERNAUX_MULTIBOOT2_ITAG_ACPI_OLD_RSDP = 14,
    KERNAUX_MULTIBOOT2_ITAG_ACPI_NEW_RSDP = 15,
    KERNAUX_MULTIBOOT2_ITAG_NETWORKING_INFO = 16,
    KERNAUX_MULTIBOOT2_ITAG_EFI_MEMORY_MAP = 17,
    KERNAUX_MULTIBOOT2_ITAG_EFI_BOOT_SERVICES_NOT_TERMINATED = 18,
    KERNAUX_MULTIBOOT2_ITAG_EFI_32BIT_IMAGE_HANDLE_PTR = 19,
    KERNAUX_MULTIBOOT2_ITAG_EFI_64BIT_IMAGE_HANDLE_PTR = 20,
    KERNAUX_MULTIBOOT2_ITAG_IMAGE_LOAD_BASE_PHYS_ADDR = 21,
};

struct KernAux_Multiboot2_Info {
    unsigned total_size : 32;
    unsigned reserved1  : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITagBase {
    enum KernAux_Multiboot2_ITag type : 32;
    unsigned size                     : 32;
}
__attribute__((packed));

/******************************
 * Information tag structures *
 ******************************/

struct KernAux_Multiboot2_ITag_None {
    // type = 0
    // size = 8
    struct KernAux_Multiboot2_ITagBase base;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_BootCmdLine {
    // type = 1
    // size = ?
    struct KernAux_Multiboot2_ITagBase base;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_BootLoaderName {
    // type = 2
    // size = ?
    struct KernAux_Multiboot2_ITagBase base;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_Module {
    // type = 3
    // size = ?
    struct KernAux_Multiboot2_ITagBase base;

    unsigned mod_start : 32;
    unsigned mod_end   : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_BasicMemoryInfo {
    // type = 4
    // size = 16
    struct KernAux_Multiboot2_ITagBase base;

    unsigned mem_lower : 32;
    unsigned mem_upper : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_BIOSBootDevice {
    // type = 5
    // size = 20
    struct KernAux_Multiboot2_ITagBase base;

    unsigned bios_dev      : 32;
    unsigned partition     : 32;
    unsigned sub_partition : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_MemoryMap {
    // type = 6
    // size = ?
    struct KernAux_Multiboot2_ITagBase base;

    unsigned entry_size    : 32;
    unsigned entry_version : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_VBEInfo {
    // type = 7
    // size = 784
    struct KernAux_Multiboot2_ITagBase base;

    unsigned vbe_mode          : 16;
    unsigned vbe_interface_seg : 16;
    unsigned vbe_interface_off : 16;
    unsigned vbe_interface_len : 16;
    unsigned char vbe_control_info[512];
    unsigned char vbe_mode_info[256];
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_FramebufferInfo {
    // type = 8
    // size = ?
    struct KernAux_Multiboot2_ITagBase base;

    unsigned long long framebuffer_addr : 64;
    unsigned framebuffer_pitch          : 32;
    unsigned framebuffer_width          : 32;
    unsigned framebuffer_height         : 32;
    unsigned framebuffer_bpp            : 8;
    unsigned framebuffer_type           : 8;
    unsigned reserved1                  : 8;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_ELFSymbols {
    // type = 9
    // size = ?
    struct KernAux_Multiboot2_ITagBase base;

    unsigned num       : 16;
    unsigned ent_size  : 16;
    unsigned shndx     : 16;
    unsigned reserved1 : 16;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_APMTable {
    // type = 10
    // size = 28
    struct KernAux_Multiboot2_ITagBase base;

    unsigned version     : 16;
    unsigned cseg        : 16;
    unsigned offset      : 32;
    unsigned cseg_16     : 16;
    unsigned dseg        : 16;
    unsigned flags       : 16;
    unsigned cseg_len    : 16;
    unsigned cseg_16_len : 16;
    unsigned dseg_len    : 16;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_EFI32bitSystemTablePtr {
    // type = 11
    // size = 12
    struct KernAux_Multiboot2_ITagBase base;

    unsigned pointer : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_EFI64bitSystemTablePtr {
    // type = 12
    // size = 16
    struct KernAux_Multiboot2_ITagBase base;

    unsigned long long pointer : 64;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_SMBIOSTables {
    // type = 13
    // size = ?
    struct KernAux_Multiboot2_ITagBase base;

    unsigned major : 8;
    unsigned minor : 8;
    unsigned char reserved1[6];
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_ACPIOldRSDP {
    // type = 14
    // size = ?
    struct KernAux_Multiboot2_ITagBase base;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_ACPINewRSDP {
    // type = 15
    // size = ?
    struct KernAux_Multiboot2_ITagBase base;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_NetworkingInfo {
    // type = 16
    // size = ?
    struct KernAux_Multiboot2_ITagBase base;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_EFIMemoryMap {
    // type = 17
    // size = ?
    struct KernAux_Multiboot2_ITagBase base;

    unsigned descriptor_size    : 32;
    unsigned descriptor_version : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_EFIBootServicesNotTerminated {
    // type = 18
    // size = 8
    struct KernAux_Multiboot2_ITagBase base;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_EFI32bitImageHandlePtr {
    // type = 19
    // size = 12
    struct KernAux_Multiboot2_ITagBase base;

    unsigned pointer : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_EFI64bitImageHandlePtr {
    // type = 20
    // size = 16
    struct KernAux_Multiboot2_ITagBase base;

    unsigned long long pointer : 64;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_ImageLoadBasePhysAddr {
    // type = 21
    // size = 12
    struct KernAux_Multiboot2_ITagBase base;

    unsigned load_base_addr : 32;
}
__attribute__((packed));

/*************************************
 * Information additional structures *
 *************************************/

struct KernAux_Multiboot2_ITag_MemoryMap_EntryBase {
    unsigned long long base_addr : 64;
    unsigned long long length    : 64;
    unsigned type                : 32;
    unsigned reserved1           : 32;
}
__attribute__((packed));

/********************************
 * Information helper functions *
 ********************************/

const struct KernAux_Multiboot2_ITagBase
*KernAux_Multiboot2_Info_first_tag_with_type(
    const struct KernAux_Multiboot2_Info *multiboot2_info,
    enum KernAux_Multiboot2_ITag tag_type
);

const struct KernAux_Multiboot2_ITagBase
*KernAux_Multiboot2_Info_tag_with_type_after(
    const struct KernAux_Multiboot2_Info *multiboot2_info,
    enum KernAux_Multiboot2_ITag tag_type,
    const struct KernAux_Multiboot2_ITagBase *after_tag
);

const char *KernAux_Multiboot2_Info_boot_cmd_line(
    const struct KernAux_Multiboot2_Info *multiboot2_info
);

/*******************************
 * Information print functions *
 *******************************/

void KernAux_Multiboot2_Info_print(
    const struct KernAux_Multiboot2_Info *multiboot2_info,
    void (*printf)(const char *format, ...)
);

void KernAux_Multiboot2_ITagBase_print(
    const struct KernAux_Multiboot2_ITagBase *tag_base,
    void (*printf)(const char *format, ...)
);

/************************************
 * Information validation functions *
 ************************************/

bool KernAux_Multiboot2_Info_is_valid(
    const struct KernAux_Multiboot2_Info *multiboot2_info
);

bool KernAux_Multiboot2_ITagBase_is_valid(
    const struct KernAux_Multiboot2_ITagBase *tag_base
);

bool KernAux_Multiboot2_ITag_None_is_valid(
    const struct KernAux_Multiboot2_ITag_None *tag
);

bool KernAux_Multiboot2_ITag_BootCmdLine_is_valid(
    const struct KernAux_Multiboot2_ITag_BootCmdLine *tag
);

bool KernAux_Multiboot2_ITag_BootLoaderName_is_valid(
    const struct KernAux_Multiboot2_ITag_BootLoaderName *tag
);

bool KernAux_Multiboot2_ITag_Module_is_valid(
    const struct KernAux_Multiboot2_ITag_Module *tag
);

bool KernAux_Multiboot2_ITag_BasicMemoryInfo_is_valid(
    const struct KernAux_Multiboot2_ITag_BasicMemoryInfo *tag
);

bool KernAux_Multiboot2_ITag_BIOSBootDevice_is_valid(
    const struct KernAux_Multiboot2_ITag_BIOSBootDevice *tag
);

bool KernAux_Multiboot2_ITag_MemoryMap_is_valid(
    const struct KernAux_Multiboot2_ITag_MemoryMap *tag
);

bool KernAux_Multiboot2_ITag_VBEInfo_is_valid(
    const struct KernAux_Multiboot2_ITag_VBEInfo *tag
);

bool KernAux_Multiboot2_ITag_FramebufferInfo_is_valid(
    const struct KernAux_Multiboot2_ITag_FramebufferInfo *tag
);

bool KernAux_Multiboot2_ITag_ELFSymbols_is_valid(
    const struct KernAux_Multiboot2_ITag_ELFSymbols *tag
);

bool KernAux_Multiboot2_ITag_APMTable_is_valid(
    const struct KernAux_Multiboot2_ITag_APMTable *tag
);

bool KernAux_Multiboot2_ITag_EFI32bitSystemTablePtr_is_valid(
    const struct KernAux_Multiboot2_ITag_EFI32bitSystemTablePtr *tag
);

bool KernAux_Multiboot2_ITag_EFI64bitSystemTablePtr_is_valid(
    const struct KernAux_Multiboot2_ITag_EFI64bitSystemTablePtr *tag
);

bool KernAux_Multiboot2_ITag_SMBIOSTables_is_valid(
    const struct KernAux_Multiboot2_ITag_SMBIOSTables *tag
);

bool KernAux_Multiboot2_ITag_ACPIOldRSDP_is_valid(
    const struct KernAux_Multiboot2_ITag_ACPIOldRSDP *tag
);

bool KernAux_Multiboot2_ITag_ACPINewRSDP_is_valid(
    const struct KernAux_Multiboot2_ITag_ACPINewRSDP *tag
);

bool KernAux_Multiboot2_ITag_NetworkingInfo_is_valid(
    const struct KernAux_Multiboot2_ITag_NetworkingInfo *tag
);

bool KernAux_Multiboot2_ITag_EFIMemoryMap_is_valid(
    const struct KernAux_Multiboot2_ITag_EFIMemoryMap *tag
);

bool KernAux_Multiboot2_ITag_EFIBootServicesNotTerminated_is_valid(
    const struct KernAux_Multiboot2_ITag_EFIBootServicesNotTerminated *tag
);

bool KernAux_Multiboot2_ITag_EFI32bitImageHandlePtr_is_valid(
    const struct KernAux_Multiboot2_ITag_EFI32bitImageHandlePtr *tag
);

bool KernAux_Multiboot2_ITag_EFI64bitImageHandlePtr_is_valid(
    const struct KernAux_Multiboot2_ITag_EFI64bitImageHandlePtr *tag
);

bool KernAux_Multiboot2_ITag_ImageLoadBasePhysAddr_is_valid(
    const struct KernAux_Multiboot2_ITag_ImageLoadBasePhysAddr *tag
);

#ifdef __cplusplus
}
#endif

#endif
