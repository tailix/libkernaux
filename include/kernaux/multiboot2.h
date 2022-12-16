#ifndef KERNAUX_INCLUDED_MULTIBOOT2
#define KERNAUX_INCLUDED_MULTIBOOT2

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>
#include <kernaux/generic/display.h>
#include <kernaux/multiboot2/header_macro.h>

#include <stdint.h>
#include <stdbool.h>

#define KERNAUX_MULTIBOOT2_HEADER_MAGIC 0xe85250d6
#define KERNAUX_MULTIBOOT2_INFO_MAGIC   0x36d76289

// @see https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#OS-image-format
#define KERNAUX_MULTIBOOT2_HEADER_ALIGN 8
// @see https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Basic-tags-structure
#define KERNAUX_MULTIBOOT2_INFO_ALIGN   8
// @see https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Header-tags
// @see https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Basic-tags-structure
#define KERNAUX_MULTIBOOT2_TAG_ALIGN    8

#define KERNAUX_MULTIBOOT2_HEADER_CHECKSUM(arch, total_size) \
    ((uint32_t)(-(                                           \
        ((uint32_t)KERNAUX_MULTIBOOT2_HEADER_MAGIC) +        \
        ((uint32_t)(arch)) +                                 \
        ((uint32_t)(total_size))                             \
    )))

#define KERNAUX_MULTIBOOT2_DATA(ptr) (((uint8_t*)(ptr)) + sizeof(*(ptr)))

#define KERNAUX_MULTIBOOT2_HTAG_NEXT(tag_base) \
    ((struct KernAux_Multiboot2_HTagBase*)KERNAUX_MULTIBOOT2_TAG_NEXT(tag_base))
#define KERNAUX_MULTIBOOT2_ITAG_NEXT(tag_base) \
    ((struct KernAux_Multiboot2_ITagBase*)KERNAUX_MULTIBOOT2_TAG_NEXT(tag_base))
#define KERNAUX_MULTIBOOT2_TAG_NEXT(tag_base) \
    ((uint8_t*)tag_base + KERNAUX_MULTIBOOT2_TAG_SIZE_ALIGN(tag_base))
#define KERNAUX_MULTIBOOT2_TAG_SIZE_ALIGN(tag_base) \
    (((tag_base)->size + 7) & ~7)

#define KERNAUX_MULTIBOOT2_HTAG_BASE_FLAG_OPTIONAL 1

#define KERNAUX_MULTIBOOT2_HTAG_FLAGS_REQUIRE_CONSOLE KERNAUX_BITS(0)
#define KERNAUX_MULTIBOOT2_HTAG_FLAGS_EGA_SUPPORT     KERNAUX_BITS(1)

#include <kernaux/macro/packing_start.run>

/***********************
 * Header common types *
 ***********************/

enum KernAux_Multiboot2_Header_Arch {
    KERNAUX_MULTIBOOT2_HEADER_ARCH_I386   = 0,
    KERNAUX_MULTIBOOT2_HEADER_ARCH_MIPS32 = 4,
};

struct KernAux_Multiboot2_Header {
    uint32_t magic;
    enum KernAux_Multiboot2_Header_Arch arch : 32;
    uint32_t total_size;
    uint32_t checksum;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_Header, 16);

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
    uint16_t flags;
    uint32_t size;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_HTagBase, 8);

/****************************
 * Information common types *
 ****************************/

struct KernAux_Multiboot2_Info {
    uint32_t total_size;
    uint32_t reserved;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_Info, 8);

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
    uint32_t size;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_ITagBase, 8);

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
    uint64_t base_addr;
    uint64_t length;
    uint32_t type;
    uint32_t reserved;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_ITag_MemoryMap_EntryBase, 24);

/*************************
 * Header tag structures *
 *************************/

struct KernAux_Multiboot2_HTag_None {
    // type = 0
    // size = 8
    struct KernAux_Multiboot2_HTagBase base;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_HTag_None, 8);

struct KernAux_Multiboot2_HTag_InfoReq {
    // type = 1
    // size > 8
    struct KernAux_Multiboot2_HTagBase base;

    // DATA: uint32_t mbi_tag_types[]
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_HTag_InfoReq, 8);

struct KernAux_Multiboot2_HTag_Addr {
    // type = 2
    // size = 24
    struct KernAux_Multiboot2_HTagBase base;

    uint32_t header_addr;
    uint32_t load_addr;
    uint32_t load_end_addr;
    uint32_t bss_end_addr;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_HTag_Addr, 24);

struct KernAux_Multiboot2_HTag_EntryAddr {
    // type = 3
    // size = 12
    struct KernAux_Multiboot2_HTagBase base;

    uint32_t entry_addr;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_HTag_EntryAddr, 12);

struct KernAux_Multiboot2_HTag_Flags {
    // type = 4
    // size = 12
    struct KernAux_Multiboot2_HTagBase base;

    uint32_t console_flags;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_HTag_Flags, 12);

struct KernAux_Multiboot2_HTag_Framebuffer {
    // type = 5
    // size = 20
    struct KernAux_Multiboot2_HTagBase base;

    uint32_t width;
    uint32_t height;
    uint32_t depth;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_HTag_Framebuffer, 20);

struct KernAux_Multiboot2_HTag_ModuleAlign {
    // type = 6
    // size = 8
    struct KernAux_Multiboot2_HTagBase base;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_HTag_ModuleAlign, 8);

struct KernAux_Multiboot2_HTag_EFIBootServices {
    // type = 7
    // size = 8
    struct KernAux_Multiboot2_HTagBase base;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_HTag_EFIBootServices, 8);

struct KernAux_Multiboot2_HTag_EFII386EntryAddr {
    // type = 8
    // size = 12
    struct KernAux_Multiboot2_HTagBase base;

    uint32_t entry_addr;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_HTag_EFII386EntryAddr, 12);

struct KernAux_Multiboot2_HTag_EFIAmd64EntryAddr {
    // type = 9
    // size = 12
    struct KernAux_Multiboot2_HTagBase base;

    uint32_t entry_addr;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_HTag_EFIAmd64EntryAddr, 12);

struct KernAux_Multiboot2_HTag_RelocatableHeader {
    // type = 10
    // size = 24
    struct KernAux_Multiboot2_HTagBase base;

    uint32_t min_addr;
    uint32_t max_addr;
    uint32_t align;
    enum KernAux_Multiboot2_HTag_RelocatableHeader_Preference preferences : 32;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_HTag_RelocatableHeader, 24);

/******************************
 * Information tag structures *
 ******************************/

struct KernAux_Multiboot2_ITag_None {
    // type = 0
    // size = 8
    struct KernAux_Multiboot2_ITagBase base;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_ITag_None, 8);

struct KernAux_Multiboot2_ITag_BootCmdLine {
    // type = 1
    // size > 8
    struct KernAux_Multiboot2_ITagBase base;

    // DATA: char cmdline[]
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_ITag_BootCmdLine, 8);

struct KernAux_Multiboot2_ITag_BootLoaderName {
    // type = 2
    // size > 8
    struct KernAux_Multiboot2_ITagBase base;

    // DATA: char name[]
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_ITag_BootLoaderName, 8);

struct KernAux_Multiboot2_ITag_Module {
    // type = 3
    // size > 16
    struct KernAux_Multiboot2_ITagBase base;

    uint32_t mod_start;
    uint32_t mod_end;

    // DATA: char cmdline[]
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_ITag_Module, 16);

struct KernAux_Multiboot2_ITag_BasicMemoryInfo {
    // type = 4
    // size = 16
    struct KernAux_Multiboot2_ITagBase base;

    uint32_t mem_lower;
    uint32_t mem_upper;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_ITag_BasicMemoryInfo, 16);

struct KernAux_Multiboot2_ITag_BIOSBootDevice {
    // type = 5
    // size = 20
    struct KernAux_Multiboot2_ITagBase base;

    uint32_t biosdev;
    uint32_t partition;
    uint32_t sub_partition;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_ITag_BIOSBootDevice, 20);

struct KernAux_Multiboot2_ITag_MemoryMap {
    // type = 6
    // size > 16
    struct KernAux_Multiboot2_ITagBase base;

    uint32_t entry_size;
    uint32_t entry_version;

    // DATA: varies(entry_size) KernAux_Multiboot2_ITag_MemoryMap_EntryBase entries[]
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_ITag_MemoryMap, 16);

struct KernAux_Multiboot2_ITag_VBEInfo {
    // type = 7
    // size = 784
    struct KernAux_Multiboot2_ITagBase base;

    uint16_t vbe_mode;
    uint16_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;
    uint8_t vbe_control_info[512];
    uint8_t vbe_mode_info[256];
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_ITag_VBEInfo, 784);

struct KernAux_Multiboot2_ITag_FramebufferInfo {
    // type = 8
    // size > 31
    struct KernAux_Multiboot2_ITagBase base;

    uint64_t framebuffer_addr;
    uint32_t framebuffer_pitch;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint8_t framebuffer_bpp;
    uint8_t framebuffer_type;

    // FIXME: GRUB 2 and Limine don't follow the spec!
    // Multiboot 2: https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#Framebuffer-info
    // GRUB 2:      https://github.com/rhboot/grub2/blob/7259d55ffcf124e32eafb61aa381f9856e98a708/include/multiboot2.h#L288
    // Limine 4:    https://github.com/limine-bootloader/limine/blob/1aba6b3aeb72ac55b177132ca75ea8adfbcb78aa/common/protos/multiboot2.h#L292
    uint8_t reserved;

    // DATA: varies color_info[]
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_ITag_FramebufferInfo, 31);

// FIXME: GRUB 2 and Limine don't follow the spec!
// Multiboot 2: https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#ELF_002dSymbols
// GRUB 2:      https://github.com/rhboot/grub2/blob/7259d55ffcf124e32eafb61aa381f9856e98a708/include/multiboot2.h#L314-L322
// Limine 4:    https://github.com/limine-bootloader/limine/blob/1aba6b3aeb72ac55b177132ca75ea8adfbcb78aa/common/protos/multiboot2.h#L318-L326
struct KernAux_Multiboot2_ITag_ELFSymbols {
    // type = 9
    // size > 16
    struct KernAux_Multiboot2_ITagBase base;

    uint16_t num;
    uint16_t ent_size;
    uint16_t shndx;
    uint16_t reserved;

    // DATA: varies section_headers[]
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_ITag_ELFSymbols, 16);

struct KernAux_Multiboot2_ITag_APMTable {
    // type = 10
    // size = 28
    struct KernAux_Multiboot2_ITagBase base;

    uint16_t version;
    uint16_t cseg;
    uint32_t offset;
    uint16_t cseg_16;
    uint16_t dseg;
    uint16_t flags;
    uint16_t cseg_len;
    uint16_t cseg_16_len;
    uint16_t dseg_len;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_ITag_APMTable, 28);

struct KernAux_Multiboot2_ITag_EFI32bitSystemTablePtr {
    // type = 11
    // size = 12
    struct KernAux_Multiboot2_ITagBase base;

    uint32_t pointer;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_ITag_EFI32bitSystemTablePtr, 12);

struct KernAux_Multiboot2_ITag_EFI64bitSystemTablePtr {
    // type = 12
    // size = 16
    struct KernAux_Multiboot2_ITagBase base;

    uint64_t pointer;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_ITag_EFI64bitSystemTablePtr, 16);

struct KernAux_Multiboot2_ITag_SMBIOSTables {
    // type = 13
    // size > 16
    struct KernAux_Multiboot2_ITagBase base;

    uint8_t major;
    uint8_t minor;
    uint8_t reserved[6];

    // TODO: DATA?
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_ITag_SMBIOSTables, 16);

struct KernAux_Multiboot2_ITag_ACPIOldRSDP {
    // type = 14
    // size > 8
    struct KernAux_Multiboot2_ITagBase base;

    // TODO: DATA?
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_ITag_ACPIOldRSDP, 8);

struct KernAux_Multiboot2_ITag_ACPINewRSDP {
    // type = 15
    // size > 8
    struct KernAux_Multiboot2_ITagBase base;

    // TODO: DATA?
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_ITag_ACPINewRSDP, 8);

struct KernAux_Multiboot2_ITag_NetworkingInfo {
    // type = 16
    // size > 8
    struct KernAux_Multiboot2_ITagBase base;

    // TODO: DATA?
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_ITag_NetworkingInfo, 8);

struct KernAux_Multiboot2_ITag_EFIMemoryMap {
    // type = 17
    // size > 16
    struct KernAux_Multiboot2_ITagBase base;

    uint32_t descriptor_size;
    uint32_t descriptor_version;

    // TODO: DATA?
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_Multiboot2_ITag_EFIMemoryMap, 16);

struct KernAux_Multiboot2_ITag_EFIBootServicesNotTerminated {
    // type = 18
    // size = 8
    struct KernAux_Multiboot2_ITagBase base;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(
    KernAux_Multiboot2_ITag_EFIBootServicesNotTerminated,
    8
);

struct KernAux_Multiboot2_ITag_EFI32bitImageHandlePtr {
    // type = 19
    // size = 12
    struct KernAux_Multiboot2_ITagBase base;

    uint32_t pointer;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(
    KernAux_Multiboot2_ITag_EFI32bitImageHandlePtr,
    12
);

struct KernAux_Multiboot2_ITag_EFI64bitImageHandlePtr {
    // type = 20
    // size = 16
    struct KernAux_Multiboot2_ITagBase base;

    uint64_t pointer;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(
    KernAux_Multiboot2_ITag_EFI64bitImageHandlePtr,
    16
);

struct KernAux_Multiboot2_ITag_ImageLoadBasePhysAddr {
    // type = 21
    // size = 12
    struct KernAux_Multiboot2_ITagBase base;

    uint32_t load_base_addr;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(
    KernAux_Multiboot2_ITag_ImageLoadBasePhysAddr,
    12
);

#include <kernaux/macro/packing_end.run>

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

/********************
 * Helper functions *
 ********************/

#include <kernaux/multiboot2/header_helpers.h>
#include <kernaux/multiboot2/info_helpers.h>

/************************
 * Validation functions *
 ************************/

#include <kernaux/multiboot2/header_is_valid.h>
#include <kernaux/multiboot2/info_is_valid.h>

/*******************
 * Print functions *
 *******************/

#include <kernaux/multiboot2/header_print.h>
#include <kernaux/multiboot2/info_print.h>

#ifdef __cplusplus
}
#endif

#endif
