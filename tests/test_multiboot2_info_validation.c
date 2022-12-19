#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/macro.h>
#include <kernaux/multiboot2.h>

#include <assert.h>

#include "../fixtures/multiboot2_info_example1.h"
#include "../fixtures/multiboot2_info_example2.h"

#include <kernaux/macro/packing_start.run>

/************
 * Tag_None *
 ************/

static const struct KernAux_Multiboot2_ITag_None tag_none_valid = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_ITAG_NONE,
        .size = 8,
    },
};

static const struct KernAux_Multiboot2_ITag_None tag_none_invalid_type = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_ITAG_BOOT_CMD_LINE,
        .size = 8,
    },
};

static const struct KernAux_Multiboot2_ITag_None tag_none_invalid_size = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_ITAG_NONE,
        .size = 9,
    },
};

/*******************
 * Tag_BootCmdLine *
 *******************/

static const struct {
    struct KernAux_Multiboot2_ITag_BootCmdLine tag;
    char cmdline[1];
} KERNAUX_PACKED tag_boot_cmd_line_with_empty_cmdline_valid = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_BOOT_CMD_LINE,
            .size = 9,
        },
    },
    .cmdline = "\0",
};

static const struct {
    struct KernAux_Multiboot2_ITag_BootCmdLine tag;
    char cmdline[14];
} KERNAUX_PACKED tag_boot_cmd_line_with_some_cmdline_valid = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_BOOT_CMD_LINE,
            .size = 22,
        },
    },
    .cmdline = "Hello, World!\0",
};

static const struct {
    struct KernAux_Multiboot2_ITag_BootCmdLine tag;
    char cmdline[1];
} KERNAUX_PACKED tag_boot_cmd_line_invalid_type = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_NONE,
            .size = 9,
        },
    },
    .cmdline = "\0",
};

static const struct {
    struct KernAux_Multiboot2_ITag_BootCmdLine tag;
    char cmdline[1];
} KERNAUX_PACKED tag_boot_cmd_line_with_empty_cmdline_invalid_size = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_BOOT_CMD_LINE,
            .size = 10,
        },
    },
    .cmdline = "\0",
};

static const struct {
    struct KernAux_Multiboot2_ITag_BootCmdLine tag;
    char cmdline[14];
} KERNAUX_PACKED tag_boot_cmd_line_with_some_cmdline_invalid_size = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_BOOT_CMD_LINE,
            .size = 23,
        },
    },
    .cmdline = "Hello, World!\0",
};

/**********************
 * Tag_BootLoaderName *
 **********************/

static const struct {
    struct KernAux_Multiboot2_ITag_BootLoaderName tag;
    char name[1];
} KERNAUX_PACKED tag_boot_loader_name_with_empty_name_valid = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_BOOT_LOADER_NAME,
            .size = 9,
        },
    },
    .name = "\0",
};

static const struct {
    struct KernAux_Multiboot2_ITag_BootLoaderName tag;
    char name[14];
} KERNAUX_PACKED tag_boot_loader_name_with_some_name_valid = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_BOOT_LOADER_NAME,
            .size = 22,
        },
    },
    .name = "Hello, World!\0",
};

static const struct {
    struct KernAux_Multiboot2_ITag_BootLoaderName tag;
    char name[1];
} KERNAUX_PACKED tag_boot_loader_name_invalid_type = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_NONE,
            .size = 9,
        },
    },
    .name = "\0",
};

static const struct {
    struct KernAux_Multiboot2_ITag_BootLoaderName tag;
    char name[1];
} KERNAUX_PACKED tag_boot_loader_name_with_empty_name_invalid_size = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_BOOT_LOADER_NAME,
            .size = 10,
        },
    },
    .name = "\0",
};

static const struct {
    struct KernAux_Multiboot2_ITag_BootLoaderName tag;
    char name[14];
} KERNAUX_PACKED tag_boot_loader_name_with_some_name_invalid_size = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_BOOT_LOADER_NAME,
            .size = 23,
        },
    },
    .name = "Hello, World!\0",
};

/**************
 * Tag_Module *
 **************/

static const struct {
    struct KernAux_Multiboot2_ITag_Module tag;
    char cmdline[1];
} KERNAUX_PACKED tag_module_with_empty_name_valid = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_MODULE,
            .size = 17,
        },
        .mod_start = 123,
        .mod_end = 456,
    },
    .cmdline = "\0",
};

static const struct {
    struct KernAux_Multiboot2_ITag_Module tag;
    char cmdline[14];
} KERNAUX_PACKED tag_module_with_some_name_valid = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_MODULE,
            .size = 30,
        },
        .mod_start = 123,
        .mod_end = 456,
    },
    .cmdline = "Hello, World!\0",
};

static const struct {
    struct KernAux_Multiboot2_ITag_Module tag;
    char cmdline[1];
} KERNAUX_PACKED tag_module_invalid_type = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_NONE,
            .size = 17,
        },
        .mod_start = 123,
        .mod_end = 456,
    },
    .cmdline = "\0",
};

static const struct {
    struct KernAux_Multiboot2_ITag_Module tag;
    char cmdline[1];
} KERNAUX_PACKED tag_module_with_empty_name_invalid_size = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_MODULE,
            .size = 18,
        },
        .mod_start = 123,
        .mod_end = 456,
    },
    .cmdline = "\0",
};

static const struct {
    struct KernAux_Multiboot2_ITag_Module tag;
    char cmdline[14];
} KERNAUX_PACKED tag_module_with_some_name_invalid_size = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_MODULE,
            .size = 31,
        },
        .mod_start = 123,
        .mod_end = 456,
    },
    .cmdline = "Hello, World!\0",
};

static const struct {
    struct KernAux_Multiboot2_ITag_Module tag;
    char cmdline[14];
} KERNAUX_PACKED tag_module_with_equal_start_end_invalid = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_MODULE,
            .size = 31,
        },
        .mod_start = 123,
        .mod_end = 123,
    },
    .cmdline = "Hello, World!\0",
};

static const struct {
    struct KernAux_Multiboot2_ITag_Module tag;
    char cmdline[14];
} KERNAUX_PACKED tag_module_with_reversed_start_end_invalid = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_MODULE,
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

static const struct KernAux_Multiboot2_ITag_BasicMemoryInfo
tag_basic_memory_info_valid = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_ITAG_BASIC_MEMORY_INFO,
        .size = 16,
    },
    .mem_lower = 123,
    .mem_upper = 123,
};

static const struct KernAux_Multiboot2_ITag_BasicMemoryInfo
tag_basic_memory_info_invalid_type = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_ITAG_NONE,
        .size = 16,
    },
    .mem_lower = 123,
    .mem_upper = 123,
};

static const struct KernAux_Multiboot2_ITag_BasicMemoryInfo
tag_basic_memory_info_invalid_size = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_ITAG_BASIC_MEMORY_INFO,
        .size = 17,
    },
    .mem_lower = 123,
    .mem_upper = 123,
};

/**********************
 * Tag_BIOSBootDevice *
 **********************/

static const struct KernAux_Multiboot2_ITag_BIOSBootDevice
tag_bios_boot_device_valid = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_ITAG_BIOS_BOOT_DEVICE,
        .size = 20,
    },
    .biosdev = 123,
    .partition = 456,
    .sub_partition = 789,
};

static const struct KernAux_Multiboot2_ITag_BIOSBootDevice
tag_bios_boot_device_invalid_type = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_ITAG_NONE,
        .size = 20,
    },
    .biosdev = 123,
    .partition = 456,
    .sub_partition = 789,
};

static const struct KernAux_Multiboot2_ITag_BIOSBootDevice
tag_bios_boot_device_invalid_size = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_ITAG_BIOS_BOOT_DEVICE,
        .size = 21,
    },
    .biosdev = 123,
    .partition = 456,
    .sub_partition = 789,
};

/*****************
 * Tag_MemoryMap *
 *****************/

static const struct KernAux_Multiboot2_ITag_MemoryMap
tag_memory_map_with_empty_data_valid = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_ITAG_MEMORY_MAP,
        .size = 16,
    },
    .entry_size = 8,
    .entry_version = 0,
};

static const struct {
    struct KernAux_Multiboot2_ITag_MemoryMap tag;
    unsigned char data[8 * 2];
} KERNAUX_PACKED tag_memory_map_with_some_small_data_items_valid = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_MEMORY_MAP,
            .size = 16 + 8 * 2,
        },
        .entry_size = 8,
        .entry_version = 123,
    },
};

static const struct {
    struct KernAux_Multiboot2_ITag_MemoryMap tag;
    unsigned char data[64 * 2];
} KERNAUX_PACKED tag_memory_map_with_some_large_data_items_valid = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_MEMORY_MAP,
            .size = 16 + 64 * 2,
        },
        .entry_size = 64,
        .entry_version = 456,
    },
};

static const struct KernAux_Multiboot2_ITag_MemoryMap
tag_memory_map_invalid_type = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_ITAG_NONE,
        .size = 16,
    },
    .entry_size = 8,
    .entry_version = 0,
};

static const struct KernAux_Multiboot2_ITag_MemoryMap
tag_memory_map_with_empty_data_invalid_size = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_ITAG_MEMORY_MAP,
        .size = 16 + 1,
    },
    .entry_size = 8,
    .entry_version = 0,
};

static const struct {
    struct KernAux_Multiboot2_ITag_MemoryMap tag;
    unsigned char data[64 * 2 + 1];
} KERNAUX_PACKED tag_memory_map_with_some_large_data_items_invalid_size = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_MEMORY_MAP,
            .size = 16 + 64 * 2 + 1,
        },
        .entry_size = 64,
        .entry_version = 456,
    },
};

static const struct KernAux_Multiboot2_ITag_MemoryMap
tag_memory_map_with_empty_data_invalid_entry_size_zero = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_ITAG_MEMORY_MAP,
        .size = 16,
    },
    .entry_size = 0,
    .entry_version = 0,
};

static const struct KernAux_Multiboot2_ITag_MemoryMap
tag_memory_map_with_empty_data_invalid_entry_size_not_mul8 = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_ITAG_MEMORY_MAP,
        .size = 16,
    },
    .entry_size = 9,
    .entry_version = 0,
};

static const struct {
    struct KernAux_Multiboot2_ITag_MemoryMap tag;
    unsigned char data[9 * 2];
} KERNAUX_PACKED tag_memory_map_with_some_small_data_items_invalid_entry_size_not_mul8 = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_MEMORY_MAP,
            .size = 16 + 9 * 2,
        },
        .entry_size = 9,
        .entry_version = 123,
    },
};

static const struct {
    struct KernAux_Multiboot2_ITag_MemoryMap tag;
    unsigned char data[63 * 2];
} KERNAUX_PACKED tag_memory_map_with_some_large_data_items_invalid_entry_size_not_mul8 = {
    .tag = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_MEMORY_MAP,
            .size = 16 + 63 * 2,
        },
        .entry_size = 63,
        .entry_version = 123,
    },
};

/***************
 * Tag_VBEInfo *
 ***************/

static const struct KernAux_Multiboot2_ITag_VBEInfo
tag_vbe_info_valid = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_ITAG_VBE_INFO,
        .size = 784,
    },
    .vbe_mode = 123,
    .vbe_interface_seg = 456,
    .vbe_interface_off = 789,
    .vbe_interface_len = 123,
    .vbe_control_info = {0, 0, 0},
    .vbe_mode_info = {0, 0, 0},
};

static const struct KernAux_Multiboot2_ITag_VBEInfo
tag_vbe_info_invalid_type = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_ITAG_NONE,
        .size = 784,
    },
    .vbe_mode = 123,
    .vbe_interface_seg = 456,
    .vbe_interface_off = 789,
    .vbe_interface_len = 123,
    .vbe_control_info = {0, 0, 0},
    .vbe_mode_info = {0, 0, 0},
};

static const struct KernAux_Multiboot2_ITag_VBEInfo
tag_vbe_info_invalid_size = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_ITAG_VBE_INFO,
        .size = 784 + 1,
    },
    .vbe_mode = 123,
    .vbe_interface_seg = 456,
    .vbe_interface_off = 789,
    .vbe_interface_len = 123,
    .vbe_control_info = {0, 0, 0},
    .vbe_mode_info = {0, 0, 0},
};

/******************
 * Tag_ELFSymbols *
 ******************/

static const struct KernAux_Multiboot2_ITag_ELFSymbols
tag_elf_symbols_with_zero_entsize_valid = {
    .base = {
        .type = KERNAUX_MULTIBOOT2_ITAG_ELF_SYMBOLS,
        .size = 20,
    },
    .num = 0,
    .entsize = 0,
    .shndx = 0,
};

/**************
 * Multiboot2 *
 **************/

static const struct {
    struct KernAux_Multiboot2_Info multiboot2_info;
    struct KernAux_Multiboot2_ITag_None tag_none;
} KERNAUX_PACKED multiboot2_empty_valid = {
    .multiboot2_info = {
        .total_size = 8 + 8,
        .reserved = 0,
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_NONE,
            .size = 8,
        },
    },
};

static const struct {
    struct KernAux_Multiboot2_Info multiboot2_info;
    struct KernAux_Multiboot2_ITag_BasicMemoryInfo tag_basic_memory_info;
    struct KernAux_Multiboot2_ITag_None tag_none;
} KERNAUX_PACKED multiboot2_with_some_additional_tag_valid = {
    .multiboot2_info = {
        .total_size = 8 + 16 + 8,
        .reserved = 0,
    },
    .tag_basic_memory_info = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_BASIC_MEMORY_INFO,
            .size = 16,
        },
        .mem_lower = 123,
        .mem_upper = 123,
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_NONE,
            .size = 8,
        },
    },
};

static const struct {
    struct KernAux_Multiboot2_Info multiboot2_info;
    struct KernAux_Multiboot2_ITag_BasicMemoryInfo tag_basic_memory_info;
    struct KernAux_Multiboot2_ITag_BIOSBootDevice tag_bios_boot_device;
    unsigned char _align1[4];
    struct KernAux_Multiboot2_ITag_None tag_none;
} KERNAUX_PACKED multiboot2_with_more_additional_tags_valid = {
    .multiboot2_info = {
        .total_size = 8 + 16 + (20 + 4) + 8,
        .reserved = 0,
    },
    .tag_basic_memory_info = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_BASIC_MEMORY_INFO,
            .size = 16,
        },
        .mem_lower = 123,
        .mem_upper = 123,
    },
    .tag_bios_boot_device = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_BIOS_BOOT_DEVICE,
            .size = 20,
        },
        .biosdev = 123,
        .partition = 456,
        .sub_partition = 789,
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_NONE,
            .size = 8,
        },
    },
};

static const struct {
    struct KernAux_Multiboot2_Info multiboot2_info;
    struct KernAux_Multiboot2_ITag_None tag_none;
} KERNAUX_PACKED multiboot2_empty_invalid_size = {
    .multiboot2_info = {
        .total_size = 8,
        .reserved = 0,
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_NONE,
            .size = 8,
        },
    },
};

static const struct KernAux_Multiboot2_Info
multiboot2_without_none_tag_invalid = {
    .total_size = 8,
    .reserved = 0,
};

static const struct {
    struct KernAux_Multiboot2_Info multiboot2_info;
    struct KernAux_Multiboot2_ITag_BasicMemoryInfo tag_basic_memory_info;
} KERNAUX_PACKED multiboot2_with_invalid_last_tag_invalid = {
    .multiboot2_info = {
        .total_size = 8 + 16,
        .reserved = 0,
    },
    .tag_basic_memory_info = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_BASIC_MEMORY_INFO,
            .size = 16,
        },
        .mem_lower = 123,
        .mem_upper = 123,
    },
};

static const struct {
    struct KernAux_Multiboot2_Info multiboot2_info;
    struct KernAux_Multiboot2_ITag_BasicMemoryInfo tag_basic_memory_info;
    struct KernAux_Multiboot2_ITag_None tag_none1;
    struct KernAux_Multiboot2_ITag_BIOSBootDevice tag_bios_boot_device;
    unsigned char _align1[4];
    struct KernAux_Multiboot2_ITag_None tag_none2;
} KERNAUX_PACKED multiboot2_with_early_none_tag_invalid = {
    .multiboot2_info = {
        .total_size = 8 + 16 + 8 + (20 + 4) + 8,
        .reserved = 0,
    },
    .tag_basic_memory_info = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_BASIC_MEMORY_INFO,
            .size = 16,
        },
        .mem_lower = 123,
        .mem_upper = 123,
    },
    .tag_none1 = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_NONE,
            .size = 8,
        },
    },
    .tag_bios_boot_device = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_BIOS_BOOT_DEVICE,
            .size = 20,
        },
        .biosdev = 123,
        .partition = 456,
        .sub_partition = 789,
    },
    .tag_none2 = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_NONE,
            .size = 8,
        },
    },
};

static const struct {
    struct KernAux_Multiboot2_Info multiboot2_info;
    struct KernAux_Multiboot2_ITag_BasicMemoryInfo tag_basic_memory_info;
    struct KernAux_Multiboot2_ITag_BIOSBootDevice tag_bios_boot_device;
    unsigned char _align1[4];
    struct KernAux_Multiboot2_ITag_None tag_none;
} KERNAUX_PACKED multiboot2_with_more_additional_tags_invalid_size_too_big = {
    .multiboot2_info = {
        .total_size = 8 + 16 + (20 + 4) + 8 + 1,
        .reserved = 0,
    },
    .tag_basic_memory_info = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_BASIC_MEMORY_INFO,
            .size = 16,
        },
        .mem_lower = 123,
        .mem_upper = 123,
    },
    .tag_bios_boot_device = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_BIOS_BOOT_DEVICE,
            .size = 20,
        },
        .biosdev = 123,
        .partition = 456,
        .sub_partition = 789,
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_NONE,
            .size = 8,
        },
    },
};

static const struct {
    struct KernAux_Multiboot2_Info multiboot2_info;
    struct KernAux_Multiboot2_ITag_BasicMemoryInfo tag_basic_memory_info;
    struct KernAux_Multiboot2_ITag_BIOSBootDevice tag_bios_boot_device;
    unsigned char _align1[4];
    struct KernAux_Multiboot2_ITag_None tag_none;
} KERNAUX_PACKED multiboot2_with_more_additional_tags_invalid_size_too_small = {
    .multiboot2_info = {
        .total_size = 8 + 16 + (20 + 4) + 8 - 1,
        .reserved = 0,
    },
    .tag_basic_memory_info = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_BASIC_MEMORY_INFO,
            .size = 16,
        },
        .mem_lower = 123,
        .mem_upper = 123,
    },
    .tag_bios_boot_device = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_BIOS_BOOT_DEVICE,
            .size = 20,
        },
        .biosdev = 123,
        .partition = 456,
        .sub_partition = 789,
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_NONE,
            .size = 8,
        },
    },
};

#include <kernaux/macro/packing_end.run>

/********
 * main *
 ********/

void test_main()
{
    // Multiboot2

    assert(KernAux_Multiboot2_Info_is_valid(
        (struct KernAux_Multiboot2_Info*)&multiboot2_info_example1
    ));

    assert(KernAux_Multiboot2_Info_is_valid(
        (struct KernAux_Multiboot2_Info*)&multiboot2_info_example2
    ));

    assert(KernAux_Multiboot2_Info_is_valid(
        &multiboot2_empty_valid.multiboot2_info
    ));

    assert(KernAux_Multiboot2_Info_is_valid(
        &multiboot2_with_some_additional_tag_valid.multiboot2_info)
    );

    assert(KernAux_Multiboot2_Info_is_valid(
        &multiboot2_with_more_additional_tags_valid.multiboot2_info)
    );

    assert(!KernAux_Multiboot2_Info_is_valid(
        &multiboot2_empty_invalid_size.multiboot2_info
    ));

    assert(!KernAux_Multiboot2_Info_is_valid(
        &multiboot2_without_none_tag_invalid
    ));

    assert(!KernAux_Multiboot2_Info_is_valid(
        &multiboot2_with_invalid_last_tag_invalid.multiboot2_info
    ));

    assert(!KernAux_Multiboot2_Info_is_valid(
        &multiboot2_with_early_none_tag_invalid.multiboot2_info
    ));

    assert(!KernAux_Multiboot2_Info_is_valid(
        &multiboot2_with_more_additional_tags_invalid_size_too_big.multiboot2_info
    ));

    assert(!KernAux_Multiboot2_Info_is_valid(
        &multiboot2_with_more_additional_tags_invalid_size_too_small.multiboot2_info
    ));

    // ITagBase

    assert(KernAux_Multiboot2_ITagBase_is_valid(&tag_none_valid.base));
    assert(!KernAux_Multiboot2_ITagBase_is_valid(&tag_none_invalid_size.base));

    assert(KernAux_Multiboot2_ITagBase_is_valid(
        &tag_boot_cmd_line_with_empty_cmdline_valid.tag.base
    ));

    assert(KernAux_Multiboot2_ITagBase_is_valid(
        &tag_boot_cmd_line_with_some_cmdline_valid.tag.base
    ));

    assert(!KernAux_Multiboot2_ITagBase_is_valid(
        &tag_boot_cmd_line_with_empty_cmdline_invalid_size.tag.base
    ));

    assert(!KernAux_Multiboot2_ITagBase_is_valid(
        &tag_boot_cmd_line_with_some_cmdline_invalid_size.tag.base
    ));

    assert(KernAux_Multiboot2_ITagBase_is_valid(
        &tag_boot_loader_name_with_empty_name_valid.tag.base
    ));

    assert(KernAux_Multiboot2_ITagBase_is_valid(
        &tag_boot_loader_name_with_some_name_valid.tag.base
    ));

    assert(!KernAux_Multiboot2_ITagBase_is_valid(
        &tag_boot_loader_name_with_empty_name_invalid_size.tag.base
    ));

    assert(!KernAux_Multiboot2_ITagBase_is_valid(
        &tag_boot_loader_name_with_some_name_invalid_size.tag.base
    ));

    assert(KernAux_Multiboot2_ITagBase_is_valid(
        &tag_module_with_empty_name_valid.tag.base
    ));

    assert(KernAux_Multiboot2_ITagBase_is_valid(
        &tag_module_with_some_name_valid.tag.base
    ));

    assert(!KernAux_Multiboot2_ITagBase_is_valid(
        &tag_module_with_empty_name_invalid_size.tag.base
    ));

    assert(!KernAux_Multiboot2_ITagBase_is_valid(
        &tag_module_with_some_name_invalid_size.tag.base
    ));

    assert(!KernAux_Multiboot2_ITagBase_is_valid(
        &tag_module_with_equal_start_end_invalid.tag.base
    ));

    assert(!KernAux_Multiboot2_ITagBase_is_valid(
        &tag_module_with_reversed_start_end_invalid.tag.base
    ));

    assert(KernAux_Multiboot2_ITagBase_is_valid(
        &tag_basic_memory_info_valid.base
    ));

    assert(!KernAux_Multiboot2_ITagBase_is_valid(
        &tag_basic_memory_info_invalid_size.base
    ));

    assert(KernAux_Multiboot2_ITagBase_is_valid(
        &tag_bios_boot_device_valid.base
    ));

    assert(!KernAux_Multiboot2_ITagBase_is_valid(
        &tag_bios_boot_device_invalid_size.base
    ));

    assert(KernAux_Multiboot2_ITagBase_is_valid(
        &tag_memory_map_with_empty_data_valid.base
    ));

    assert(KernAux_Multiboot2_ITagBase_is_valid(
        &tag_memory_map_with_some_small_data_items_valid.tag.base
    ));

    assert(KernAux_Multiboot2_ITagBase_is_valid(
        &tag_memory_map_with_some_large_data_items_valid.tag.base
    ));

    assert(!KernAux_Multiboot2_ITagBase_is_valid(
        &tag_memory_map_with_empty_data_invalid_size.base
    ));

    assert(!KernAux_Multiboot2_ITagBase_is_valid(
        &tag_memory_map_with_some_large_data_items_invalid_size.tag.base
    ));

    assert(!KernAux_Multiboot2_ITagBase_is_valid(
        &tag_memory_map_with_empty_data_invalid_entry_size_zero.base
    ));

    assert(!KernAux_Multiboot2_ITagBase_is_valid(
        &tag_memory_map_with_empty_data_invalid_entry_size_not_mul8.base
    ));

    assert(!KernAux_Multiboot2_ITagBase_is_valid(
        &tag_memory_map_with_some_small_data_items_invalid_entry_size_not_mul8
            .tag.base
    ));

    assert(!KernAux_Multiboot2_ITagBase_is_valid(
        &tag_memory_map_with_some_large_data_items_invalid_entry_size_not_mul8
            .tag.base
    ));

    assert(KernAux_Multiboot2_ITagBase_is_valid(
        &tag_vbe_info_valid.base
    ));

    assert(!KernAux_Multiboot2_ITagBase_is_valid(
        &tag_vbe_info_invalid_size.base
    ));

    assert(KernAux_Multiboot2_ITagBase_is_valid(
        &tag_elf_symbols_with_zero_entsize_valid.base
    ));

    // Tag_None

    assert(KernAux_Multiboot2_ITag_None_is_valid(&tag_none_valid));
    assert(!KernAux_Multiboot2_ITag_None_is_valid(&tag_none_invalid_type));
    assert(!KernAux_Multiboot2_ITag_None_is_valid(&tag_none_invalid_size));

    // Tag_BootCmdLine

    assert(KernAux_Multiboot2_ITag_BootCmdLine_is_valid(
        &tag_boot_cmd_line_with_empty_cmdline_valid.tag
    ));

    assert(KernAux_Multiboot2_ITag_BootCmdLine_is_valid(
        &tag_boot_cmd_line_with_some_cmdline_valid.tag
    ));

    assert(!KernAux_Multiboot2_ITag_BootCmdLine_is_valid(
        &tag_boot_cmd_line_invalid_type.tag
    ));

    assert(!KernAux_Multiboot2_ITag_BootCmdLine_is_valid(
        &tag_boot_cmd_line_with_empty_cmdline_invalid_size.tag
    ));

    assert(!KernAux_Multiboot2_ITag_BootCmdLine_is_valid(
        &tag_boot_cmd_line_with_some_cmdline_invalid_size.tag
    ));

    // Tag_BootLoaderName

    assert(KernAux_Multiboot2_ITag_BootLoaderName_is_valid(
        &tag_boot_loader_name_with_empty_name_valid.tag
    ));

    assert(KernAux_Multiboot2_ITag_BootLoaderName_is_valid(
        &tag_boot_loader_name_with_some_name_valid.tag
    ));

    assert(!KernAux_Multiboot2_ITag_BootLoaderName_is_valid(
        &tag_boot_loader_name_invalid_type.tag
    ));

    assert(!KernAux_Multiboot2_ITag_BootLoaderName_is_valid(
        &tag_boot_loader_name_with_empty_name_invalid_size.tag
    ));

    assert(!KernAux_Multiboot2_ITag_BootLoaderName_is_valid(
        &tag_boot_loader_name_with_some_name_invalid_size.tag
    ));

    // Tag_Module

    assert(KernAux_Multiboot2_ITag_Module_is_valid(
        &tag_module_with_empty_name_valid.tag
    ));

    assert(KernAux_Multiboot2_ITag_Module_is_valid(
        &tag_module_with_some_name_valid.tag
    ));

    assert(!KernAux_Multiboot2_ITag_Module_is_valid(
        &tag_module_invalid_type.tag
    ));

    assert(!KernAux_Multiboot2_ITag_Module_is_valid(
        &tag_module_with_empty_name_invalid_size.tag
    ));

    assert(!KernAux_Multiboot2_ITag_Module_is_valid(
        &tag_module_with_some_name_invalid_size.tag
    ));

    assert(!KernAux_Multiboot2_ITag_Module_is_valid(
        &tag_module_with_equal_start_end_invalid.tag
    ));

    assert(!KernAux_Multiboot2_ITag_Module_is_valid(
        &tag_module_with_reversed_start_end_invalid.tag
    ));

    // Tag_BasicMemoryInfo

    assert(KernAux_Multiboot2_ITag_BasicMemoryInfo_is_valid(
        &tag_basic_memory_info_valid
    ));

    assert(!KernAux_Multiboot2_ITag_BasicMemoryInfo_is_valid(
        &tag_basic_memory_info_invalid_type
    ));

    assert(!KernAux_Multiboot2_ITag_BasicMemoryInfo_is_valid(
        &tag_basic_memory_info_invalid_size
    ));

    // Tag_BIOSBootDevice

    assert(KernAux_Multiboot2_ITag_BIOSBootDevice_is_valid(
        &tag_bios_boot_device_valid
    ));

    assert(!KernAux_Multiboot2_ITag_BIOSBootDevice_is_valid(
        &tag_bios_boot_device_invalid_type
    ));

    assert(!KernAux_Multiboot2_ITag_BIOSBootDevice_is_valid(
        &tag_bios_boot_device_invalid_size
    ));

    // Tag_MemoryMap

    assert(KernAux_Multiboot2_ITag_MemoryMap_is_valid(
        &tag_memory_map_with_empty_data_valid
    ));

    assert(KernAux_Multiboot2_ITag_MemoryMap_is_valid(
        &tag_memory_map_with_some_small_data_items_valid.tag
    ));

    assert(KernAux_Multiboot2_ITag_MemoryMap_is_valid(
        &tag_memory_map_with_some_large_data_items_valid.tag
    ));

    assert(!KernAux_Multiboot2_ITag_MemoryMap_is_valid(
        &tag_memory_map_invalid_type
    ));

    assert(!KernAux_Multiboot2_ITag_MemoryMap_is_valid(
        &tag_memory_map_with_some_large_data_items_invalid_size.tag
    ));

    assert(!KernAux_Multiboot2_ITag_MemoryMap_is_valid(
        &tag_memory_map_with_empty_data_invalid_entry_size_zero
    ));

    assert(!KernAux_Multiboot2_ITag_MemoryMap_is_valid(
        &tag_memory_map_with_empty_data_invalid_entry_size_not_mul8
    ));

    assert(!KernAux_Multiboot2_ITag_MemoryMap_is_valid(
        &tag_memory_map_with_some_small_data_items_invalid_entry_size_not_mul8
            .tag
    ));

    assert(!KernAux_Multiboot2_ITag_MemoryMap_is_valid(
        &tag_memory_map_with_some_large_data_items_invalid_entry_size_not_mul8
            .tag
    ));

    // Tag_VBEInfo

    assert(KernAux_Multiboot2_ITag_VBEInfo_is_valid(
        &tag_vbe_info_valid
    ));

    assert(!KernAux_Multiboot2_ITag_VBEInfo_is_valid(
        &tag_vbe_info_invalid_type
    ));

    assert(!KernAux_Multiboot2_ITag_VBEInfo_is_valid(
        &tag_vbe_info_invalid_size
    ));

    // Tag_ELFSymbols


    assert(KernAux_Multiboot2_ITag_ELFSymbols_is_valid(
        &tag_elf_symbols_with_zero_entsize_valid
    ));
}
