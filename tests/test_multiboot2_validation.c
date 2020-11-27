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

/********
 * main *
 ********/

int main()
{
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

    return 0;
}
