#ifndef KERNAUX_INCLUDED_MULTIBOOT2
#define KERNAUX_INCLUDED_MULTIBOOT2 1

#include <kernaux/stdlib.h>

#define KERNAUX_MULTIBOOT2_MAGIC 0x36d76289

#ifdef __cplusplus
extern "C" {
#endif

/****************
 * Common types *
 ****************/

enum KernAux_Multiboot2_TagType {
    KERNAUX_MULTIBOOT2_TAGTYPE_NONE = 0,
    KERNAUX_MULTIBOOT2_TAGTYPE_BOOT_CMD_LINE = 1,
    KERNAUX_MULTIBOOT2_TAGTYPE_BOOT_LOADER_NAME = 2,
    KERNAUX_MULTIBOOT2_TAGTYPE_MODULE = 3,
    KERNAUX_MULTIBOOT2_TAGTYPE_BASIC_MEMORY_INFO = 4,
    KERNAUX_MULTIBOOT2_TAGTYPE_BIOS_BOOT_DEVICE = 5,
    KERNAUX_MULTIBOOT2_TAGTYPE_MEMORY_MAP = 6,
    KERNAUX_MULTIBOOT2_TAGTYPE_VBE_INFO = 7,
    KERNAUX_MULTIBOOT2_TAGTYPE_FRAMEBUFFER_INFO = 8,
    KERNAUX_MULTIBOOT2_TAGTYPE_ELF_SYMBOLS = 9,
    KERNAUX_MULTIBOOT2_TAGTYPE_APM_TABLE = 10,
    KERNAUX_MULTIBOOT2_TAGTYPE_EFI_32BIT_SYSTEM_TABLE_PTR = 11,
    KERNAUX_MULTIBOOT2_TAGTYPE_EFI_64BIT_SYSTEM_TABLE_PTR = 12,
    KERNAUX_MULTIBOOT2_TAGTYPE_SMBIOS_TABLES = 13,
    KERNAUX_MULTIBOOT2_TAGTYPE_ACPI_OLD_RSDP = 14,
    KERNAUX_MULTIBOOT2_TAGTYPE_ACPI_NEW_RSDP = 15,
    KERNAUX_MULTIBOOT2_TAGTYPE_NETWORKING_INFO = 16,
    KERNAUX_MULTIBOOT2_TAGTYPE_EFI_MEMORY_MAP = 17,
    KERNAUX_MULTIBOOT2_TAGTYPE_EFI_BOOT_SERVICES_NOT_TERMINATED = 18,
    KERNAUX_MULTIBOOT2_TAGTYPE_EFI_32BIT_IMAGE_HANDLE_PTR = 19,
    KERNAUX_MULTIBOOT2_TAGTYPE_EFI_64BIT_IMAGE_HANDLE_PTR = 20,
    KERNAUX_MULTIBOOT2_TAGTYPE_IMAGE_LOAD_BASE_PHYS_ADDR = 21,
};

struct KernAux_Multiboot2 {
    unsigned int total_size : 32;
    unsigned int reserved1  : 32;

    unsigned char data[];
}
__attribute__((packed));

struct KernAux_Multiboot2_TagBase {
    enum KernAux_Multiboot2_TagType type : 32;
    unsigned int size                    : 32;

    unsigned char data[];
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

    char cmdline[];
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_BootLoaderName {
    // type = 2
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    char name[];
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_Module {
    // type = 3
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    unsigned int mod_start : 32;
    unsigned int mod_end   : 32;

    char cmdline[];
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_BasicMemoryInfo {
    // type = 4
    // size = 16
    struct KernAux_Multiboot2_TagBase base;

    unsigned int mem_lower : 32;
    unsigned int mem_upper : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_BIOSBootDevice {
    // type = 5
    // size = 20
    struct KernAux_Multiboot2_TagBase base;

    unsigned int bios_dev      : 32;
    unsigned int partition     : 32;
    unsigned int sub_partition : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_MemoryMap {
    // type = 6
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    unsigned int entry_size    : 32;
    unsigned int entry_version : 32;

    unsigned char data[];
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_VBEInfo {
    // type = 7
    // size = 784
    struct KernAux_Multiboot2_TagBase base;

    unsigned short vbe_mode          : 16;
    unsigned short vbe_interface_seg : 16;
    unsigned short vbe_interface_off : 16;
    unsigned short vbe_interface_len : 16;
    unsigned char vbe_control_info[512];
    unsigned char vbe_mode_info[256];
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_FramebufferInfo {
    // type = 8
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    unsigned long long framebuffer_addr : 64;
    unsigned int framebuffer_pitch      : 32;
    unsigned int framebuffer_width      : 32;
    unsigned int framebuffer_height     : 32;
    unsigned char framebuffer_bpp       : 8;
    unsigned char framebuffer_type      : 8;
    unsigned char reserved1             : 8;

    unsigned char data[];
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_ELFSymbols {
    // type = 9
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    unsigned short num       : 16;
    unsigned short ent_size  : 16;
    unsigned short shndx     : 16;
    unsigned short reserved1 : 16;

    unsigned char section_headers[];
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_APMTable {
    // type = 10
    // size = 28
    struct KernAux_Multiboot2_TagBase base;

    unsigned short version     : 16;
    unsigned short cseg        : 16;
    unsigned int offset        : 32;
    unsigned short cseg_16     : 16;
    unsigned short dseg        : 16;
    unsigned short flags       : 16;
    unsigned short cseg_len    : 16;
    unsigned short cseg_16_len : 16;
    unsigned short dseg_len    : 16;
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_EFI32bitSystemTablePtr {
    // type = 11
    // size = 12
    struct KernAux_Multiboot2_TagBase base;

    unsigned int pointer : 32;
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

    unsigned char major : 8;
    unsigned char minor : 8;
    unsigned char reserved1[6];

    unsigned char data[];
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_ACPIOldRSDP {
    // type = 14
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    unsigned char data[];
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_ACPINewRSDP {
    // type = 15
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    unsigned char data[];
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_NetworkingInfo {
    // type = 16
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    unsigned char data[];
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_EFIMemoryMap {
    // type = 17
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    unsigned int descriptor_size    : 32;
    unsigned int descriptor_version : 32;

    unsigned char data[];
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

    unsigned int pointer : 32;
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

    unsigned int load_base_addr : 32;
}
__attribute__((packed));

/*************************
 * Additional structures *
 *************************/

struct KernAux_Multiboot2_Tag_MemoryMap_EntryBase {
    unsigned long long base_addr : 64;
    unsigned long long length    : 64;
    unsigned int type            : 32;
    unsigned int reserved1       : 32;
}
__attribute__((packed));

/********************
 * Helper functions *
 ********************/

const struct KernAux_Multiboot2_TagBase *KernAux_Multiboot2_first_tag_with_type(
    const struct KernAux_Multiboot2 *multiboot2,
    enum KernAux_Multiboot2_TagType tag_type
)
__attribute__((nonnull));

const struct KernAux_Multiboot2_TagBase *KernAux_Multiboot2_tag_with_type_after(
    const struct KernAux_Multiboot2 *multiboot2,
    enum KernAux_Multiboot2_TagType tag_type,
    const struct KernAux_Multiboot2_TagBase *after_tag
)
__attribute__((nonnull));

const char *KernAux_Multiboot2_boot_cmd_line(
    const struct KernAux_Multiboot2 *multiboot2
)
__attribute__((nonnull));

/*******************
 * Print functions *
 *******************/

void KernAux_Multiboot2_print(
    const struct KernAux_Multiboot2 *multiboot2,
    void (*print)(const char *format, ...)
)
__attribute__((nonnull));

void KernAux_Multiboot2_TagBase_print(
    const struct KernAux_Multiboot2_TagBase *tag_base,
    void (*print)(const char *format, ...)
)
__attribute__((nonnull));

/************************
 * Validation functions *
 ************************/

kernaux_bool KernAux_Multiboot2_is_valid(
    const struct KernAux_Multiboot2 *multiboot2
)
__attribute__((nonnull));

kernaux_bool KernAux_Multiboot2_TagBase_is_valid(
    const struct KernAux_Multiboot2_TagBase *tag_base
)
__attribute__((nonnull));

kernaux_bool KernAux_Multiboot2_Tag_None_is_valid(
    const struct KernAux_Multiboot2_Tag_None *tag
)
__attribute__((nonnull));

kernaux_bool KernAux_Multiboot2_Tag_BootCmdLine_is_valid(
    const struct KernAux_Multiboot2_Tag_BootCmdLine *tag
)
__attribute__((nonnull));

kernaux_bool KernAux_Multiboot2_Tag_BootLoaderName_is_valid(
    const struct KernAux_Multiboot2_Tag_BootLoaderName *tag
)
__attribute__((nonnull));

kernaux_bool KernAux_Multiboot2_Tag_Module_is_valid(
    const struct KernAux_Multiboot2_Tag_Module *tag
)
__attribute__((nonnull));

kernaux_bool KernAux_Multiboot2_Tag_BasicMemoryInfo_is_valid(
    const struct KernAux_Multiboot2_Tag_BasicMemoryInfo *tag
)
__attribute__((nonnull));

kernaux_bool KernAux_Multiboot2_Tag_BIOSBootDevice_is_valid(
    const struct KernAux_Multiboot2_Tag_BIOSBootDevice *tag
)
__attribute__((nonnull));

kernaux_bool KernAux_Multiboot2_Tag_MemoryMap_is_valid(
    const struct KernAux_Multiboot2_Tag_MemoryMap *tag
)
__attribute__((nonnull));

kernaux_bool KernAux_Multiboot2_Tag_VBEInfo_is_valid(
    const struct KernAux_Multiboot2_Tag_VBEInfo *tag
)
__attribute__((nonnull));

kernaux_bool KernAux_Multiboot2_Tag_FramebufferInfo_is_valid(
    const struct KernAux_Multiboot2_Tag_FramebufferInfo *tag
)
__attribute__((nonnull));

kernaux_bool KernAux_Multiboot2_Tag_ELFSymbols_is_valid(
    const struct KernAux_Multiboot2_Tag_ELFSymbols *tag
)
__attribute__((nonnull));

kernaux_bool KernAux_Multiboot2_Tag_APMTable_is_valid(
    const struct KernAux_Multiboot2_Tag_APMTable *tag
)
__attribute__((nonnull));

kernaux_bool KernAux_Multiboot2_Tag_EFI32bitSystemTablePtr_is_valid(
    const struct KernAux_Multiboot2_Tag_EFI32bitSystemTablePtr *tag
)
__attribute__((nonnull));

kernaux_bool KernAux_Multiboot2_Tag_EFI64bitSystemTablePtr_is_valid(
    const struct KernAux_Multiboot2_Tag_EFI64bitSystemTablePtr *tag
)
__attribute__((nonnull));

kernaux_bool KernAux_Multiboot2_Tag_SMBIOSTables_is_valid(
    const struct KernAux_Multiboot2_Tag_SMBIOSTables *tag
)
__attribute__((nonnull));

kernaux_bool KernAux_Multiboot2_Tag_ACPIOldRSDP_is_valid(
    const struct KernAux_Multiboot2_Tag_ACPIOldRSDP *tag
)
__attribute__((nonnull));

kernaux_bool KernAux_Multiboot2_Tag_ACPINewRSDP_is_valid(
    const struct KernAux_Multiboot2_Tag_ACPINewRSDP *tag
)
__attribute__((nonnull));

kernaux_bool KernAux_Multiboot2_Tag_NetworkingInfo_is_valid(
    const struct KernAux_Multiboot2_Tag_NetworkingInfo *tag
)
__attribute__((nonnull));

kernaux_bool KernAux_Multiboot2_Tag_EFIMemoryMap_is_valid(
    const struct KernAux_Multiboot2_Tag_EFIMemoryMap *tag
)
__attribute__((nonnull));

kernaux_bool KernAux_Multiboot2_Tag_EFIBootServicesNotTerminated_is_valid(
    const struct KernAux_Multiboot2_Tag_EFIBootServicesNotTerminated *tag
)
__attribute__((nonnull));

kernaux_bool KernAux_Multiboot2_Tag_EFI32bitImageHandlePtr_is_valid(
    const struct KernAux_Multiboot2_Tag_EFI32bitImageHandlePtr *tag
)
__attribute__((nonnull));

kernaux_bool KernAux_Multiboot2_Tag_EFI64bitImageHandlePtr_is_valid(
    const struct KernAux_Multiboot2_Tag_EFI64bitImageHandlePtr *tag
)
__attribute__((nonnull));

kernaux_bool KernAux_Multiboot2_Tag_ImageLoadBasePhysAddr_is_valid(
    const struct KernAux_Multiboot2_Tag_ImageLoadBasePhysAddr *tag
)
__attribute__((nonnull));

#ifdef __cplusplus
}
#endif

#endif
