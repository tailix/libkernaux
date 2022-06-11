#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/multiboot2.h>

#include <assert.h>
#include <stdint.h>

#include "multiboot2_info_example2.h"

#include <stdio.h>

// For flag tags that don't include any data
#define TEST0(name)                                                      \
    do {                                                                 \
        assert(((uint8_t*)&multiboot2_info_example2.tag_##name) == ptr); \
        ptr += 8;                                                        \
    } while (0)

#define TEST2(name, tag_or_data, align)                                  \
    do {                                                                 \
        assert(((uint8_t*)&multiboot2_info_example2.tag_##name) == ptr); \
        ptr += 8 + (tag_or_data) + (align);                              \
    } while (0)

#define TEST3(name, tag, data, align)                                    \
    do {                                                                 \
        assert(((uint8_t*)&multiboot2_info_example2.tag_##name) == ptr); \
        ptr += 8 + (tag) + (data) + (align);                             \
    } while (0)

int main()
{
    const uint8_t *ptr = ((const uint8_t*)&multiboot2_info_example2) + 8;

    //   (name,                             tag,  data,      align);
    TEST2(boot_cmd_line,                    /**/  15,        1    );
    TEST2(boot_loader_name,                 /**/  22,        2    );
    TEST3(module1,                          8,    17,        7    );
    TEST3(module2,                          8,    17,        7    );
    TEST2(basic_memory_info,                8,    /**/       0    );
    TEST2(bios_boot_device,                 12,   /**/       4    );
    TEST3(memory_map,                       8,    160 - 16,  0    );
    TEST2(vbe_info,                         776,  /**/       0    );
    TEST3(framebuffer_info,                 23,   8,         1    );
    TEST3(elf_symbols,                      8,    420 - 16,  4    );
    TEST2(apm_table,                        20,   /**/       4    );
    TEST2(efi_32bit_system_table_ptr,       4,    /**/       4    );
    TEST2(efi_64bit_system_table_ptr,       8,    /**/       0    );
    TEST3(smbios_tables,                    8,    8,         0    );
    TEST2(acpi_old_rsdp,                    /**/  8,         0    );
    TEST2(acpi_new_rsdp,                    /**/  8,         0    );
    TEST2(networking_info,                  /**/  8,         0    );
    TEST3(efi_memory_map,                   8,    8,         0    );
    TEST0(efi_boot_services_not_terminated  /**/  /**/       /**/ );
    TEST2(efi_32bit_image_handle_ptr,       4,    /**/       4    );
    TEST2(efi_64bit_image_handle_ptr,       8,    /**/       0    );
    TEST2(image_load_base_phys_addr,        4,    /**/       4    );
    TEST0(none                              /**/  /**/       /**/ );

    return 0;
}
