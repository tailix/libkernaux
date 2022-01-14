static const struct {
    struct KernAux_Multiboot2_Header multiboot2_header;

    struct {
        struct KernAux_Multiboot2_HTag_InfoReq tag;
        enum KernAux_Multiboot2_ITag mbi_tag_types[22];
    } tag_info_req;

    struct KernAux_Multiboot2_HTag_None tag_none;
} multiboot2_header_example2 = {
    .multiboot2_header = {
        .magic = KERNAUX_MULTIBOOT2_MAGIC,
        .arch = KERNAUX_MULTIBOOT2_ARCH_I386,
        .total_size = sizeof(multiboot2_header_example2),
        .checksum = KERNAUX_MULTIBOOT2_CHECKSUM(
            KERNAUX_MULTIBOOT2_ARCH_I386,
            sizeof(multiboot2_header_example2)
        ),
    },
    .tag_info_req = {
        .tag = {
            .base = {
                .type = KERNAUX_MULTIBOOT2_HTAG_INFO_REQ,
                .flags = 0,
                .size = sizeof(multiboot2_header_example2.tag_info_req),
            },
        },
        .mbi_tag_types = {
            KERNAUX_MULTIBOOT2_ITAG_NONE,
            KERNAUX_MULTIBOOT2_ITAG_BOOT_CMD_LINE,
            KERNAUX_MULTIBOOT2_ITAG_BOOT_LOADER_NAME,
            KERNAUX_MULTIBOOT2_ITAG_MODULE,
            KERNAUX_MULTIBOOT2_ITAG_BASIC_MEMORY_INFO,
            KERNAUX_MULTIBOOT2_ITAG_BIOS_BOOT_DEVICE,
            KERNAUX_MULTIBOOT2_ITAG_MEMORY_MAP,
            KERNAUX_MULTIBOOT2_ITAG_VBE_INFO,
            KERNAUX_MULTIBOOT2_ITAG_FRAMEBUFFER_INFO,
            KERNAUX_MULTIBOOT2_ITAG_ELF_SYMBOLS,
            KERNAUX_MULTIBOOT2_ITAG_APM_TABLE,
            KERNAUX_MULTIBOOT2_ITAG_EFI_32BIT_SYSTEM_TABLE_PTR,
            KERNAUX_MULTIBOOT2_ITAG_EFI_64BIT_SYSTEM_TABLE_PTR,
            KERNAUX_MULTIBOOT2_ITAG_SMBIOS_TABLES,
            KERNAUX_MULTIBOOT2_ITAG_ACPI_OLD_RSDP,
            KERNAUX_MULTIBOOT2_ITAG_ACPI_NEW_RSDP,
            KERNAUX_MULTIBOOT2_ITAG_NETWORKING_INFO,
            KERNAUX_MULTIBOOT2_ITAG_EFI_MEMORY_MAP,
            KERNAUX_MULTIBOOT2_ITAG_EFI_BOOT_SERVICES_NOT_TERMINATED,
            KERNAUX_MULTIBOOT2_ITAG_EFI_32BIT_IMAGE_HANDLE_PTR,
            KERNAUX_MULTIBOOT2_ITAG_EFI_64BIT_IMAGE_HANDLE_PTR,
            KERNAUX_MULTIBOOT2_ITAG_IMAGE_LOAD_BASE_PHYS_ADDR,
        },
    },
    .tag_none = {
        .base = {
            .type = KERNAUX_MULTIBOOT2_HTAG_NONE,
            .flags = 0,
            .size = sizeof(multiboot2_header_example2.tag_none),
        },
    },
};
