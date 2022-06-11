#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/multiboot2.h>

#include <assert.h>
#include <stdint.h>

#include "multiboot2_header_example2.h"

#include <stdio.h>

// For flag tags that don't include any data
#define TEST0(name)                                                        \
    do {                                                                   \
        assert(((uint8_t*)&multiboot2_header_example2.tag_##name) == ptr); \
        ptr += 8;                                                          \
    } while (0)

#define TEST2(name, tag_or_data, align)                                    \
    do {                                                                   \
        assert(((uint8_t*)&multiboot2_header_example2.tag_##name) == ptr); \
        ptr += 8 + (tag_or_data) + (align);                                \
    } while (0)

#define TEST3(name, tag, data, align)                                      \
    do {                                                                   \
        assert(((uint8_t*)&multiboot2_header_example2.tag_##name) == ptr); \
        ptr += 8 + (tag) + (data) + (align);                               \
    } while (0)

int main()
{
    const uint8_t *ptr = ((const uint8_t*)&multiboot2_header_example2) + 16;

    //   (name,                             tag,  data,      align);
    TEST2(info_req,                         /**/  4 * 22,    0    );
    TEST2(addr,                             16,   /**/       0    );
    TEST2(entry_addr,                       4,    /**/       4    );
    TEST2(flags,                            4,    /**/       4    );
    TEST2(framebuffer,                      12,   /**/       4    );
    TEST0(module_align                      /**/  /**/       /**/ );
    TEST0(efi_boot_services                 /**/  /**/       /**/ );
    TEST2(efi_i386_entry_addr,              4,    /**/       4    );
    TEST2(efi_amd64_entry_addr,             4,    /**/       4    );
    TEST2(relocatable_header,               16,   /**/       0    );
    TEST0(none                              /**/  /**/       /**/ );

    return 0;
}
