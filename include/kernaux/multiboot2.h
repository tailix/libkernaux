#ifndef KERNAUX_INCLUDED_MULTIBOOT2
#define KERNAUX_INCLUDED_MULTIBOOT2 1

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 * Common structures *
 *********************/

struct KernAux_Multiboot2 {
    unsigned int total_size : 32;
    unsigned int reserved1  : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_TagBase {
    unsigned int type : 32;
    unsigned int size : 32;
}
__attribute__((packed));

/******************
 * Tag structures *
 ******************/

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

struct KernAux_Multiboot2_Tag_EFI32bitSystemTablePointer {
    // type = 11
    // size = 12
    struct KernAux_Multiboot2_TagBase base;

    unsigned int pointer : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_EFI64bitSystemTablePointer {
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

struct KernAux_Multiboot2_Tag_EFI32bitImageHandlePointer {
    // type = 19
    // size = 12
    struct KernAux_Multiboot2_TagBase base;

    unsigned int pointer : 32;
}
__attribute__((packed));

struct KernAux_Multiboot2_Tag_EFI64bitImageHandlePointer {
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

#ifdef __cplusplus
}
#endif

#endif
