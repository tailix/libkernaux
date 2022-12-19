#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/multiboot2.h>

#include <assert.h>
#include <stdint.h>

#include "../fixtures/multiboot2_header_example2.h"
#include "../fixtures/multiboot2_info_example2.h"

#define HEAD_SIZEOF1(type, inst, size)                                       \
    do {                                                                     \
        assert(sizeof(struct KernAux_Multiboot2_HTag_##type)     == (size)); \
        assert(sizeof(multiboot2_header_example2.tag_##inst)     == (size)); \
    } while (0)

#define HEAD_SIZEOF2(type, inst, size1, size2)                                          \
    do {                                                                                \
        assert(sizeof(struct KernAux_Multiboot2_HTag_##type)     == (size1));           \
        assert(sizeof(multiboot2_header_example2.tag_##inst.tag) == (size1));           \
        assert(sizeof(multiboot2_header_example2.tag_##inst)     == (size1) + (size2)); \
    } while (0)

#define INFO_SIZEOF1(type, inst, size)                                     \
    do {                                                                   \
        assert(sizeof(struct KernAux_Multiboot2_ITag_##type)   == (size)); \
        assert(sizeof(multiboot2_info_example2.tag_##inst)     == (size)); \
    } while (0)

#define INFO_SIZEOF2(type, inst, size1, size2)                                        \
    do {                                                                              \
        assert(sizeof(struct KernAux_Multiboot2_ITag_##type)   == (size1));           \
        assert(sizeof(multiboot2_info_example2.tag_##inst.tag) == (size1));           \
        assert(sizeof(multiboot2_info_example2.tag_##inst)     == (size1) + (size2)); \
    } while (0)

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

void test_main()
{
    assert(sizeof(struct KernAux_Multiboot2_Header) == 16);
    assert(sizeof(struct KernAux_Multiboot2_Info)   == 8);

    assert(sizeof(multiboot2_header_example2.multiboot2_header) == 16);
    assert(sizeof(multiboot2_info_example2.multiboot2_info)     == 8);

    assert(sizeof(struct KernAux_Multiboot2_HTagBase) == 8);
    assert(sizeof(struct KernAux_Multiboot2_ITagBase) == 8);

    HEAD_SIZEOF1(None,                         none,                             8           );
    HEAD_SIZEOF2(InfoReq,                      info_req,                         8,  4 * 22  );
    HEAD_SIZEOF1(Addr,                         addr,                             24          );
    HEAD_SIZEOF1(EntryAddr,                    entry_addr,                       12          );
    HEAD_SIZEOF1(Flags,                        flags,                            12          );
    HEAD_SIZEOF1(Framebuffer,                  framebuffer,                      20          );
    HEAD_SIZEOF1(ModuleAlign,                  module_align,                     8           );
    HEAD_SIZEOF1(EFIBootServices,              efi_boot_services,                8           );
    HEAD_SIZEOF1(EFII386EntryAddr,             efi_i386_entry_addr,              12          );
    HEAD_SIZEOF1(EFIAmd64EntryAddr,            efi_amd64_entry_addr,             12          );
    HEAD_SIZEOF1(RelocatableHeader,            relocatable_header,               24          );

    INFO_SIZEOF1(None,                         none,                             8           );
    INFO_SIZEOF2(BootCmdLine,                  boot_cmd_line,                    8,  15      );
    INFO_SIZEOF2(BootLoaderName,               boot_loader_name,                 8,  22      );
    INFO_SIZEOF2(Module,                       module1,                          16, 17      );
    INFO_SIZEOF2(Module,                       module2,                          16, 17      );
    INFO_SIZEOF1(BasicMemoryInfo,              basic_memory_info,                16          );
    INFO_SIZEOF1(BIOSBootDevice,               bios_boot_device,                 20          );
    INFO_SIZEOF2(MemoryMap,                    memory_map,                       16, 160 - 16);
    INFO_SIZEOF1(VBEInfo,                      vbe_info,                         784         );
    INFO_SIZEOF2(FramebufferInfo,              framebuffer_info,                 32, 8       );
    INFO_SIZEOF2(ELFSymbols,                   elf_symbols,                      20, 420 - 20);
    INFO_SIZEOF1(APMTable,                     apm_table,                        28          );
    INFO_SIZEOF1(EFI32bitSystemTablePtr,       efi_32bit_system_table_ptr,       12          );
    INFO_SIZEOF1(EFI64bitSystemTablePtr,       efi_64bit_system_table_ptr,       16          );
    INFO_SIZEOF2(SMBIOSTables,                 smbios_tables,                    16, 8       );
    INFO_SIZEOF2(ACPIOldRSDP,                  acpi_old_rsdp,                    8,  8       );
    INFO_SIZEOF2(ACPINewRSDP,                  acpi_new_rsdp,                    8,  8       );
    INFO_SIZEOF2(NetworkingInfo,               networking_info,                  8,  8       );
    INFO_SIZEOF2(EFIMemoryMap,                 efi_memory_map,                   16, 8       );
    INFO_SIZEOF1(EFIBootServicesNotTerminated, efi_boot_services_not_terminated, 8           );
    INFO_SIZEOF1(EFI32bitImageHandlePtr,       efi_32bit_image_handle_ptr,       12          );
    INFO_SIZEOF1(EFI64bitImageHandlePtr,       efi_64bit_image_handle_ptr,       16          );
    INFO_SIZEOF1(ImageLoadBasePhysAddr,        image_load_base_phys_addr,        12          );

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
}
