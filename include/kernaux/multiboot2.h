#ifndef KERNAUX_INCLUDED_MULTIBOOT2
#define KERNAUX_INCLUDED_MULTIBOOT2

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#define KERNAUX_MULTIBOOT2_HEADER_MAGIC 0xe85250d6
#define KERNAUX_MULTIBOOT2_INFO_MAGIC   0x36d76289

#define KERNAUX_MULTIBOOT2_HEADER_ALIGN 4

#define KERNAUX_MULTIBOOT2_HEADER_CHECKSUM(arch, total_size) \
    ((uint32_t)(-(                                           \
        ((uint32_t)KERNAUX_MULTIBOOT2_HEADER_MAGIC) +        \
        ((uint32_t)(arch)) +                                 \
        ((uint32_t)(total_size))                             \
    )))

#define KERNAUX_MULTIBOOT2_DATA(ptr) (((uint8_t*)(ptr)) + sizeof(*(ptr)))

#define KERNAUX_MULTIBOOT2_TAG_ALIGN 8

#define KERNAUX_MULTIBOOT2_HTAG_NEXT(tag_base) \
    ((struct KernAux_Multiboot2_HTagBase*)KERNAUX_MULTIBOOT2_TAG_NEXT(tag_base))
#define KERNAUX_MULTIBOOT2_ITAG_NEXT(tag_base) \
    ((struct KernAux_Multiboot2_ITagBase*)KERNAUX_MULTIBOOT2_TAG_NEXT(tag_base))
#define KERNAUX_MULTIBOOT2_TAG_NEXT(tag_base) \
    ((uint8_t*)tag_base + KERNAUX_MULTIBOOT2_TAG_SIZE_ALIGN(tag_base))
#define KERNAUX_MULTIBOOT2_TAG_SIZE_ALIGN(tag_base) \
    (((tag_base)->size + 7) & ~7)

#define KERNAUX_MULTIBOOT2_HTAG_BASE_FLAG_OPTIONAL 1

#define KERNAUX_MULTIBOOT2_HTAG_FLAGS_REQUIRE_CONSOLE (1 << 0)
#define KERNAUX_MULTIBOOT2_HTAG_FLAGS_EGA_SUPPORT     (1 << 1)

#ifdef __TINYC__
#pragma pack(push, 1)
#endif

/***********************
 * Header common types *
 ***********************/

enum KernAux_Multiboot2_Header_Arch {
    KERNAUX_MULTIBOOT2_HEADER_ARCH_I386   = 0,
    KERNAUX_MULTIBOOT2_HEADER_ARCH_MIPS32 = 4,
};

struct KernAux_Multiboot2_Header {
    unsigned magic                           : 32;
    enum KernAux_Multiboot2_Header_Arch arch : 32;
    unsigned total_size                      : 32;
    unsigned checksum                        : 32;
}
__attribute__((packed));

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

struct KernAux_Multiboot2_HTagBase {
    enum KernAux_Multiboot2_HTag type : 16;
    unsigned flags                    : 16;
    unsigned size                     : 32;
}
__attribute__((packed));

/****************************
 * Information common types *
 ****************************/

struct KernAux_Multiboot2_Info {
    unsigned total_size : 32;
    unsigned reserved1  : 32;
}
__attribute__((packed));

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

struct KernAux_Multiboot2_ITagBase {
    enum KernAux_Multiboot2_ITag type : 32;
    unsigned size                     : 32;
}
__attribute__((packed));

/***************************
 * Header additional types *
 ***************************/

enum KernAux_Multiboot2_HTag_RelocatableHeader_Preference {
    KERNAUX_MULTIBOOT2_HTAG_RELOCATABLE_HEADER_PREFERENCE_NONE    = 0,
    KERNAUX_MULTIBOOT2_HTAG_RELOCATABLE_HEADER_PREFERENCE_LOWEST  = 1,
    KERNAUX_MULTIBOOT2_HTAG_RELOCATABLE_HEADER_PREFERENCE_HIGHEST = 2,
};

/********************************
 * Information additional types *
 ********************************/

struct KernAux_Multiboot2_ITag_MemoryMap_EntryBase {
    unsigned long long base_addr : 64;
    unsigned long long length    : 64;
    unsigned type                : 32;
    unsigned reserved1           : 32;
}
__attribute__((packed));

/*************************
 * Header tag structures *
 *************************/

struct KernAux_Multiboot2_HTag_None {
    // type = 0
    // size = 8
    struct KernAux_Multiboot2_HTagBase base;
}
__attribute__((packed));

struct KernAux_Multiboot2_HTag_InfoReq {
    // type = 1
    // size > 8
    struct KernAux_Multiboot2_HTagBase base;
}
__attribute__((packed));

struct KernAux_Multiboot2_HTag_Addr {
    // type = 2
    // size = 24
    struct KernAux_Multiboot2_HTagBase base;

    unsigned header_addr   : 32;
    unsigned load_addr     : 32;
    unsigned load_end_addr : 32;
    unsigned bss_end_addr  : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_HTag_EntryAddr {
    // type = 3
    // size = 12
    struct KernAux_Multiboot2_HTagBase base;

    unsigned entry_addr : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_HTag_Flags {
    // type = 4
    // size = 12
    struct KernAux_Multiboot2_HTagBase base;

    unsigned console_flags : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_HTag_Framebuffer {
    // type = 5
    // size = 20
    struct KernAux_Multiboot2_HTagBase base;

    unsigned width  : 32;
    unsigned height : 32;
    unsigned depth  : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_HTag_ModuleAlign {
    // type = 6
    // size = 8
    struct KernAux_Multiboot2_HTagBase base;
}
__attribute__((packed));

struct KernAux_Multiboot2_HTag_EFIBootServices {
    // type = 7
    // size = 8
    struct KernAux_Multiboot2_HTagBase base;
}
__attribute__((packed));

struct KernAux_Multiboot2_HTag_EFII386EntryAddr {
    // type = 8
    // size = 12
    struct KernAux_Multiboot2_HTagBase base;

    unsigned entry_addr : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_HTag_EFIAmd64EntryAddr {
    // type = 9
    // size = 12
    struct KernAux_Multiboot2_HTagBase base;

    unsigned entry_addr : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_HTag_RelocatableHeader {
    // type = 10
    // size = 24
    struct KernAux_Multiboot2_HTagBase base;

    unsigned min_addr                                                     : 32;
    unsigned max_addr                                                     : 32;
    unsigned align                                                        : 32;
    enum KernAux_Multiboot2_HTag_RelocatableHeader_Preference preferences : 32;
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
    // size > 8
    struct KernAux_Multiboot2_ITagBase base;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_BootLoaderName {
    // type = 2
    // size > 8
    struct KernAux_Multiboot2_ITagBase base;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_Module {
    // type = 3
    // size > 16
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
    // size > 16
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
    // size > 31
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
    // size > 16
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
    // size > 16
    struct KernAux_Multiboot2_ITagBase base;

    unsigned major : 8;
    unsigned minor : 8;
    unsigned char reserved1[6];
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_ACPIOldRSDP {
    // type = 14
    // size > 8
    struct KernAux_Multiboot2_ITagBase base;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_ACPINewRSDP {
    // type = 15
    // size > 8
    struct KernAux_Multiboot2_ITagBase base;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_NetworkingInfo {
    // type = 16
    // size > 8
    struct KernAux_Multiboot2_ITagBase base;
}
__attribute__((packed));

struct KernAux_Multiboot2_ITag_EFIMemoryMap {
    // type = 17
    // size > 16
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

#ifdef __TINYC__
#pragma pack(pop)
#endif

/********************
 * String functions *
 ********************/

const char *KernAux_Multiboot2_Header_Arch_to_str(
    enum KernAux_Multiboot2_Header_Arch arch
);

const char *KernAux_Multiboot2_HTag_to_str(
    enum KernAux_Multiboot2_HTag tag_type
);

const char *KernAux_Multiboot2_ITag_to_str(
    enum KernAux_Multiboot2_ITag tag_type
);

const char *KernAux_Multiboot2_HTag_RelocatableHeader_Preference_to_str(
    enum KernAux_Multiboot2_HTag_RelocatableHeader_Preference pref
);

/***************************
 * Header helper functions *
 ***************************/

const struct KernAux_Multiboot2_HTagBase
*KernAux_Multiboot2_Header_first_tag_with_type(
    const struct KernAux_Multiboot2_Header *multiboot2_header,
    enum KernAux_Multiboot2_HTag tag_type
);

const struct KernAux_Multiboot2_HTagBase
*KernAux_Multiboot2_Header_tag_with_type_after(
    const struct KernAux_Multiboot2_Header *multiboot2_header,
    enum KernAux_Multiboot2_HTag tag_type,
    const struct KernAux_Multiboot2_HTagBase *after_tag
);

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
 * Header validation functions *
 *******************************/

bool KernAux_Multiboot2_Header_is_valid(
    const struct KernAux_Multiboot2_Header *multiboot2_header
);

bool KernAux_Multiboot2_HTagBase_is_valid(
    const struct KernAux_Multiboot2_HTagBase *tag_base
);

bool KernAux_Multiboot2_HTag_None_is_valid(
    const struct KernAux_Multiboot2_HTag_None *tag
);

bool KernAux_Multiboot2_HTag_InfoReq_is_valid(
    const struct KernAux_Multiboot2_HTag_InfoReq *tag
);

bool KernAux_Multiboot2_HTag_Addr_is_valid(
    const struct KernAux_Multiboot2_HTag_Addr *tag
);

bool KernAux_Multiboot2_HTag_EntryAddr_is_valid(
    const struct KernAux_Multiboot2_HTag_EntryAddr *tag
);

bool KernAux_Multiboot2_HTag_Flags_is_valid(
    const struct KernAux_Multiboot2_HTag_Flags *tag
);

bool KernAux_Multiboot2_HTag_Framebuffer_is_valid(
    const struct KernAux_Multiboot2_HTag_Framebuffer *tag
);

bool KernAux_Multiboot2_HTag_ModuleAlign_is_valid(
    const struct KernAux_Multiboot2_HTag_ModuleAlign *tag
);

bool KernAux_Multiboot2_HTag_EFIBootServices_is_valid(
    const struct KernAux_Multiboot2_HTag_EFIBootServices *tag
);

bool KernAux_Multiboot2_HTag_EFII386EntryAddr_is_valid(
    const struct KernAux_Multiboot2_HTag_EFII386EntryAddr *tag
);

bool KernAux_Multiboot2_HTag_EFIAmd64EntryAddr_is_valid(
    const struct KernAux_Multiboot2_HTag_EFIAmd64EntryAddr *tag
);

bool KernAux_Multiboot2_HTag_RelocatableHeader_is_valid(
    const struct KernAux_Multiboot2_HTag_RelocatableHeader *tag
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

/**************************
 * Header print functions *
 **************************/

void KernAux_Multiboot2_Header_print(
    const struct KernAux_Multiboot2_Header *multiboot2_header,
    void (*printf)(const char *format, ...)
    __attribute__((format(printf, 1, 2)))
);

void KernAux_Multiboot2_HTagBase_print(
    const struct KernAux_Multiboot2_HTagBase *tag_base,
    void (*printf)(const char *format, ...)
    __attribute__((format(printf, 1, 2)))
);

/*******************************
 * Information print functions *
 *******************************/

void KernAux_Multiboot2_Info_print(
    const struct KernAux_Multiboot2_Info *multiboot2_info,
    void (*printf)(const char *format, ...)
    __attribute__((format(printf, 1, 2)))
);

void KernAux_Multiboot2_ITagBase_print(
    const struct KernAux_Multiboot2_ITagBase *tag_base,
    void (*printf)(const char *format, ...)
    __attribute__((format(printf, 1, 2)))
);

void KernAux_Multiboot2_ITag_BootCmdLine_print(
    const struct KernAux_Multiboot2_ITag_BootCmdLine *tag,
    void (*printf)(const char *format, ...)
    __attribute__((format(printf, 1, 2)))
);

void KernAux_Multiboot2_ITag_BootLoaderName_print(
    const struct KernAux_Multiboot2_ITag_BootLoaderName *tag,
    void (*printf)(const char *format, ...)
    __attribute__((format(printf, 1, 2)))
);

void KernAux_Multiboot2_ITag_MemoryMap_print(
    const struct KernAux_Multiboot2_ITag_MemoryMap *tag,
    void (*printf)(const char *format, ...)
    __attribute__((format(printf, 1, 2)))
);

void KernAux_Multiboot2_ITag_ELFSymbols_print(
    const struct KernAux_Multiboot2_ITag_ELFSymbols *tag,
    void (*printf)(const char *format, ...)
    __attribute__((format(printf, 1, 2)))
);

#ifdef __cplusplus
}
#endif

#endif
