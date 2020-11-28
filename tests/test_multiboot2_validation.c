#include <kernaux/multiboot2.h>

#include <assert.h>

/************
 * Tag_None *
 ************/

static const struct KernAux_Multiboot2_Tag_None tag_none_valid = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_TAGTYPE_NONE,
        .size = 8,
    },
};

static const struct KernAux_Multiboot2_Tag_None tag_none_invalid_type = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_TAGTYPE_BOOT_CMD_LINE,
        .size = 8,
    },
};

static const struct KernAux_Multiboot2_Tag_None tag_none_invalid_size = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_TAGTYPE_NONE,
        .size = 9,
    },
};

/*******************
 * Tag_BootCmdLine *
 *******************/

static const struct {
    struct KernAux_Multiboot2_Tag_BootCmdLine tag;
    char cmdline[1];
} tag_boot_cmd_line_with_empty_cmdline_valid = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_BOOT_CMD_LINE,
            .size = 9,
        },
    },
    .cmdline = "\0",
};

static const struct {
    struct KernAux_Multiboot2_Tag_BootCmdLine tag;
    char cmdline[14];
} tag_boot_cmd_line_with_some_cmdline_valid = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_BOOT_CMD_LINE,
            .size = 22,
        },
    },
    .cmdline = "Hello, World!\0",
};

static const struct {
    struct KernAux_Multiboot2_Tag_BootCmdLine tag;
    char cmdline[1];
} tag_boot_cmd_line_invalid_type = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_NONE,
            .size = 9,
        },
    },
    .cmdline = "\0",
};

static const struct {
    struct KernAux_Multiboot2_Tag_BootCmdLine tag;
    char cmdline[1];
} tag_boot_cmd_line_with_empty_cmdline_invalid_size = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_BOOT_CMD_LINE,
            .size = 10,
        },
    },
    .cmdline = "\0",
};

static const struct {
    struct KernAux_Multiboot2_Tag_BootCmdLine tag;
    char cmdline[14];
} tag_boot_cmd_line_with_some_cmdline_invalid_size = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_BOOT_CMD_LINE,
            .size = 23,
        },
    },
    .cmdline = "Hello, World!\0",
};

/**********************
 * Tag_BootLoaderName *
 **********************/

static const struct {
    struct KernAux_Multiboot2_Tag_BootLoaderName tag;
    char name[1];
} tag_boot_loader_name_with_empty_name_valid = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_BOOT_LOADER_NAME,
            .size = 9,
        },
    },
    .name = "\0",
};

static const struct {
    struct KernAux_Multiboot2_Tag_BootLoaderName tag;
    char name[14];
} tag_boot_loader_name_with_some_name_valid = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_BOOT_LOADER_NAME,
            .size = 22,
        },
    },
    .name = "Hello, World!\0",
};

static const struct {
    struct KernAux_Multiboot2_Tag_BootLoaderName tag;
    char name[1];
} tag_boot_loader_name_invalid_type = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_NONE,
            .size = 9,
        },
    },
    .name = "\0",
};

static const struct {
    struct KernAux_Multiboot2_Tag_BootLoaderName tag;
    char name[1];
} tag_boot_loader_name_with_empty_name_invalid_size = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_BOOT_LOADER_NAME,
            .size = 10,
        },
    },
    .name = "\0",
};

static const struct {
    struct KernAux_Multiboot2_Tag_BootLoaderName tag;
    char name[14];
} tag_boot_loader_name_with_some_name_invalid_size = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_BOOT_LOADER_NAME,
            .size = 23,
        },
    },
    .name = "Hello, World!\0",
};

/**************
 * Tag_Module *
 **************/

static const struct {
    struct KernAux_Multiboot2_Tag_Module tag;
    char cmdline[1];
} tag_module_with_empty_name_valid = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_MODULE,
            .size = 17,
        },
        .mod_start = 123,
        .mod_end = 456,
    },
    .cmdline = "\0",
};

static const struct {
    struct KernAux_Multiboot2_Tag_Module tag;
    char cmdline[14];
} tag_module_with_some_name_valid = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_MODULE,
            .size = 30,
        },
        .mod_start = 123,
        .mod_end = 456,
    },
    .cmdline = "Hello, World!\0",
};

static const struct {
    struct KernAux_Multiboot2_Tag_Module tag;
    char cmdline[1];
} tag_module_invalid_type = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_NONE,
            .size = 17,
        },
        .mod_start = 123,
        .mod_end = 456,
    },
    .cmdline = "\0",
};

static const struct {
    struct KernAux_Multiboot2_Tag_Module tag;
    char cmdline[1];
} tag_module_with_empty_name_invalid_size = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_MODULE,
            .size = 18,
        },
        .mod_start = 123,
        .mod_end = 456,
    },
    .cmdline = "\0",
};

static const struct {
    struct KernAux_Multiboot2_Tag_Module tag;
    char cmdline[14];
} tag_module_with_some_name_invalid_size = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_MODULE,
            .size = 31,
        },
        .mod_start = 123,
        .mod_end = 456,
    },
    .cmdline = "Hello, World!\0",
};

static const struct {
    struct KernAux_Multiboot2_Tag_Module tag;
    char cmdline[14];
} tag_module_with_equal_start_end_invalid = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_MODULE,
            .size = 31,
        },
        .mod_start = 123,
        .mod_end = 123,
    },
    .cmdline = "Hello, World!\0",
};

static const struct {
    struct KernAux_Multiboot2_Tag_Module tag;
    char cmdline[14];
} tag_module_with_reversed_start_end_invalid = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_MODULE,
            .size = 31,
        },
        .mod_start = 456,
        .mod_end = 123,
    },
    .cmdline = "Hello, World!\0",
};

/***********************
 * Tag_BasicMemoryInfo *
 ***********************/

static const struct KernAux_Multiboot2_Tag_BasicMemoryInfo
tag_basic_memory_info_valid = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_TAGTYPE_BASIC_MEMORY_INFO,
        .size = 16,
    },
    .mem_lower = 123,
    .mem_upper = 123,
};

static const struct KernAux_Multiboot2_Tag_BasicMemoryInfo
tag_basic_memory_info_invalid_type = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_TAGTYPE_NONE,
        .size = 16,
    },
    .mem_lower = 123,
    .mem_upper = 123,
};

static const struct KernAux_Multiboot2_Tag_BasicMemoryInfo
tag_basic_memory_info_invalid_size = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_TAGTYPE_BASIC_MEMORY_INFO,
        .size = 17,
    },
    .mem_lower = 123,
    .mem_upper = 123,
};

/**********************
 * Tag_BIOSBootDevice *
 **********************/

static const struct KernAux_Multiboot2_Tag_BIOSBootDevice
tag_bios_boot_device_valid = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_TAGTYPE_BIOS_BOOT_DEVICE,
        .size = 20,
    },
    .bios_dev = 123,
    .partition = 456,
    .sub_partition = 789,
};

static const struct KernAux_Multiboot2_Tag_BIOSBootDevice
tag_bios_boot_device_invalid_type = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_TAGTYPE_NONE,
        .size = 20,
    },
    .bios_dev = 123,
    .partition = 456,
    .sub_partition = 789,
};

static const struct KernAux_Multiboot2_Tag_BIOSBootDevice
tag_bios_boot_device_invalid_size = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_TAGTYPE_BIOS_BOOT_DEVICE,
        .size = 21,
    },
    .bios_dev = 123,
    .partition = 456,
    .sub_partition = 789,
};

/*****************
 * Tag_MemoryMap *
 *****************/

static const struct KernAux_Multiboot2_Tag_MemoryMap
tag_memory_map_with_empty_data_valid = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_TAGTYPE_MEMORY_MAP,
        .size = 16,
    },
    .entry_size = 8,
    .entry_version = 0,
};

static const struct {
    struct KernAux_Multiboot2_Tag_MemoryMap tag;
    unsigned char data[8 * 2];
} tag_memory_map_with_some_small_data_items_valid = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_MEMORY_MAP,
            .size = 16 + 8 * 2,
        },
        .entry_size = 8,
        .entry_version = 123,
    },
};

static const struct {
    struct KernAux_Multiboot2_Tag_MemoryMap tag;
    unsigned char data[64 * 2];
} tag_memory_map_with_some_large_data_items_valid = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_MEMORY_MAP,
            .size = 16 + 64 * 2,
        },
        .entry_size = 64,
        .entry_version = 456,
    },
};

static const struct KernAux_Multiboot2_Tag_MemoryMap
tag_memory_map_invalid_type = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_TAGTYPE_NONE,
        .size = 16,
    },
    .entry_size = 8,
    .entry_version = 0,
};

static const struct KernAux_Multiboot2_Tag_MemoryMap
tag_memory_map_with_empty_data_invalid_size = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_TAGTYPE_MEMORY_MAP,
        .size = 16 + 1,
    },
    .entry_size = 8,
    .entry_version = 0,
};

static const struct {
    struct KernAux_Multiboot2_Tag_MemoryMap tag;
    unsigned char data[64 * 2 + 1];
} tag_memory_map_with_some_large_data_items_invalid_size = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_MEMORY_MAP,
            .size = 16 + 64 * 2 + 1,
        },
        .entry_size = 64,
        .entry_version = 456,
    },
};

/***************
 * Tag_VBEInfo *
 ***************/

static const struct KernAux_Multiboot2_Tag_VBEInfo
tag_vbe_info_valid = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_TAGTYPE_VBE_INFO,
        .size = 784,
    },
    .vbe_mode = 123,
    .vbe_interface_seg = 456,
    .vbe_interface_off = 789,
    .vbe_interface_len = 123,
    .vbe_control_info = {0, 0, 0},
    .vbe_mode_info = {0, 0, 0},
};

static const struct KernAux_Multiboot2_Tag_VBEInfo
tag_vbe_info_invalid_type = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_TAGTYPE_NONE,
        .size = 784,
    },
    .vbe_mode = 123,
    .vbe_interface_seg = 456,
    .vbe_interface_off = 789,
    .vbe_interface_len = 123,
    .vbe_control_info = {0, 0, 0},
    .vbe_mode_info = {0, 0, 0},
};

static const struct KernAux_Multiboot2_Tag_VBEInfo
tag_vbe_info_invalid_size = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_TAGTYPE_VBE_INFO,
        .size = 784 + 1,
    },
    .vbe_mode = 123,
    .vbe_interface_seg = 456,
    .vbe_interface_off = 789,
    .vbe_interface_len = 123,
    .vbe_control_info = {0, 0, 0},
    .vbe_mode_info = {0, 0, 0},
};

/**************
 * Multiboot2 *
 **************/

static const struct {
    struct KernAux_Multiboot2 multiboot2;
    struct KernAux_Multiboot2_Tag_None tag_none;
} multiboot2_empty_valid = {
    .multiboot2 = {
        .total_size = 8 + 8,
        .reserved1 = 0,
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_NONE,
            .size = 8,
        },
    },
};

static const struct {
    struct KernAux_Multiboot2 multiboot2;
    struct KernAux_Multiboot2_Tag_BasicMemoryInfo tag_basic_memory_info;
    struct KernAux_Multiboot2_Tag_None tag_none;
} multiboot2_with_some_additional_tag_valid = {
    .multiboot2 = {
        .total_size = 8 + 16 + 8,
        .reserved1 = 0,
    },
    .tag_basic_memory_info = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_BASIC_MEMORY_INFO,
            .size = 16,
        },
        .mem_lower = 123,
        .mem_upper = 123,
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_NONE,
            .size = 8,
        },
    },
};

static const struct {
    struct KernAux_Multiboot2 multiboot2;
    struct KernAux_Multiboot2_Tag_BasicMemoryInfo tag_basic_memory_info;
    struct KernAux_Multiboot2_Tag_BIOSBootDevice tag_bios_boot_device;
    unsigned char _align1[4];
    struct KernAux_Multiboot2_Tag_None tag_none;
} multiboot2_with_more_additional_tags_valid = {
    .multiboot2 = {
        .total_size = 8 + 16 + (20 + 4) + 8,
        .reserved1 = 0,
    },
    .tag_basic_memory_info = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_BASIC_MEMORY_INFO,
            .size = 16,
        },
        .mem_lower = 123,
        .mem_upper = 123,
    },
    .tag_bios_boot_device = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_BIOS_BOOT_DEVICE,
            .size = 20,
        },
        .bios_dev = 123,
        .partition = 456,
        .sub_partition = 789,
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_NONE,
            .size = 8,
        },
    },
};

static const struct {
    struct KernAux_Multiboot2 multiboot2;
    struct KernAux_Multiboot2_Tag_None tag_none;
} multiboot2_empty_invalid_size = {
    .multiboot2 = {
        .total_size = 8,
        .reserved1 = 0,
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_NONE,
            .size = 8,
        },
    },
};

static const struct KernAux_Multiboot2 multiboot2_without_none_tag_invalid = {
    .total_size = 8,
    .reserved1 = 0,
};

static const struct {
    struct KernAux_Multiboot2 multiboot2;
    struct KernAux_Multiboot2_Tag_BasicMemoryInfo tag_basic_memory_info;
} multiboot2_with_invalid_last_tag_invalid = {
    .multiboot2 = {
        .total_size = 8 + 16,
        .reserved1 = 0,
    },
    .tag_basic_memory_info = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_BASIC_MEMORY_INFO,
            .size = 16,
        },
        .mem_lower = 123,
        .mem_upper = 123,
    },
};

static const struct {
    struct KernAux_Multiboot2 multiboot2;
    struct KernAux_Multiboot2_Tag_BasicMemoryInfo tag_basic_memory_info;
    struct KernAux_Multiboot2_Tag_None tag_none1;
    struct KernAux_Multiboot2_Tag_BIOSBootDevice tag_bios_boot_device;
    unsigned char _align1[4];
    struct KernAux_Multiboot2_Tag_None tag_none2;
} multiboot2_with_early_none_tag_invalid = {
    .multiboot2 = {
        .total_size = 8 + 16 + 8 + (20 + 4) + 8,
        .reserved1 = 0,
    },
    .tag_basic_memory_info = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_BASIC_MEMORY_INFO,
            .size = 16,
        },
        .mem_lower = 123,
        .mem_upper = 123,
    },
    .tag_none1 = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_NONE,
            .size = 8,
        },
    },
    .tag_bios_boot_device = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_BIOS_BOOT_DEVICE,
            .size = 20,
        },
        .bios_dev = 123,
        .partition = 456,
        .sub_partition = 789,
    },
    .tag_none2 = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_NONE,
            .size = 8,
        },
    },
};

static const struct {
    struct KernAux_Multiboot2 multiboot2;
    struct KernAux_Multiboot2_Tag_BasicMemoryInfo tag_basic_memory_info;
    struct KernAux_Multiboot2_Tag_BIOSBootDevice tag_bios_boot_device;
    unsigned char _align1[4];
    struct KernAux_Multiboot2_Tag_None tag_none;
} multiboot2_with_more_additional_tags_invalid_size_too_big = {
    .multiboot2 = {
        .total_size = 8 + 16 + (20 + 4) + 8 + 1,
        .reserved1 = 0,
    },
    .tag_basic_memory_info = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_BASIC_MEMORY_INFO,
            .size = 16,
        },
        .mem_lower = 123,
        .mem_upper = 123,
    },
    .tag_bios_boot_device = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_BIOS_BOOT_DEVICE,
            .size = 20,
        },
        .bios_dev = 123,
        .partition = 456,
        .sub_partition = 789,
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_NONE,
            .size = 8,
        },
    },
};

static const struct {
    struct KernAux_Multiboot2 multiboot2;
    struct KernAux_Multiboot2_Tag_BasicMemoryInfo tag_basic_memory_info;
    struct KernAux_Multiboot2_Tag_BIOSBootDevice tag_bios_boot_device;
    unsigned char _align1[4];
    struct KernAux_Multiboot2_Tag_None tag_none;
} multiboot2_with_more_additional_tags_invalid_size_too_small = {
    .multiboot2 = {
        .total_size = 8 + 16 + (20 + 4) + 8 - 1,
        .reserved1 = 0,
    },
    .tag_basic_memory_info = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_BASIC_MEMORY_INFO,
            .size = 16,
        },
        .mem_lower = 123,
        .mem_upper = 123,
    },
    .tag_bios_boot_device = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_BIOS_BOOT_DEVICE,
            .size = 20,
        },
        .bios_dev = 123,
        .partition = 456,
        .sub_partition = 789,
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_NONE,
            .size = 8,
        },
    },
};

static const unsigned char multiboot2_example[864] = {
    96, 3, 0, 0, 0, 0, 0, 0, 21, 0, 0, 0, 12, 0, 0, 0,
    0, 0, 64, 0, 0, 0, 232, 133, 1, 0, 0, 0, 21, 0, 0, 0,
    104, 101, 108, 108, 111, 32, 107, 101, 114, 110, 101, 108, 0, 139, 69, 228,
    2, 0, 0, 0, 30, 0, 0, 0, 71, 82, 85, 66, 32, 50, 46, 48,
    50, 45, 50, 117, 98, 117, 110, 116, 117, 56, 46, 50, 48, 0, 0, 0,
    10, 0, 0, 0, 28, 0, 0, 0, 2, 1, 0, 240, 207, 212, 0, 0,
    0, 240, 0, 240, 3, 0, 240, 255, 240, 255, 240, 255, 1, 0, 0, 0,
    3, 0, 0, 0, 29, 0, 0, 0, 0, 32, 16, 0, 156, 50, 16, 0,
    104, 101, 108, 108, 111, 32, 109, 111, 100, 117, 108, 101, 0, 131, 255, 16,
    3, 0, 0, 0, 17, 0, 0, 0, 0, 64, 16, 0, 84, 82, 16, 0,
    0, 232, 99, 9, 0, 0, 235, 53, 6, 0, 0, 0, 160, 0, 0, 0,
    24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 252, 9, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 252, 9, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0,
    2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 238, 7, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 254, 7, 0, 0, 0, 0,
    0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 252, 255, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0,
    2, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 164, 1, 0, 0,
    10, 0, 0, 0, 40, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0,
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
    0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 217, 255, 255, 137,
    4, 0, 0, 0, 16, 0, 0, 0, 127, 2, 0, 0, 128, 251, 1, 0,
    5, 0, 0, 0, 20, 0, 0, 0, 224, 0, 0, 0, 255, 255, 255, 255,
    255, 255, 255, 255, 208, 137, 69, 212, 8, 0, 0, 0, 32, 0, 0, 0,
    0, 128, 11, 0, 0, 0, 0, 0, 160, 0, 0, 0, 80, 0, 0, 0,
    25, 0, 0, 0, 16, 2, 0, 0, 14, 0, 0, 0, 28, 0, 0, 0,
    82, 83, 68, 32, 80, 84, 82, 32, 60, 66, 79, 67, 72, 83, 32, 0,
    252, 21, 254, 7, 236, 0, 0, 235, 0, 0, 0, 0, 8, 0, 0, 0,
};

/********
 * main *
 ********/

int main()
{
    // Multiboot2

    assert(KernAux_Multiboot2_is_valid(
        (struct KernAux_Multiboot2*)multiboot2_example
    ));

    assert(KernAux_Multiboot2_is_valid(&multiboot2_empty_valid.multiboot2));

    assert(KernAux_Multiboot2_is_valid(
        &multiboot2_with_some_additional_tag_valid.multiboot2)
    );

    assert(KernAux_Multiboot2_is_valid(
        &multiboot2_with_more_additional_tags_valid.multiboot2)
    );

    assert(!KernAux_Multiboot2_is_valid(
        &multiboot2_empty_invalid_size.multiboot2
    ));

    assert(!KernAux_Multiboot2_is_valid(&multiboot2_without_none_tag_invalid));

    assert(!KernAux_Multiboot2_is_valid(
        &multiboot2_with_invalid_last_tag_invalid.multiboot2
    ));

    assert(!KernAux_Multiboot2_is_valid(
        &multiboot2_with_early_none_tag_invalid.multiboot2
    ));

    assert(!KernAux_Multiboot2_is_valid(
        &multiboot2_with_more_additional_tags_invalid_size_too_big.multiboot2)
    );

    assert(!KernAux_Multiboot2_is_valid(
        &multiboot2_with_more_additional_tags_invalid_size_too_small.multiboot2)
    );

    // TagBase

    assert(KernAux_Multiboot2_TagBase_is_valid(&tag_none_valid.base));
    assert(!KernAux_Multiboot2_TagBase_is_valid(&tag_none_invalid_size.base));

    assert(KernAux_Multiboot2_TagBase_is_valid(
        &tag_boot_cmd_line_with_empty_cmdline_valid.tag.base
    ));

    assert(KernAux_Multiboot2_TagBase_is_valid(
        &tag_boot_cmd_line_with_some_cmdline_valid.tag.base
    ));

    assert(!KernAux_Multiboot2_TagBase_is_valid(
        &tag_boot_cmd_line_with_empty_cmdline_invalid_size.tag.base
    ));

    assert(!KernAux_Multiboot2_TagBase_is_valid(
        &tag_boot_cmd_line_with_some_cmdline_invalid_size.tag.base
    ));

    assert(KernAux_Multiboot2_TagBase_is_valid(
        &tag_boot_loader_name_with_empty_name_valid.tag.base
    ));

    assert(KernAux_Multiboot2_TagBase_is_valid(
        &tag_boot_loader_name_with_some_name_valid.tag.base
    ));

    assert(!KernAux_Multiboot2_TagBase_is_valid(
        &tag_boot_loader_name_with_empty_name_invalid_size.tag.base
    ));

    assert(!KernAux_Multiboot2_TagBase_is_valid(
        &tag_boot_loader_name_with_some_name_invalid_size.tag.base
    ));

    assert(KernAux_Multiboot2_TagBase_is_valid(
        &tag_module_with_empty_name_valid.tag.base
    ));

    assert(KernAux_Multiboot2_TagBase_is_valid(
        &tag_module_with_some_name_valid.tag.base
    ));

    assert(!KernAux_Multiboot2_TagBase_is_valid(
        &tag_module_with_empty_name_invalid_size.tag.base
    ));

    assert(!KernAux_Multiboot2_TagBase_is_valid(
        &tag_module_with_some_name_invalid_size.tag.base
    ));

    assert(!KernAux_Multiboot2_TagBase_is_valid(
        &tag_module_with_equal_start_end_invalid.tag.base
    ));

    assert(!KernAux_Multiboot2_TagBase_is_valid(
        &tag_module_with_reversed_start_end_invalid.tag.base
    ));

    assert(KernAux_Multiboot2_TagBase_is_valid(
        &tag_basic_memory_info_valid.base
    ));

    assert(!KernAux_Multiboot2_TagBase_is_valid(
        &tag_basic_memory_info_invalid_size.base
    ));

    assert(KernAux_Multiboot2_TagBase_is_valid(
        &tag_bios_boot_device_valid.base
    ));

    assert(!KernAux_Multiboot2_TagBase_is_valid(
        &tag_bios_boot_device_invalid_size.base
    ));

    assert(KernAux_Multiboot2_TagBase_is_valid(
        &tag_memory_map_with_empty_data_valid.base
    ));

    assert(KernAux_Multiboot2_TagBase_is_valid(
        &tag_memory_map_with_some_small_data_items_valid.tag.base
    ));

    assert(KernAux_Multiboot2_TagBase_is_valid(
        &tag_memory_map_with_some_large_data_items_valid.tag.base
    ));

    assert(!KernAux_Multiboot2_TagBase_is_valid(
        &tag_memory_map_with_empty_data_invalid_size.base
    ));

    assert(!KernAux_Multiboot2_TagBase_is_valid(
        &tag_memory_map_with_some_large_data_items_invalid_size.tag.base
    ));

    assert(KernAux_Multiboot2_TagBase_is_valid(
        &tag_vbe_info_valid.base
    ));

    assert(!KernAux_Multiboot2_TagBase_is_valid(
        &tag_vbe_info_invalid_size.base
    ));

    // Tag_None

    assert(KernAux_Multiboot2_Tag_None_is_valid(&tag_none_valid));
    assert(!KernAux_Multiboot2_Tag_None_is_valid(&tag_none_invalid_type));
    assert(!KernAux_Multiboot2_Tag_None_is_valid(&tag_none_invalid_size));

    // Tag_BootCmdLine

    assert(KernAux_Multiboot2_Tag_BootCmdLine_is_valid(
        &tag_boot_cmd_line_with_empty_cmdline_valid.tag
    ));

    assert(KernAux_Multiboot2_Tag_BootCmdLine_is_valid(
        &tag_boot_cmd_line_with_some_cmdline_valid.tag
    ));

    assert(!KernAux_Multiboot2_Tag_BootCmdLine_is_valid(
        &tag_boot_cmd_line_invalid_type.tag
    ));

    assert(!KernAux_Multiboot2_Tag_BootCmdLine_is_valid(
        &tag_boot_cmd_line_with_empty_cmdline_invalid_size.tag
    ));

    assert(!KernAux_Multiboot2_Tag_BootCmdLine_is_valid(
        &tag_boot_cmd_line_with_some_cmdline_invalid_size.tag
    ));

    // Tag_BootLoaderName

    assert(KernAux_Multiboot2_Tag_BootLoaderName_is_valid(
        &tag_boot_loader_name_with_empty_name_valid.tag
    ));

    assert(KernAux_Multiboot2_Tag_BootLoaderName_is_valid(
        &tag_boot_loader_name_with_some_name_valid.tag
    ));

    assert(!KernAux_Multiboot2_Tag_BootLoaderName_is_valid(
        &tag_boot_loader_name_invalid_type.tag
    ));

    assert(!KernAux_Multiboot2_Tag_BootLoaderName_is_valid(
        &tag_boot_loader_name_with_empty_name_invalid_size.tag
    ));

    assert(!KernAux_Multiboot2_Tag_BootLoaderName_is_valid(
        &tag_boot_loader_name_with_some_name_invalid_size.tag
    ));

    // Tag_Module

    assert(KernAux_Multiboot2_Tag_Module_is_valid(
        &tag_module_with_empty_name_valid.tag
    ));

    assert(KernAux_Multiboot2_Tag_Module_is_valid(
        &tag_module_with_some_name_valid.tag
    ));

    assert(!KernAux_Multiboot2_Tag_Module_is_valid(
        &tag_module_invalid_type.tag
    ));

    assert(!KernAux_Multiboot2_Tag_Module_is_valid(
        &tag_module_with_empty_name_invalid_size.tag
    ));

    assert(!KernAux_Multiboot2_Tag_Module_is_valid(
        &tag_module_with_some_name_invalid_size.tag
    ));

    assert(!KernAux_Multiboot2_Tag_Module_is_valid(
        &tag_module_with_equal_start_end_invalid.tag
    ));

    assert(!KernAux_Multiboot2_Tag_Module_is_valid(
        &tag_module_with_reversed_start_end_invalid.tag
    ));

    // Tag_BasicMemoryInfo

    assert(KernAux_Multiboot2_Tag_BasicMemoryInfo_is_valid(
        &tag_basic_memory_info_valid
    ));

    assert(!KernAux_Multiboot2_Tag_BasicMemoryInfo_is_valid(
        &tag_basic_memory_info_invalid_type
    ));

    assert(!KernAux_Multiboot2_Tag_BasicMemoryInfo_is_valid(
        &tag_basic_memory_info_invalid_size
    ));

    // Tag_BIOSBootDevice

    assert(KernAux_Multiboot2_Tag_BIOSBootDevice_is_valid(
        &tag_bios_boot_device_valid
    ));

    assert(!KernAux_Multiboot2_Tag_BIOSBootDevice_is_valid(
        &tag_bios_boot_device_invalid_type
    ));

    assert(!KernAux_Multiboot2_Tag_BIOSBootDevice_is_valid(
        &tag_bios_boot_device_invalid_size
    ));

    // Tag_MemoryMap

    assert(KernAux_Multiboot2_Tag_MemoryMap_is_valid(
        &tag_memory_map_with_empty_data_valid
    ));

    assert(KernAux_Multiboot2_Tag_MemoryMap_is_valid(
        &tag_memory_map_with_some_small_data_items_valid.tag
    ));

    assert(KernAux_Multiboot2_Tag_MemoryMap_is_valid(
        &tag_memory_map_with_some_large_data_items_valid.tag
    ));

    assert(!KernAux_Multiboot2_Tag_MemoryMap_is_valid(
        &tag_memory_map_invalid_type
    ));

    assert(!KernAux_Multiboot2_Tag_MemoryMap_is_valid(
        &tag_memory_map_with_some_large_data_items_invalid_size.tag
    ));

    // Tag_VBEInfo

    assert(KernAux_Multiboot2_Tag_VBEInfo_is_valid(
        &tag_vbe_info_valid
    ));

    assert(!KernAux_Multiboot2_Tag_VBEInfo_is_valid(
        &tag_vbe_info_invalid_type
    ));

    assert(!KernAux_Multiboot2_Tag_VBEInfo_is_valid(
        &tag_vbe_info_invalid_size
    ));

    return 0;
}
