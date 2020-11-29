#include <kernaux/multiboot2.h>

#include <assert.h>

static const struct {
    struct KernAux_Multiboot2 multiboot2;
    struct KernAux_Multiboot2_Tag_None tag_none;
} multiboot2_without_boot_cmd_line = {
    .multiboot2 = {
        .total_size = sizeof(multiboot2_without_boot_cmd_line),
        .reserved1 = 0,
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_NONE,
            .size = sizeof(multiboot2_without_boot_cmd_line.tag_none),
        },
    },
};

static const struct {
    struct KernAux_Multiboot2 multiboot2;

    struct {
        struct KernAux_Multiboot2_Tag_BootCmdLine tag;
        char cmdline[14];
    } tag_boot_cmd_line;

    unsigned char _align1[2];

    struct KernAux_Multiboot2_Tag_None tag_none;
} multiboot2_with_some_boot_cmd_line = {
    .multiboot2 = {
        .total_size = sizeof(multiboot2_with_some_boot_cmd_line),
        .reserved1 = 0,
    },
    .tag_boot_cmd_line = {
        .tag = {
            .base = {
                .type = KERNAUX_MULTIBOOT2_TAGTYPE_BOOT_CMD_LINE,
                .size = sizeof(
                    multiboot2_with_some_boot_cmd_line.tag_boot_cmd_line
                ),
            },
        },
        .cmdline = "Hello, World!\0",
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_NONE,
            .size = sizeof(multiboot2_with_some_boot_cmd_line.tag_none),
        },
    },
};

static const struct {
    struct KernAux_Multiboot2 multiboot2;

    struct {
        struct KernAux_Multiboot2_Tag_BootCmdLine tag;
        char cmdline[14];
    } tag_boot_cmd_line1;

    unsigned char _align1[2];

    struct {
        struct KernAux_Multiboot2_Tag_BootCmdLine tag;
        char cmdline[13];
    } tag_boot_cmd_line2;

    unsigned char _align2[3];

    struct KernAux_Multiboot2_Tag_None tag_none;
} multiboot2_with_two_boot_cmd_lines = {
    .multiboot2 = {
        .total_size = sizeof(multiboot2_with_two_boot_cmd_lines),
        .reserved1 = 0,
    },
    .tag_boot_cmd_line1 = {
        .tag = {
            .base = {
                .type = KERNAUX_MULTIBOOT2_TAGTYPE_BOOT_CMD_LINE,
                .size = sizeof(
                    multiboot2_with_two_boot_cmd_lines.tag_boot_cmd_line1
                ),
            },
        },
        .cmdline = "Hello, World!\0",
    },
    .tag_boot_cmd_line2 = {
        .tag = {
            .base = {
                .type = KERNAUX_MULTIBOOT2_TAGTYPE_BOOT_CMD_LINE,
                .size = sizeof(
                    multiboot2_with_two_boot_cmd_lines.tag_boot_cmd_line2
                ),
            },
        },
        .cmdline = "Hello again!\0",
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_TAGTYPE_NONE,
            .size = sizeof(multiboot2_with_two_boot_cmd_lines.tag_none),
        },
    },
};

int main()
{
    assert(KernAux_Multiboot2_is_valid(
        &multiboot2_without_boot_cmd_line.multiboot2
    ));

    assert(KernAux_Multiboot2_is_valid(
        &multiboot2_with_some_boot_cmd_line.multiboot2
    ));

    assert(KernAux_Multiboot2_is_valid(
        &multiboot2_with_two_boot_cmd_lines.multiboot2
    ));

    assert(
        KernAux_Multiboot2_boot_cmd_line(
            &multiboot2_without_boot_cmd_line.multiboot2
        ) == 0
    );

    assert(
        KernAux_Multiboot2_boot_cmd_line(
            &multiboot2_with_some_boot_cmd_line.multiboot2
        ) == multiboot2_with_some_boot_cmd_line.tag_boot_cmd_line.cmdline
    );

    assert(
        KernAux_Multiboot2_boot_cmd_line(
            &multiboot2_with_two_boot_cmd_lines.multiboot2
        ) == multiboot2_with_two_boot_cmd_lines.tag_boot_cmd_line1.cmdline
    );

    return 0;
}
