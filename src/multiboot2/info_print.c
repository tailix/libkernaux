#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/generic/display.h>
#include <kernaux/macro.h>
#include <kernaux/multiboot2.h>

#include <stddef.h>
#include <stdint.h>

#define PRINTLN(s) do { KernAux_Display_println(display, s); } while (0)
#define PRINTLNF(format, ...) \
    do { KernAux_Display_printlnf(display, format, __VA_ARGS__); } while (0)

#define HEADER(Type) do { \
    KERNAUX_ASSERT(tag);                                     \
    KERNAUX_ASSERT(display);                                 \
                                                             \
    if (!KernAux_Multiboot2_ITag_##Type##_is_valid(tag)) {   \
        PRINTLN("Multiboot 2 info tag // invalid!");         \
    }                                                        \
                                                             \
    KERNAUX_CAST_CONST(unsigned long, size, tag->base.size); \
                                                             \
    PRINTLN("Multiboot 2 info tag {");                       \
    PRINTLNF("  u32 type: %u (%s)",                          \
        tag->base.type,                                      \
        KernAux_Multiboot2_ITag_to_str(tag->base.type)       \
    );                                                       \
    PRINTLNF("  u32 size: %lu", size);                       \
} while (0)

#define FOOTER do { PRINTLN("}"); } while (0)

void KernAux_Multiboot2_Info_print(
    const struct KernAux_Multiboot2_Info *const multiboot2_info,
    const KernAux_Display display
) {
    KERNAUX_ASSERT(multiboot2_info);
    KERNAUX_ASSERT(display);

    KERNAUX_CAST_CONST(unsigned long, total_size, multiboot2_info->total_size);
    KERNAUX_CAST_CONST(unsigned long, reserved1,  multiboot2_info->reserved1);

    PRINTLN("Multiboot 2 info {");
    PRINTLNF("  u32 size: %lu", total_size);
    PRINTLNF("  u32 reserved1: %lu", reserved1);
    PRINTLN("}");

    const struct KernAux_Multiboot2_ITagBase *tag_base =
        (struct KernAux_Multiboot2_ITagBase*)
        KERNAUX_MULTIBOOT2_DATA(multiboot2_info);

    while (tag_base <
           (struct KernAux_Multiboot2_ITagBase*)
           ((uint8_t*)multiboot2_info + multiboot2_info->total_size))
    {
        if (!KernAux_Multiboot2_ITagBase_is_valid(tag_base)) return;
        KernAux_Multiboot2_ITagBase_print(tag_base, display);
        tag_base = KERNAUX_MULTIBOOT2_ITAG_NEXT(tag_base);
    }
}

void KernAux_Multiboot2_ITagBase_print(
    const struct KernAux_Multiboot2_ITagBase *const tag_base,
    const KernAux_Display display
) {
    KERNAUX_ASSERT(tag_base);
    KERNAUX_ASSERT(display);

    switch (tag_base->type) {
    case KERNAUX_MULTIBOOT2_ITAG_NONE:
        KernAux_Multiboot2_ITag_None_print(
            (struct KernAux_Multiboot2_ITag_None*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_BOOT_CMD_LINE:
        KernAux_Multiboot2_ITag_BootCmdLine_print(
            (struct KernAux_Multiboot2_ITag_BootCmdLine*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_BOOT_LOADER_NAME:
        KernAux_Multiboot2_ITag_BootLoaderName_print(
            (struct KernAux_Multiboot2_ITag_BootLoaderName*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_MODULE:
        KernAux_Multiboot2_ITag_Module_print(
            (struct KernAux_Multiboot2_ITag_Module*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_BASIC_MEMORY_INFO:
        KernAux_Multiboot2_ITag_BasicMemoryInfo_print(
            (struct KernAux_Multiboot2_ITag_BasicMemoryInfo*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_BIOS_BOOT_DEVICE:
        KernAux_Multiboot2_ITag_BIOSBootDevice_print(
            (struct KernAux_Multiboot2_ITag_BIOSBootDevice*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_MEMORY_MAP:
        KernAux_Multiboot2_ITag_MemoryMap_print(
            (struct KernAux_Multiboot2_ITag_MemoryMap*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_VBE_INFO:
        KernAux_Multiboot2_ITag_VBEInfo_print(
            (struct KernAux_Multiboot2_ITag_VBEInfo*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_FRAMEBUFFER_INFO:
        KernAux_Multiboot2_ITag_FramebufferInfo_print(
            (struct KernAux_Multiboot2_ITag_FramebufferInfo*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_ELF_SYMBOLS:
        KernAux_Multiboot2_ITag_ELFSymbols_print(
            (struct KernAux_Multiboot2_ITag_ELFSymbols*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_APM_TABLE:
        KernAux_Multiboot2_ITag_APMTable_print(
            (struct KernAux_Multiboot2_ITag_APMTable*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_EFI_32BIT_SYSTEM_TABLE_PTR:
        KernAux_Multiboot2_ITag_EFI32bitSystemTablePtr_print(
            (struct KernAux_Multiboot2_ITag_EFI32bitSystemTablePtr*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_EFI_64BIT_SYSTEM_TABLE_PTR:
        KernAux_Multiboot2_ITag_EFI64bitSystemTablePtr_print(
            (struct KernAux_Multiboot2_ITag_EFI64bitSystemTablePtr*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_SMBIOS_TABLES:
        KernAux_Multiboot2_ITag_SMBIOSTables_print(
            (struct KernAux_Multiboot2_ITag_SMBIOSTables*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_ACPI_OLD_RSDP:
        KernAux_Multiboot2_ITag_ACPIOldRSDP_print(
            (struct KernAux_Multiboot2_ITag_ACPIOldRSDP*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_ACPI_NEW_RSDP:
        KernAux_Multiboot2_ITag_ACPINewRSDP_print(
            (struct KernAux_Multiboot2_ITag_ACPINewRSDP*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_NETWORKING_INFO:
        KernAux_Multiboot2_ITag_NetworkingInfo_print(
            (struct KernAux_Multiboot2_ITag_NetworkingInfo*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_EFI_MEMORY_MAP:
        KernAux_Multiboot2_ITag_EFIMemoryMap_print(
            (struct KernAux_Multiboot2_ITag_EFIMemoryMap*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_EFI_BOOT_SERVICES_NOT_TERMINATED:
        KernAux_Multiboot2_ITag_EFIBootServicesNotTerminated_print(
            (struct KernAux_Multiboot2_ITag_EFIBootServicesNotTerminated*)
            tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_EFI_32BIT_IMAGE_HANDLE_PTR:
        KernAux_Multiboot2_ITag_EFI32bitImageHandlePtr_print(
            (struct KernAux_Multiboot2_ITag_EFI32bitImageHandlePtr*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_EFI_64BIT_IMAGE_HANDLE_PTR:
        KernAux_Multiboot2_ITag_EFI64bitImageHandlePtr_print(
            (struct KernAux_Multiboot2_ITag_EFI64bitImageHandlePtr*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_IMAGE_LOAD_BASE_PHYS_ADDR:
        KernAux_Multiboot2_ITag_ImageLoadBasePhysAddr_print(
            (struct KernAux_Multiboot2_ITag_ImageLoadBasePhysAddr*)tag_base,
            display
        );
        break;
    }
}

void KernAux_Multiboot2_ITag_None_print(
    const struct KernAux_Multiboot2_ITag_None *const tag,
    const KernAux_Display display
) {
    HEADER(None);
    FOOTER;
}

void KernAux_Multiboot2_ITag_BootCmdLine_print(
    const struct KernAux_Multiboot2_ITag_BootCmdLine *const tag,
    const KernAux_Display display
) {
    HEADER(BootCmdLine);

    // Print data:
    PRINTLNF("  char cmdline[]: \"%s\"", KERNAUX_MULTIBOOT2_DATA(tag));

    FOOTER;
}

void KernAux_Multiboot2_ITag_BootLoaderName_print(
    const struct KernAux_Multiboot2_ITag_BootLoaderName *const tag,
    const KernAux_Display display
) {
    HEADER(BootLoaderName);

    // Print data:
    PRINTLNF("  char name[]: \"%s\"", KERNAUX_MULTIBOOT2_DATA(tag));

    FOOTER;
}

void KernAux_Multiboot2_ITag_Module_print(
    const struct KernAux_Multiboot2_ITag_Module *const tag,
    const KernAux_Display display
) {
    HEADER(Module);

    KERNAUX_CAST_CONST(unsigned long, mod_start, tag->mod_start);
    KERNAUX_CAST_CONST(unsigned long, mod_end,   tag->mod_end);

    PRINTLNF("  u32 start: %lu", mod_start);
    PRINTLNF("  u32 end: %lu", mod_end);

    // Print data:
    PRINTLNF("  char cmdline[]: \"%s\"", KERNAUX_MULTIBOOT2_DATA(tag));

    FOOTER;
}

void KernAux_Multiboot2_ITag_BasicMemoryInfo_print(
    const struct KernAux_Multiboot2_ITag_BasicMemoryInfo *const tag,
    const KernAux_Display display
) {
    HEADER(BasicMemoryInfo);

    KERNAUX_CAST_CONST(unsigned long, mem_lower, tag->mem_lower);
    KERNAUX_CAST_CONST(unsigned long, mem_upper, tag->mem_upper);

    PRINTLNF("  u32 mem_lower: %lu", mem_lower);
    PRINTLNF("  u32 mem_upper: %lu", mem_upper);

    FOOTER;
}

void KernAux_Multiboot2_ITag_BIOSBootDevice_print(
    const struct KernAux_Multiboot2_ITag_BIOSBootDevice *const tag,
    const KernAux_Display display
) {
    HEADER(BIOSBootDevice);

    KERNAUX_CAST_CONST(unsigned long, bios_dev,      tag->bios_dev);
    KERNAUX_CAST_CONST(unsigned long, partition,     tag->partition);
    KERNAUX_CAST_CONST(unsigned long, sub_partition, tag->sub_partition);

    PRINTLNF("  u32 bios_dev: %lu", bios_dev);
    PRINTLNF("  u32 partition: %lu", partition);
    PRINTLNF("  u32 sub_partition: %lu", sub_partition);

    FOOTER;
}

void KernAux_Multiboot2_ITag_MemoryMap_print(
    const struct KernAux_Multiboot2_ITag_MemoryMap *const tag,
    const KernAux_Display display
) {
    HEADER(MemoryMap);

    KERNAUX_CAST_CONST(unsigned long, entry_size,    tag->entry_size);
    KERNAUX_CAST_CONST(unsigned long, entry_version, tag->entry_version);

    PRINTLNF("  u32 entry_size: %lu",    entry_size);
    PRINTLNF("  u32 entry_version: %lu", entry_version);
    PRINTLN("  entries:");

    // Print data:

    const struct KernAux_Multiboot2_ITag_MemoryMap_EntryBase *const entries =
        (struct KernAux_Multiboot2_ITag_MemoryMap_EntryBase*)
        KERNAUX_MULTIBOOT2_DATA((struct KernAux_Multiboot2_ITag_MemoryMap*)tag);

    for (
        size_t index = 0;
        index < (tag->base.size - sizeof(*tag)) / tag->entry_size;
        ++index
    ) {
        KERNAUX_CAST_CONST(unsigned long long, base_addr, entries[index].base_addr);
        KERNAUX_CAST_CONST(unsigned long long, length,    entries[index].length);
        KERNAUX_CAST_CONST(unsigned long,      type,      entries[index].type);
        KERNAUX_CAST_CONST(unsigned long,      reserved1, entries[index].reserved1);

        PRINTLNF("    entry %zu", index);
        PRINTLNF("      u64 base_addr: %llu", base_addr);
        PRINTLNF("      u64 length: %llu",    length);
        PRINTLNF("      u32 type: %lu",       type);
        PRINTLNF("      u32 reserved1: %lu",  reserved1);
    }

    FOOTER;
}

void KernAux_Multiboot2_ITag_VBEInfo_print(
    const struct KernAux_Multiboot2_ITag_VBEInfo *const tag,
    const KernAux_Display display
) {
    HEADER(VBEInfo);

    KERNAUX_CAST_CONST(unsigned long, mode,          tag->vbe_mode);
    KERNAUX_CAST_CONST(unsigned long, interface_seg, tag->vbe_interface_seg);
    KERNAUX_CAST_CONST(unsigned long, interface_off, tag->vbe_interface_off);
    KERNAUX_CAST_CONST(unsigned long, interface_len, tag->vbe_interface_len);

    PRINTLNF("  u16 vbe_mode: %lu",          mode);
    PRINTLNF("  u16 vbe_interface_seg: %lu", interface_seg);
    PRINTLNF("  u16 vbe_interface_off: %lu", interface_off);
    PRINTLNF("  u16 vbe_interface_len: %lu", interface_len);

    FOOTER;
}

void KernAux_Multiboot2_ITag_FramebufferInfo_print(
    const struct KernAux_Multiboot2_ITag_FramebufferInfo *const tag,
    const KernAux_Display display
) {
    HEADER(FramebufferInfo);

    KERNAUX_CAST_CONST(unsigned long long, addr,      tag->framebuffer_addr);
    KERNAUX_CAST_CONST(unsigned long,      pitch,     tag->framebuffer_pitch);
    KERNAUX_CAST_CONST(unsigned long,      width,     tag->framebuffer_width);
    KERNAUX_CAST_CONST(unsigned long,      height,    tag->framebuffer_height);
    KERNAUX_CAST_CONST(unsigned long,      bpp,       tag->framebuffer_bpp);
    KERNAUX_CAST_CONST(unsigned long,      type,      tag->framebuffer_type);
    KERNAUX_CAST_CONST(unsigned long,      reserved1, tag->reserved1);

    PRINTLNF("  u64 framebuffer_addr: %llu",  addr);
    PRINTLNF("  u32 framebuffer_pitch: %lu",  pitch);
    PRINTLNF("  u32 framebuffer_width: %lu",  width);
    PRINTLNF("  u32 framebuffer_height: %lu", height);
    PRINTLNF("  u8 framebuffer_bpp: %lu",    bpp);
    PRINTLNF("  u8 framebuffer_type: %lu",   type);
    PRINTLNF("  u8 reserved1: %lu",          reserved1);

    // TODO: Print data?

    FOOTER;
}

void KernAux_Multiboot2_ITag_ELFSymbols_print(
    const struct KernAux_Multiboot2_ITag_ELFSymbols *const tag,
    const KernAux_Display display
) {
    HEADER(ELFSymbols);

    KERNAUX_CAST_CONST(unsigned long, num,       tag->num);
    KERNAUX_CAST_CONST(unsigned long, ent_size,  tag->ent_size);
    KERNAUX_CAST_CONST(unsigned long, shndx,     tag->shndx);
    KERNAUX_CAST_CONST(unsigned long, reserved1, tag->reserved1);

    PRINTLNF("  u16 num: %lu",       num);
    PRINTLNF("  u16 entsize: %lu",   ent_size);
    PRINTLNF("  u16 shndx: %lu",     shndx);
    PRINTLNF("  u16 reserved1: %lu", reserved1);

    // TODO: Print data?

    FOOTER;
}

void KernAux_Multiboot2_ITag_APMTable_print(
    const struct KernAux_Multiboot2_ITag_APMTable *const tag,
    const KernAux_Display display
) {
    HEADER(APMTable);

    KERNAUX_CAST_CONST(unsigned long, version,     tag->version);
    KERNAUX_CAST_CONST(unsigned long, cseg,        tag->cseg);
    KERNAUX_CAST_CONST(unsigned long, offset,      tag->offset);
    KERNAUX_CAST_CONST(unsigned long, cseg_16,     tag->cseg_16);
    KERNAUX_CAST_CONST(unsigned long, dseg,        tag->dseg);
    KERNAUX_CAST_CONST(unsigned long, flags,       tag->flags);
    KERNAUX_CAST_CONST(unsigned long, cseg_len,    tag->cseg_len);
    KERNAUX_CAST_CONST(unsigned long, cseg_16_len, tag->cseg_16_len);
    KERNAUX_CAST_CONST(unsigned long, dseg_len,    tag->dseg_len);

    PRINTLNF("  u16 version: %lu",     version);
    PRINTLNF("  u16 cseg: %lu",        cseg);
    PRINTLNF("  u32 offset: %lu",      offset);
    PRINTLNF("  u16 cseg_16: %lu",     cseg_16);
    PRINTLNF("  u16 dseg: %lu",        dseg);
    PRINTLNF("  u16 flags: %lu",       flags);
    PRINTLNF("  u16 cseg_len: %lu",    cseg_len);
    PRINTLNF("  u16 cseg_16_len: %lu", cseg_16_len);
    PRINTLNF("  u16 dseg_len: %lu",    dseg_len);

    FOOTER;
}

void KernAux_Multiboot2_ITag_EFI32bitSystemTablePtr_print(
    const struct KernAux_Multiboot2_ITag_EFI32bitSystemTablePtr *const tag,
    const KernAux_Display display
) {
    HEADER(EFI32bitSystemTablePtr);

    KERNAUX_CAST_CONST(unsigned long, pointer, tag->pointer);

    PRINTLNF("  u32 pointer: %lu", pointer);

    FOOTER;
}

void KernAux_Multiboot2_ITag_EFI64bitSystemTablePtr_print(
    const struct KernAux_Multiboot2_ITag_EFI64bitSystemTablePtr *const tag,
    const KernAux_Display display
) {
    HEADER(EFI64bitSystemTablePtr);

    KERNAUX_CAST_CONST(unsigned long long, pointer, tag->pointer);

    PRINTLNF("  u64 pointer: %llu", pointer);

    FOOTER;
}

void KernAux_Multiboot2_ITag_SMBIOSTables_print(
    const struct KernAux_Multiboot2_ITag_SMBIOSTables *const tag,
    const KernAux_Display display
) {
    HEADER(SMBIOSTables);

    KERNAUX_CAST_CONST(unsigned long, major,     tag->major);
    KERNAUX_CAST_CONST(unsigned long, minor,     tag->minor);
    KERNAUX_CAST_CONST(unsigned long, reserved0, tag->reserved1[0]);
    KERNAUX_CAST_CONST(unsigned long, reserved1, tag->reserved1[1]);
    KERNAUX_CAST_CONST(unsigned long, reserved2, tag->reserved1[2]);
    KERNAUX_CAST_CONST(unsigned long, reserved3, tag->reserved1[3]);
    KERNAUX_CAST_CONST(unsigned long, reserved4, tag->reserved1[4]);
    KERNAUX_CAST_CONST(unsigned long, reserved5, tag->reserved1[5]);

    PRINTLNF("  u8 major: %lu", major);
    PRINTLNF("  u8 minor: %lu", minor);
    PRINTLNF("  u8 reserved1[6]: {%lu, %lu, %lu, %lu, %lu, %lu}",
        reserved0, reserved1, reserved2,
        reserved3, reserved4, reserved5
    );

    // TODO: Print data?

    FOOTER;
}

void KernAux_Multiboot2_ITag_ACPIOldRSDP_print(
    const struct KernAux_Multiboot2_ITag_ACPIOldRSDP *const tag,
    const KernAux_Display display
) {
    HEADER(ACPIOldRSDP);

    // TODO: Print data?

    FOOTER;
}

void KernAux_Multiboot2_ITag_ACPINewRSDP_print(
    const struct KernAux_Multiboot2_ITag_ACPINewRSDP *const tag,
    const KernAux_Display display
) {
    HEADER(ACPINewRSDP);

    // TODO: Print data?

    FOOTER;
}

void KernAux_Multiboot2_ITag_NetworkingInfo_print(
    const struct KernAux_Multiboot2_ITag_NetworkingInfo *const tag,
    const KernAux_Display display
) {
    HEADER(NetworkingInfo);

    // TODO: Print data?

    FOOTER;
}

void KernAux_Multiboot2_ITag_EFIMemoryMap_print(
    const struct KernAux_Multiboot2_ITag_EFIMemoryMap *const tag,
    const KernAux_Display display
) {
    HEADER(EFIMemoryMap);

    KERNAUX_CAST_CONST(unsigned long, descr_size,    tag->descriptor_size);
    KERNAUX_CAST_CONST(unsigned long, descr_version, tag->descriptor_version);

    PRINTLNF("  u32 descriptor_size: %lu",    descr_size);
    PRINTLNF("  u32 descriptor_version: %lu", descr_version);

    // TODO: Print data?

    FOOTER;
}

void KernAux_Multiboot2_ITag_EFIBootServicesNotTerminated_print(
    const struct KernAux_Multiboot2_ITag_EFIBootServicesNotTerminated *const tag,
    const KernAux_Display display
) {
    HEADER(EFIBootServicesNotTerminated);

    FOOTER;
}

void KernAux_Multiboot2_ITag_EFI32bitImageHandlePtr_print(
    const struct KernAux_Multiboot2_ITag_EFI32bitImageHandlePtr *const tag,
    const KernAux_Display display
) {
    HEADER(EFI32bitImageHandlePtr);

    KERNAUX_CAST_CONST(unsigned long, pointer, tag->pointer);

    PRINTLNF("  u32 pointer: %lu", pointer);

    FOOTER;
}

void KernAux_Multiboot2_ITag_EFI64bitImageHandlePtr_print(
    const struct KernAux_Multiboot2_ITag_EFI64bitImageHandlePtr *const tag,
    const KernAux_Display display
) {
    HEADER(EFI64bitImageHandlePtr);

    KERNAUX_CAST_CONST(unsigned long long, pointer, tag->pointer);

    PRINTLNF("  u64 pointer: %llu", pointer);

    FOOTER;
}

void KernAux_Multiboot2_ITag_ImageLoadBasePhysAddr_print(
    const struct KernAux_Multiboot2_ITag_ImageLoadBasePhysAddr *const tag,
    const KernAux_Display display
) {
    HEADER(ImageLoadBasePhysAddr);

    KERNAUX_CAST_CONST(unsigned long, load_base_addr, tag->load_base_addr);

    PRINTLNF("  u32 load_base_addr: %lu", load_base_addr);

    FOOTER;
}
