#include <kernaux/multiboot2.h>

#include <assert.h>

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

int main()
{
    assert(KernAux_Multiboot2_Tag_None_is_valid(&tag_none_valid));
    assert(!KernAux_Multiboot2_Tag_None_is_valid(&tag_none_invalid_type));
    assert(!KernAux_Multiboot2_Tag_None_is_valid(&tag_none_invalid_size));

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

    return 0;
}
