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
    uint32_t magic;
    uint32_t arch;
    uint32_t total_size;
    uint32_t checksum;
}
__attribute__((packed));

struct KernAux_Multiboot2_HTagBase {
    enum KernAux_Multiboot2_HTag type : 16;
    uint16_t flags;
    uint32_t size;
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

struct KernAux_Multiboot2 {
    unsigned total_size : 32;
    unsigned reserved1  : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_TagBase {
    enum KernAux_Multiboot2_ITag type : 32;
    unsigned size                     : 32;
}
__attribute__((packed));

/******************
 * Tag structures *
 ******************/

struct KernAux_Multiboot2_Tag_None {
    // type = 0
    // size = 8
    struct KernAux_Multiboot2_TagBase base;
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_BootCmdLine {
    // type = 1
    // size = ?
    struct KernAux_Multiboot2_TagBase base;
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_BootLoaderName {
    // type = 2
    // size = ?
    struct KernAux_Multiboot2_TagBase base;
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_Module {
    // type = 3
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    unsigned mod_start : 32;
    unsigned mod_end   : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_BasicMemoryInfo {
    // type = 4
    // size = 16
    struct KernAux_Multiboot2_TagBase base;

    unsigned mem_lower : 32;
    unsigned mem_upper : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_BIOSBootDevice {
    // type = 5
    // size = 20
    struct KernAux_Multiboot2_TagBase base;

    unsigned bios_dev      : 32;
    unsigned partition     : 32;
    unsigned sub_partition : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_MemoryMap {
    // type = 6
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    unsigned entry_size    : 32;
    unsigned entry_version : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_VBEInfo {
    // type = 7
    // size = 784
    struct KernAux_Multiboot2_TagBase base;

    unsigned vbe_mode          : 16;
    unsigned vbe_interface_seg : 16;
    unsigned vbe_interface_off : 16;
    unsigned vbe_interface_len : 16;
    unsigned char vbe_control_info[512];
    unsigned char vbe_mode_info[256];
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_FramebufferInfo {
    // type = 8
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    unsigned long long framebuffer_addr : 64;
    unsigned framebuffer_pitch          : 32;
    unsigned framebuffer_width          : 32;
    unsigned framebuffer_height         : 32;
    unsigned framebuffer_bpp            : 8;
    unsigned framebuffer_type           : 8;
    unsigned reserved1                  : 8;
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_ELFSymbols {
    // type = 9
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    unsigned num       : 16;
    unsigned ent_size  : 16;
    unsigned shndx     : 16;
    unsigned reserved1 : 16;
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_APMTable {
    // type = 10
    // size = 28
    struct KernAux_Multiboot2_TagBase base;

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

struct KernAux_Multiboot2_Tag_EFI32bitSystemTablePtr {
    // type = 11
    // size = 12
    struct KernAux_Multiboot2_TagBase base;

    unsigned pointer : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_EFI64bitSystemTablePtr {
    // type = 12
    // size = 16
    struct KernAux_Multiboot2_TagBase base;

    unsigned long long pointer : 64;
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_SMBIOSTables {
    // type = 13
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    unsigned major : 8;
    unsigned minor : 8;
    unsigned char reserved1[6];
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_ACPIOldRSDP {
    // type = 14
    // size = ?
    struct KernAux_Multiboot2_TagBase base;
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_ACPINewRSDP {
    // type = 15
    // size = ?
    struct KernAux_Multiboot2_TagBase base;
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_NetworkingInfo {
    // type = 16
    // size = ?
    struct KernAux_Multiboot2_TagBase base;
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_EFIMemoryMap {
    // type = 17
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    unsigned descriptor_size    : 32;
    unsigned descriptor_version : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_EFIBootServicesNotTerminated {
    // type = 18
    // size = 8
    struct KernAux_Multiboot2_TagBase base;
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_EFI32bitImageHandlePtr {
    // type = 19
    // size = 12
    struct KernAux_Multiboot2_TagBase base;

    unsigned pointer : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_EFI64bitImageHandlePtr {
    // type = 20
    // size = 16
    struct KernAux_Multiboot2_TagBase base;

    unsigned long long pointer : 64;
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_ImageLoadBasePhysAddr {
    // type = 21
    // size = 12
    struct KernAux_Multiboot2_TagBase base;

    unsigned load_base_addr : 32;
}
__attribute__((packed));

/*************************
 * Additional structures *
 *************************/

struct KernAux_Multiboot2_Tag_MemoryMap_EntryBase {
    unsigned long long base_addr : 64;
    unsigned long long length    : 64;
    unsigned type                : 32;
    unsigned reserved1           : 32;
}
__attribute__((packed));

/********************
 * Helper functions *
 ********************/

const struct KernAux_Multiboot2_TagBase *KernAux_Multiboot2_first_tag_with_type(
    const struct KernAux_Multiboot2 *multiboot2,
    enum KernAux_Multiboot2_ITag tag_type
);

const struct KernAux_Multiboot2_TagBase *KernAux_Multiboot2_tag_with_type_after(
    const struct KernAux_Multiboot2 *multiboot2,
    enum KernAux_Multiboot2_ITag tag_type,
    const struct KernAux_Multiboot2_TagBase *after_tag
);

const char *KernAux_Multiboot2_boot_cmd_line(
    const struct KernAux_Multiboot2 *multiboot2
);

/*******************
 * Print functions *
 *******************/

void KernAux_Multiboot2_print(
    const struct KernAux_Multiboot2 *multiboot2,
    void (*printf)(const char *format, ...)
);

void KernAux_Multiboot2_TagBase_print(
    const struct KernAux_Multiboot2_TagBase *tag_base,
    void (*printf)(const char *format, ...)
);

/************************
 * Validation functions *
 ************************/

bool KernAux_Multiboot2_is_valid(
    const struct KernAux_Multiboot2 *multiboot2
);

bool KernAux_Multiboot2_TagBase_is_valid(
    const struct KernAux_Multiboot2_TagBase *tag_base
);

bool KernAux_Multiboot2_Tag_None_is_valid(
    const struct KernAux_Multiboot2_Tag_None *tag
);

bool KernAux_Multiboot2_Tag_BootCmdLine_is_valid(
    const struct KernAux_Multiboot2_Tag_BootCmdLine *tag
);

bool KernAux_Multiboot2_Tag_BootLoaderName_is_valid(
    const struct KernAux_Multiboot2_Tag_BootLoaderName *tag
);

bool KernAux_Multiboot2_Tag_Module_is_valid(
    const struct KernAux_Multiboot2_Tag_Module *tag
);

bool KernAux_Multiboot2_Tag_BasicMemoryInfo_is_valid(
    const struct KernAux_Multiboot2_Tag_BasicMemoryInfo *tag
);

bool KernAux_Multiboot2_Tag_BIOSBootDevice_is_valid(
    const struct KernAux_Multiboot2_Tag_BIOSBootDevice *tag
);

bool KernAux_Multiboot2_Tag_MemoryMap_is_valid(
    const struct KernAux_Multiboot2_Tag_MemoryMap *tag
);

bool KernAux_Multiboot2_Tag_VBEInfo_is_valid(
    const struct KernAux_Multiboot2_Tag_VBEInfo *tag
);

bool KernAux_Multiboot2_Tag_FramebufferInfo_is_valid(
    const struct KernAux_Multiboot2_Tag_FramebufferInfo *tag
);

bool KernAux_Multiboot2_Tag_ELFSymbols_is_valid(
    const struct KernAux_Multiboot2_Tag_ELFSymbols *tag
);

bool KernAux_Multiboot2_Tag_APMTable_is_valid(
    const struct KernAux_Multiboot2_Tag_APMTable *tag
);

bool KernAux_Multiboot2_Tag_EFI32bitSystemTablePtr_is_valid(
    const struct KernAux_Multiboot2_Tag_EFI32bitSystemTablePtr *tag
);

bool KernAux_Multiboot2_Tag_EFI64bitSystemTablePtr_is_valid(
    const struct KernAux_Multiboot2_Tag_EFI64bitSystemTablePtr *tag
);

bool KernAux_Multiboot2_Tag_SMBIOSTables_is_valid(
    const struct KernAux_Multiboot2_Tag_SMBIOSTables *tag
);

bool KernAux_Multiboot2_Tag_ACPIOldRSDP_is_valid(
    const struct KernAux_Multiboot2_Tag_ACPIOldRSDP *tag
);

bool KernAux_Multiboot2_Tag_ACPINewRSDP_is_valid(
    const struct KernAux_Multiboot2_Tag_ACPINewRSDP *tag
);

bool KernAux_Multiboot2_Tag_NetworkingInfo_is_valid(
    const struct KernAux_Multiboot2_Tag_NetworkingInfo *tag
);

bool KernAux_Multiboot2_Tag_EFIMemoryMap_is_valid(
    const struct KernAux_Multiboot2_Tag_EFIMemoryMap *tag
);

bool KernAux_Multiboot2_Tag_EFIBootServicesNotTerminated_is_valid(
    const struct KernAux_Multiboot2_Tag_EFIBootServicesNotTerminated *tag
);

bool KernAux_Multiboot2_Tag_EFI32bitImageHandlePtr_is_valid(
    const struct KernAux_Multiboot2_Tag_EFI32bitImageHandlePtr *tag
);

bool KernAux_Multiboot2_Tag_EFI64bitImageHandlePtr_is_valid(
    const struct KernAux_Multiboot2_Tag_EFI64bitImageHandlePtr *tag
);

bool KernAux_Multiboot2_Tag_ImageLoadBasePhysAddr_is_valid(
    const struct KernAux_Multiboot2_Tag_ImageLoadBasePhysAddr *tag
);

#ifdef __cplusplus
}
#endif

#endif
