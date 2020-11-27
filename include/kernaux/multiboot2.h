#ifndef KERNAUX_INCLUDED_MULTIBOOT2
#define KERNAUX_INCLUDED_MULTIBOOT2 1

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 * Common structures *
 *********************/

struct KernAux_Multiboot2 {
    unsigned int total_size;
    unsigned int reserved1;
};

struct KernAux_Multiboot2_TagBase {
    unsigned int type;
    unsigned int size;
};

/******************
 * Tag structures *
 ******************/

struct KernAux_Multiboot2_Tag_BootCmdLine {
    // type = 1
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    char cmdline[];
};

struct KernAux_Multiboot2_Tag_BootLoaderName {
    // type = 2
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    char name[];
};

struct KernAux_Multiboot2_Tag_Module {
    // type = 3
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    unsigned int mod_start;
    unsigned int mod_end;

    char cmdline[];
};

struct KernAux_Multiboot2_Tag_BasicMemoryInfo {
    // type = 4
    // size = 16
    struct KernAux_Multiboot2_TagBase base;

    unsigned int mem_lower;
    unsigned int mem_upper;
};

struct KernAux_Multiboot2_Tag_BIOSBootDevice {
    // type = 5
    // size = 20
    struct KernAux_Multiboot2_TagBase base;

    unsigned int bios_dev;
    unsigned int partition;
    unsigned int sub_partition;
};

struct KernAux_Multiboot2_Tag_MemoryMap {
    // type = 5
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    unsigned int size;
    unsigned int entry_size;
    unsigned int entry_version;

    unsigned char data[];
};

struct KernAux_Multiboot2_Tag_VBEInfo {
    // type = 7
    // size = 784
    struct KernAux_Multiboot2_TagBase base;

    unsigned short vbe_mode;
    unsigned short vbe_interface_seg;
    unsigned short vbe_interface_off;
    unsigned short vbe_interface_len;
    unsigned char vbe_control_info[512];
    unsigned char vbe_mode_info[256];
};

struct KernAux_Multiboot2_Tag_FramebufferInfo {
    // type = 8
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    unsigned long long framebuffer_addr;
    unsigned int framebuffer_pitch;
    unsigned int framebuffer_width;
    unsigned int framebuffer_height;
    unsigned char framebuffer_bpp;
    unsigned char framebuffer_type;
    unsigned char reserved1;

    unsigned char data[];
};

struct KernAux_Multiboot2_Tag_ELFSymbols {
    // type = 9
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    unsigned short num;
    unsigned short ent_size;
    unsigned short shndx;
    unsigned short reserved1;

    unsigned char section_headers[];
};

struct KernAux_Multiboot2_Tag_APMTable {
    // type = 10
    // size = 20
    struct KernAux_Multiboot2_TagBase base;

    unsigned short version;
    unsigned short cseg;
    unsigned int offset;
    unsigned short cseg_16;
    unsigned short dseg;
    unsigned short flags;
    unsigned short cseg_len;
    unsigned short cseg_16_len;
    unsigned short dseg_len;
};

struct KernAux_Multiboot2_Tag_EFI32bitSystemTablePointer {
    // type = 11
    // size = 12
    struct KernAux_Multiboot2_TagBase base;

    unsigned int pointer;
};

struct KernAux_Multiboot2_Tag_EFI64bitSystemTablePointer {
    // type = 12
    // size = 16
    struct KernAux_Multiboot2_TagBase base;

    unsigned long long pointer;
};

struct KernAux_Multiboot2_Tag_SMBIOSTables {
    // type = 13
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    unsigned char major;
    unsigned char minor;
    unsigned char reserved1[6];

    unsigned char data[];
};

struct KernAux_Multiboot2_Tag_ACPIOldRSDP {
    // type = 14
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    unsigned char data[];
};

struct KernAux_Multiboot2_Tag_ACPINewRSDP {
    // type = 15
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    unsigned char data[];
};

struct KernAux_Multiboot2_Tag_NetworkingInfo {
    // type = 16
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    unsigned char data[];
};

struct KernAux_Multiboot2_Tag_EFIMemoryMap {
    // type = 17
    // size = ?
    struct KernAux_Multiboot2_TagBase base;

    unsigned int descriptor_size;
    unsigned int descriptor_version;

    unsigned char data[];
};

struct KernAux_Multiboot2_Tag_EFIBootServicesNotTerminated {
    // type = 18
    // size = 8
    struct KernAux_Multiboot2_TagBase base;
};

struct KernAux_Multiboot2_Tag_EFI32bitImageHandlePointer {
    // type = 19
    // size = 12
    struct KernAux_Multiboot2_TagBase base;

    unsigned int pointer;
};

struct KernAux_Multiboot2_Tag_EFI64bitImageHandlePointer {
    // type = 20
    // size = 16
    struct KernAux_Multiboot2_TagBase base;

    unsigned long long pointer;
};

struct KernAux_Multiboot2_Tag_ImageLoadBasePhysAddr {
    // type = 21
    // size = 12
    struct KernAux_Multiboot2_TagBase base;

    unsigned int load_base_addr;
};

/*************************
 * Additional structures *
 *************************/

struct KernAux_Multiboot2_Tag_MemoryMap_EntryBase {
    unsigned long long base_addr;
    unsigned long long length;
    unsigned int type;
    unsigned int reserved1;
};

#ifdef __cplusplus
}
#endif

#endif
