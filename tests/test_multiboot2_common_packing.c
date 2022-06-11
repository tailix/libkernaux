#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/multiboot2.h>

#include <assert.h>
#include <stdint.h>

#include "multiboot2_header_example2.h"
#include "multiboot2_info_example2.h"

// For flag tags that don't include any data
#define HEAD0(name)                                                         \
    do {                                                                    \
        assert(((uint8_t*)&multiboot2_header_example2.tag_##name) == head); \
        head += 8;                                                          \
    } while (0)

#define HEAD2(name, tag_or_data, align)                                     \
    do {                                                                    \
        assert(((uint8_t*)&multiboot2_header_example2.tag_##name) == head); \
        head += 8 + (tag_or_data) + (align);                                \
    } while (0)

#define HEAD3(name, tag, data, align)                                       \
    do {                                                                    \
        assert(((uint8_t*)&multiboot2_header_example2.tag_##name) == head); \
        head += 8 + (tag) + (data) + (align);                               \
    } while (0)

// For flag tags that don't include any data
#define INFO0(name)                                                       \
    do {                                                                  \
        assert(((uint8_t*)&multiboot2_info_example2.tag_##name) == info); \
        info += 8;                                                        \
    } while (0)

#define INFO2(name, tag_or_data, align)                                   \
    do {                                                                  \
        assert(((uint8_t*)&multiboot2_info_example2.tag_##name) == info); \
        info += 8 + (tag_or_data) + (align);                              \
    } while (0)

#define INFO3(name, tag, data, align)                                     \
    do {                                                                  \
        assert(((uint8_t*)&multiboot2_info_example2.tag_##name) == info); \
        info += 8 + (tag) + (data) + (align);                             \
    } while (0)

int main()
{
    const uint8_t *head = ((const uint8_t*)&multiboot2_header_example2) + 16;
    const uint8_t *info = ((const uint8_t*)&multiboot2_info_example2) + 8;

    //   (name,                             tag,  data,      align);
    HEAD2(info_req,                         /**/  4 * 22,    0    );
    HEAD2(addr,                             16,   /**/       0    );
    HEAD2(entry_addr,                       4,    /**/       4    );
    HEAD2(flags,                            4,    /**/       4    );
    HEAD2(framebuffer,                      12,   /**/       4    );
    HEAD0(module_align                      /**/  /**/       /**/ );
    HEAD0(efi_boot_services                 /**/  /**/       /**/ );
    HEAD2(efi_i386_entry_addr,              4,    /**/       4    );
    HEAD2(efi_amd64_entry_addr,             4,    /**/       4    );
    HEAD2(relocatable_header,               16,   /**/       0    );
    HEAD0(none                              /**/  /**/       /**/ );

    //   (name,                             tag,  data,      align);
    INFO2(boot_cmd_line,                    /**/  15,        1    );
    INFO2(boot_loader_name,                 /**/  22,        2    );
    INFO3(module1,                          8,    17,        7    );
    INFO3(module2,                          8,    17,        7    );
    INFO2(basic_memory_info,                8,    /**/       0    );
    INFO2(bios_boot_device,                 12,   /**/       4    );
    INFO3(memory_map,                       8,    160 - 16,  0    );
    INFO2(vbe_info,                         776,  /**/       0    );
    INFO3(framebuffer_info,                 23,   8,         1    );
    INFO3(elf_symbols,                      8,    420 - 16,  4    );
    INFO2(apm_table,                        20,   /**/       4    );
    INFO2(efi_32bit_system_table_ptr,       4,    /**/       4    );
    INFO2(efi_64bit_system_table_ptr,       8,    /**/       0    );
    INFO3(smbios_tables,                    8,    8,         0    );
    INFO2(acpi_old_rsdp,                    /**/  8,         0    );
    INFO2(acpi_new_rsdp,                    /**/  8,         0    );
    INFO2(networking_info,                  /**/  8,         0    );
    INFO3(efi_memory_map,                   8,    8,         0    );
    INFO0(efi_boot_services_not_terminated  /**/  /**/       /**/ );
    INFO2(efi_32bit_image_handle_ptr,       4,    /**/       4    );
    INFO2(efi_64bit_image_handle_ptr,       8,    /**/       0    );
    INFO2(image_load_base_phys_addr,        4,    /**/       4    );
    INFO0(none                              /**/  /**/       /**/ );

    return 0;
}
