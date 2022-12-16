#include <kernaux/macro.h>
#include <kernaux/multiboot2.h>

#include <kernaux/macro/packing_start.run>

KERNAUX_ALIGNED(KERNAUX_MULTIBOOT2_INFO_ALIGN)
static const struct {
    struct KernAux_Multiboot2_Info multiboot2_info;

    struct {
        struct KernAux_Multiboot2_ITag_BootCmdLine tag;
        char cmdline[15];
    } tag_boot_cmd_line;
    uint8_t _align1[1];

    struct {
        struct KernAux_Multiboot2_ITag_BootLoaderName tag;
        char name[22];
    } tag_boot_loader_name;
    uint8_t _align2[2];

    struct {
        struct KernAux_Multiboot2_ITag_Module tag;
        char cmdline[17];
    } tag_module1;
    uint8_t _align3[7];

    struct {
        struct KernAux_Multiboot2_ITag_Module tag;
        char cmdline[17];
    } tag_module2;
    uint8_t _align4[7];

    struct KernAux_Multiboot2_ITag_BasicMemoryInfo tag_basic_memory_info;

    struct KernAux_Multiboot2_ITag_BIOSBootDevice tag_bios_boot_device;
    uint8_t _align5[4];

    struct {
        struct KernAux_Multiboot2_ITag_MemoryMap tag;

        uint8_t data[160 - sizeof(struct KernAux_Multiboot2_ITag_MemoryMap)];
    } tag_memory_map;

    struct KernAux_Multiboot2_ITag_VBEInfo tag_vbe_info;

    struct {
        struct KernAux_Multiboot2_ITag_FramebufferInfo tag;
        uint8_t data[8];
    } tag_framebuffer_info;

    struct {
        struct KernAux_Multiboot2_ITag_ELFSymbols tag;

        uint8_t data[420 - sizeof(struct KernAux_Multiboot2_ITag_ELFSymbols)];
    } tag_elf_symbols;
    uint8_t _align7[4];

    struct KernAux_Multiboot2_ITag_APMTable tag_apm_table;
    uint8_t _align8[4];

    struct KernAux_Multiboot2_ITag_EFI32bitSystemTablePtr
        tag_efi_32bit_system_table_ptr;
    uint8_t _align9[4];

    struct KernAux_Multiboot2_ITag_EFI64bitSystemTablePtr
        tag_efi_64bit_system_table_ptr;

    struct {
        struct KernAux_Multiboot2_ITag_SMBIOSTables tag;
        uint8_t data[8];
    } tag_smbios_tables;

    struct {
        struct KernAux_Multiboot2_ITag_ACPIOldRSDP tag;
        uint8_t data[8];
    } tag_acpi_old_rsdp;

    struct {
        struct KernAux_Multiboot2_ITag_ACPINewRSDP tag;
        uint8_t data[8];
    } tag_acpi_new_rsdp;

    struct {
        struct KernAux_Multiboot2_ITag_NetworkingInfo tag;
        uint8_t data[8];
    } tag_networking_info;

    struct {
        struct KernAux_Multiboot2_ITag_EFIMemoryMap tag;
        uint8_t data[8];
    } tag_efi_memory_map;

    struct KernAux_Multiboot2_ITag_EFIBootServicesNotTerminated
        tag_efi_boot_services_not_terminated;

    struct KernAux_Multiboot2_ITag_EFI32bitImageHandlePtr
        tag_efi_32bit_image_handle_ptr;
    uint8_t _align10[4];

    struct KernAux_Multiboot2_ITag_EFI64bitImageHandlePtr
        tag_efi_64bit_image_handle_ptr;

    struct KernAux_Multiboot2_ITag_ImageLoadBasePhysAddr
        tag_image_load_base_phys_addr;
    uint8_t _align11[4];

    struct KernAux_Multiboot2_ITag_None tag_none;
}
KERNAUX_PACKED
multiboot2_info_example2 = {
    .multiboot2_info = {
        .total_size = sizeof(multiboot2_info_example2),
        .reserved = 0,
    },
    .tag_boot_cmd_line = {
        .tag = {
            .base = {
                .type = KERNAUX_MULTIBOOT2_ITAG_BOOT_CMD_LINE,
                .size = sizeof(multiboot2_info_example2.tag_boot_cmd_line),
            },
        },
        .cmdline = "Hello, Kernel!\0",
    },
    .tag_boot_loader_name = {
        .tag = {
            .base = {
                .type = KERNAUX_MULTIBOOT2_ITAG_BOOT_LOADER_NAME,
                .size = sizeof(multiboot2_info_example2.tag_boot_loader_name),
            },
        },
        .name = "GRUB 2.02-2ubuntu8.20\0",
    },
    .tag_module1 = {
        .tag = {
            .base = {
                .type = KERNAUX_MULTIBOOT2_ITAG_MODULE,
                .size = sizeof(multiboot2_info_example2.tag_module1),
            },
            .mod_start = 123,
            .mod_end = 456,
        },
        .cmdline = "Hello, Module 1!\0",
    },
    .tag_module2 = {
        .tag = {
            .base = {
                .type = KERNAUX_MULTIBOOT2_ITAG_MODULE,
                .size = sizeof(multiboot2_info_example2.tag_module2),
            },
            .mod_start = 123,
            .mod_end = 456,
        },
        .cmdline = "Hello, Module 2!\0",
    },
    .tag_basic_memory_info = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_BASIC_MEMORY_INFO,
            .size = sizeof(multiboot2_info_example2.tag_basic_memory_info),
        },
        .mem_lower = 123,
        .mem_upper = 456,
    },
    .tag_bios_boot_device = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_BIOS_BOOT_DEVICE,
            .size = sizeof(multiboot2_info_example2.tag_bios_boot_device),
        },
        .biosdev = 0,
        .partition = 1,
        .sub_partition = 2,
    },
    .tag_memory_map = {
        .tag = {
            .base = {
                .type = KERNAUX_MULTIBOOT2_ITAG_MEMORY_MAP,
                .size = sizeof(multiboot2_info_example2.tag_memory_map),
            },
            .entry_size = 24,
            .entry_version = 0,
        },
        .data = {
            0, 0,    0,   0,   0, 0, 0, 0,
            0,  252, 9,   0,   0, 0, 0, 0, 1, 0, 0,   0, 0, 0, 0, 0,
            0,  252, 9,   0,   0, 0, 0, 0, 0, 4, 0,   0, 0, 0, 0, 0,
            2,  0,   0,   0,   0, 0, 0, 0, 0, 0, 15,  0, 0, 0, 0, 0,
            0,  0,   1,   0,   0, 0, 0, 0, 2, 0, 0,   0, 0, 0, 0, 0,
            0,  0,   16,  0,   0, 0, 0, 0, 0, 0, 238, 7, 0, 0, 0, 0,
            1,  0,   0,   0,   0, 0, 0, 0, 0, 0, 254, 7, 0, 0, 0, 0,
            0,  0,   2,   0,   0, 0, 0, 0, 2, 0, 0,   0, 0, 0, 0, 0,
            0,  0,   252, 255, 0, 0, 0, 0, 0, 0, 4,   0, 0, 0, 0, 0,
            2,  0,   0,   0,   0, 0, 0, 0,
        },
    },
    .tag_vbe_info = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_VBE_INFO,
            .size = sizeof(multiboot2_info_example2.tag_vbe_info),
        },
        .vbe_mode = 0,
        .vbe_interface_seg = 123,
        .vbe_interface_off = 456,
        .vbe_interface_len = 789,
        .vbe_control_info = {
            [0]   = 0,
            [16]  = 1,
            [32]  = 12,
            [48]  = 123,
            [79]  = 1,
            [95]  = 12,
            [111] = 123,
        },
        .vbe_mode_info = {
            [0]   = 0,
            [16]  = 3,
            [32]  = 32,
            [48]  = 255,
            [79]  = 3,
            [95]  = 32,
            [111] = 255,
        },
    },
    .tag_framebuffer_info = {
        .tag = {
            .base = {
                .type = KERNAUX_MULTIBOOT2_ITAG_FRAMEBUFFER_INFO,
                .size = sizeof(multiboot2_info_example2.tag_framebuffer_info),
            },
            .framebuffer_addr = 123,
            .framebuffer_pitch = 456,
            .framebuffer_width = 123,
            .framebuffer_height = 456,
            .framebuffer_bpp = 8,
            .framebuffer_type = 1,
        },
        .data = {0, 1, 2, 3, 4, 5, 6, 7},
    },
    .tag_elf_symbols = {
        .tag = {
            .base = {
                .type = KERNAUX_MULTIBOOT2_ITAG_ELF_SYMBOLS,
                .size = sizeof(multiboot2_info_example2.tag_elf_symbols),
            },
            .num = 10,
            .entsize = 40,
            .shndx = 9,
        },
        .data = {
            0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 27, 0, 0, 0, 1, 0, 0, 0, 6, 0, 0, 0,
            0, 0, 64, 0, 0, 16, 0, 0, 150, 53, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 33, 0, 0, 0,
            1, 0, 0, 0, 2, 0, 0, 0, 0, 64, 64, 0, 0, 80, 0, 0,
            8, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0,
            0, 0, 0, 0, 41, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0,
            8, 75, 64, 0, 8, 91, 0, 0, 132, 10, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 51, 0, 0, 0,
            1, 0, 0, 0, 3, 0, 0, 0, 0, 96, 64, 0, 0, 112, 0, 0,
            1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0,
            0, 0, 0, 0, 57, 0, 0, 0, 8, 0, 0, 0, 3, 0, 0, 0,
            0, 112, 64, 0, 1, 112, 0, 0, 64, 169, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 16, 0, 0, 0, 0, 0, 0, 62, 0, 0, 0,
            1, 0, 0, 0, 48, 0, 0, 0, 0, 0, 16, 0, 1, 112, 0, 0,
            17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
            1, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
            20, 0, 16, 0, 20, 112, 0, 0, 176, 12, 0, 0, 8, 0, 0, 0,
            72, 0, 0, 0, 4, 0, 0, 0, 16, 0, 0, 0, 9, 0, 0, 0,
            3, 0, 0, 0, 0, 0, 0, 0, 196, 12, 16, 0, 196, 124, 0, 0,
            208, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
            0, 0, 0, 0, 17, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0,
            148, 26, 16, 0, 148, 138, 0, 0, 71, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
        },
    },
    .tag_apm_table = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_APM_TABLE,
            .size = sizeof(multiboot2_info_example2.tag_apm_table),
        },
        .version = 0,
        .cseg = 123,
        .offset = 456,
        .cseg_16 = 789,
        .dseg = 123,
        .flags = 1,
        .cseg_len = 456,
        .cseg_16_len = 789,
        .dseg_len = 123,
    },
    .tag_efi_32bit_system_table_ptr = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_EFI_32BIT_SYSTEM_TABLE_PTR,
            .size = sizeof(multiboot2_info_example2.tag_efi_32bit_system_table_ptr),
        },
        .pointer = 0,
    },
    .tag_efi_64bit_system_table_ptr = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_EFI_64BIT_SYSTEM_TABLE_PTR,
            .size = sizeof(multiboot2_info_example2.tag_efi_64bit_system_table_ptr),
        },
        .pointer = 0,
    },
    .tag_smbios_tables = {
        .tag = {
            .base = {
                .type = KERNAUX_MULTIBOOT2_ITAG_SMBIOS_TABLES,
                .size = sizeof(multiboot2_info_example2.tag_smbios_tables),
            },
            .major = 1,
            .minor = 2,
            .reserved = {0, 0, 0, 0, 0, 0},
        },
        .data = {0, 0, 0, 0, 0, 0, 0, 0},
    },
    .tag_acpi_old_rsdp = {
        .tag = {
            .base = {
                .type = KERNAUX_MULTIBOOT2_ITAG_ACPI_OLD_RSDP,
                .size = sizeof(multiboot2_info_example2.tag_acpi_old_rsdp),
            },
        },
        .data = {0, 0, 0, 0, 0, 0, 0, 0},
    },
    .tag_acpi_new_rsdp = {
        .tag = {
            .base = {
                .type = KERNAUX_MULTIBOOT2_ITAG_ACPI_NEW_RSDP,
                .size = sizeof(multiboot2_info_example2.tag_acpi_new_rsdp),
            },
        },
        .data = {0, 0, 0, 0, 0, 0, 0, 0},
    },
    .tag_networking_info = {
        .tag = {
            .base = {
                .type = KERNAUX_MULTIBOOT2_ITAG_NETWORKING_INFO,
                .size = sizeof(multiboot2_info_example2.tag_networking_info),
            },
        },
        .data = {0, 0, 0, 0, 0, 0, 0, 0},
    },
    .tag_efi_memory_map = {
        .tag = {
            .base = {
                .type = KERNAUX_MULTIBOOT2_ITAG_EFI_MEMORY_MAP,
                .size = sizeof(multiboot2_info_example2.tag_efi_memory_map),
            },
            .descriptor_size = 123,
            .descriptor_version = 1,
        },
        .data = {0, 0, 0, 0, 0, 0, 0, 0},
    },
    .tag_efi_boot_services_not_terminated = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_EFI_BOOT_SERVICES_NOT_TERMINATED,
            .size = sizeof(
                multiboot2_info_example2.tag_efi_boot_services_not_terminated
            ),
        },
    },
    .tag_efi_32bit_image_handle_ptr = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_EFI_32BIT_IMAGE_HANDLE_PTR,
            .size = sizeof(multiboot2_info_example2.tag_efi_32bit_image_handle_ptr),
        },
        .pointer = 0,
    },
    .tag_efi_64bit_image_handle_ptr = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_EFI_64BIT_IMAGE_HANDLE_PTR,
            .size = sizeof(multiboot2_info_example2.tag_efi_64bit_image_handle_ptr),
        },
        .pointer = 0,
    },
    .tag_image_load_base_phys_addr = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_IMAGE_LOAD_BASE_PHYS_ADDR,
            .size = sizeof(multiboot2_info_example2.tag_image_load_base_phys_addr),
        },
        .load_base_addr = 123,
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_NONE,
            .size = sizeof(multiboot2_info_example2.tag_none),
        },
    },
};

#include <kernaux/macro/packing_end.run>
