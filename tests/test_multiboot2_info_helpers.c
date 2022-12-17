#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/macro.h>
#include <kernaux/multiboot2.h>

#include <assert.h>

#include "../fixtures/multiboot2_info_example1.h"
#include "../fixtures/multiboot2_info_example2.h"

#include <kernaux/macro/packing_start.run>

static const struct {
    struct KernAux_Multiboot2_Info multiboot2_info;
    struct KernAux_Multiboot2_ITag_None tag_none;
} KERNAUX_PACKED multiboot2_without_boot_cmd_line = {
    .multiboot2_info = {
        .total_size = sizeof(multiboot2_without_boot_cmd_line),
        .reserved = 0,
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_NONE,
            .size = sizeof(multiboot2_without_boot_cmd_line.tag_none),
        },
    },
};

static const struct {
    struct KernAux_Multiboot2_Info multiboot2_info;

    struct {
        struct KernAux_Multiboot2_ITag_BootCmdLine tag;
        char cmdline[14];
    } tag_boot_cmd_line;

    unsigned char _align1[2];

    struct KernAux_Multiboot2_ITag_None tag_none;
} KERNAUX_PACKED multiboot2_with_some_boot_cmd_line = {
    .multiboot2_info = {
        .total_size = sizeof(multiboot2_with_some_boot_cmd_line),
        .reserved = 0,
    },
    .tag_boot_cmd_line = {
        .tag = {
            .base = {
                .type = KERNAUX_MULTIBOOT2_ITAG_BOOT_CMD_LINE,
                .size = sizeof(
                    multiboot2_with_some_boot_cmd_line.tag_boot_cmd_line
                ),
            },
        },
        .cmdline = "Hello, World!\0",
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_NONE,
            .size = sizeof(multiboot2_with_some_boot_cmd_line.tag_none),
        },
    },
};

static const struct {
    struct KernAux_Multiboot2_Info multiboot2_info;

    struct {
        struct KernAux_Multiboot2_ITag_BootCmdLine tag;
        char cmdline[14];
    } tag_boot_cmd_line1;

    unsigned char _align1[2];

    struct {
        struct KernAux_Multiboot2_ITag_BootCmdLine tag;
        char cmdline[13];
    } tag_boot_cmd_line2;

    unsigned char _align2[3];

    struct KernAux_Multiboot2_ITag_None tag_none;
} KERNAUX_PACKED multiboot2_with_two_boot_cmd_lines = {
    .multiboot2_info = {
        .total_size = sizeof(multiboot2_with_two_boot_cmd_lines),
        .reserved = 0,
    },
    .tag_boot_cmd_line1 = {
        .tag = {
            .base = {
                .type = KERNAUX_MULTIBOOT2_ITAG_BOOT_CMD_LINE,
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
                .type = KERNAUX_MULTIBOOT2_ITAG_BOOT_CMD_LINE,
                .size = sizeof(
                    multiboot2_with_two_boot_cmd_lines.tag_boot_cmd_line2
                ),
            },
        },
        .cmdline = "Hello again!\0",
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_ITAG_NONE,
            .size = sizeof(multiboot2_with_two_boot_cmd_lines.tag_none),
        },
    },
};

#include <kernaux/macro/packing_end.run>

void test_main()
{
    assert(KernAux_Multiboot2_Info_is_valid(
        (struct KernAux_Multiboot2_Info*)multiboot2_info_example1
    ));

    assert(KernAux_Multiboot2_Info_is_valid(
        &multiboot2_info_example2.multiboot2_info
    ));

    assert(KernAux_Multiboot2_Info_is_valid(
        &multiboot2_without_boot_cmd_line.multiboot2_info
    ));

    assert(KernAux_Multiboot2_Info_is_valid(
        &multiboot2_with_some_boot_cmd_line.multiboot2_info
    ));

    assert(KernAux_Multiboot2_Info_is_valid(
        &multiboot2_with_two_boot_cmd_lines.multiboot2_info
    ));

    assert(
        KernAux_Multiboot2_Info_boot_cmd_line(
            &multiboot2_without_boot_cmd_line.multiboot2_info
        ) == 0
    );

    // KernAux_Multiboot2_Info_first_tag_with_type

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            (struct KernAux_Multiboot2_Info*)multiboot2_info_example1,
            KERNAUX_MULTIBOOT2_ITAG_EFI_32BIT_SYSTEM_TABLE_PTR
        ) == 0
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            (struct KernAux_Multiboot2_Info*)multiboot2_info_example1,
            KERNAUX_MULTIBOOT2_ITAG_EFI_64BIT_SYSTEM_TABLE_PTR
        ) == 0
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            (struct KernAux_Multiboot2_Info*)multiboot2_info_example1,
            KERNAUX_MULTIBOOT2_ITAG_SMBIOS_TABLES
        ) == 0
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            (struct KernAux_Multiboot2_Info*)multiboot2_info_example1,
            KERNAUX_MULTIBOOT2_ITAG_ACPI_NEW_RSDP
        ) == 0
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            (struct KernAux_Multiboot2_Info*)multiboot2_info_example1,
            KERNAUX_MULTIBOOT2_ITAG_NETWORKING_INFO
        ) == 0
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            (struct KernAux_Multiboot2_Info*)multiboot2_info_example1,
            KERNAUX_MULTIBOOT2_ITAG_EFI_MEMORY_MAP
        ) == 0
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            (struct KernAux_Multiboot2_Info*)multiboot2_info_example1,
            KERNAUX_MULTIBOOT2_ITAG_EFI_BOOT_SERVICES_NOT_TERMINATED
        ) == 0
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            (struct KernAux_Multiboot2_Info*)multiboot2_info_example1,
            KERNAUX_MULTIBOOT2_ITAG_EFI_32BIT_IMAGE_HANDLE_PTR
        ) == 0
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            (struct KernAux_Multiboot2_Info*)multiboot2_info_example1,
            KERNAUX_MULTIBOOT2_ITAG_EFI_64BIT_IMAGE_HANDLE_PTR
        ) == 0
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            &multiboot2_info_example2.multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_NONE
        ) == &multiboot2_info_example2.tag_none.base
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            &multiboot2_info_example2.multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_BOOT_CMD_LINE
        ) == &multiboot2_info_example2.tag_boot_cmd_line.tag.base
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            &multiboot2_info_example2.multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_BOOT_LOADER_NAME
        ) == &multiboot2_info_example2.tag_boot_loader_name.tag.base
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            &multiboot2_info_example2.multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_MODULE
        ) == &multiboot2_info_example2.tag_module1.tag.base
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            &multiboot2_info_example2.multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_BASIC_MEMORY_INFO
        ) == &multiboot2_info_example2.tag_basic_memory_info.base
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            &multiboot2_info_example2.multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_FRAMEBUFFER_INFO
        ) == &multiboot2_info_example2.tag_framebuffer_info.tag.base
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            &multiboot2_info_example2.multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_ELF_SYMBOLS
        ) == &multiboot2_info_example2.tag_elf_symbols.tag.base
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            &multiboot2_info_example2.multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_APM_TABLE
        ) == &multiboot2_info_example2.tag_apm_table.base
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            &multiboot2_info_example2.multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_EFI_32BIT_SYSTEM_TABLE_PTR
        ) == &multiboot2_info_example2.tag_efi_32bit_system_table_ptr.base
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            &multiboot2_info_example2.multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_EFI_64BIT_SYSTEM_TABLE_PTR
        ) == &multiboot2_info_example2.tag_efi_64bit_system_table_ptr.base
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            &multiboot2_info_example2.multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_SMBIOS_TABLES
        ) == &multiboot2_info_example2.tag_smbios_tables.tag.base
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            &multiboot2_info_example2.multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_ACPI_OLD_RSDP
        ) == &multiboot2_info_example2.tag_acpi_old_rsdp.tag.base
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            &multiboot2_info_example2.multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_ACPI_NEW_RSDP
        ) == &multiboot2_info_example2.tag_acpi_new_rsdp.tag.base
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            &multiboot2_info_example2.multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_NETWORKING_INFO
        ) == &multiboot2_info_example2.tag_networking_info.tag.base
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            &multiboot2_info_example2.multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_EFI_MEMORY_MAP
        ) == &multiboot2_info_example2.tag_efi_memory_map.tag.base
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            &multiboot2_info_example2.multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_EFI_BOOT_SERVICES_NOT_TERMINATED
        ) == &multiboot2_info_example2.tag_efi_boot_services_not_terminated.base
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            &multiboot2_info_example2.multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_EFI_32BIT_IMAGE_HANDLE_PTR
        ) == &multiboot2_info_example2.tag_efi_32bit_image_handle_ptr.base
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            &multiboot2_info_example2.multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_EFI_64BIT_IMAGE_HANDLE_PTR
        ) == &multiboot2_info_example2.tag_efi_64bit_image_handle_ptr.base
    );

    assert(
        KernAux_Multiboot2_Info_first_tag_with_type(
            &multiboot2_info_example2.multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_IMAGE_LOAD_BASE_PHYS_ADDR
        ) == &multiboot2_info_example2.tag_image_load_base_phys_addr.base
    );

    // KernAux_Multiboot2_Info_tag_with_type_after

    assert(
        KernAux_Multiboot2_Info_tag_with_type_after(
            &multiboot2_info_example2.multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_MODULE,
            KernAux_Multiboot2_Info_first_tag_with_type(
                &multiboot2_info_example2.multiboot2_info,
                KERNAUX_MULTIBOOT2_ITAG_MODULE
            ) - 1
        ) == (struct KernAux_Multiboot2_ITagBase*)
            &multiboot2_info_example2.tag_module1
    );

    assert(
        KernAux_Multiboot2_Info_tag_with_type_after(
            &multiboot2_info_example2.multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_MODULE,
            KernAux_Multiboot2_Info_first_tag_with_type(
                &multiboot2_info_example2.multiboot2_info,
                KERNAUX_MULTIBOOT2_ITAG_MODULE
            )
        ) == (struct KernAux_Multiboot2_ITagBase*)
            &multiboot2_info_example2.tag_module2
    );

    assert(
        KernAux_Multiboot2_Info_tag_with_type_after(
            &multiboot2_info_example2.multiboot2_info,
            KERNAUX_MULTIBOOT2_ITAG_MODULE,
            KernAux_Multiboot2_Info_tag_with_type_after(
                &multiboot2_info_example2.multiboot2_info,
                KERNAUX_MULTIBOOT2_ITAG_MODULE,
                KernAux_Multiboot2_Info_first_tag_with_type(
                    &multiboot2_info_example2.multiboot2_info,
                    KERNAUX_MULTIBOOT2_ITAG_MODULE
                )
            )
        ) == 0
    );

    // KernAux_Multiboot2_Info_boot_cmd_line

    assert(
        KernAux_Multiboot2_Info_boot_cmd_line(
            &multiboot2_with_some_boot_cmd_line.multiboot2_info
        ) == multiboot2_with_some_boot_cmd_line.tag_boot_cmd_line.cmdline
    );

    assert(
        KernAux_Multiboot2_Info_boot_cmd_line(
            &multiboot2_with_two_boot_cmd_lines.multiboot2_info
        ) == multiboot2_with_two_boot_cmd_lines.tag_boot_cmd_line1.cmdline
    );
}
