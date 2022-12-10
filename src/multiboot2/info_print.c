#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/macro.h>
#include <kernaux/multiboot2.h>

#include <stddef.h>
#include <stdint.h>

// TODO: create macro for this
#define INT_IF(a, b) (sizeof(int) == sizeof(long) ? (a) : (b))

#define PRINTLN(s) KernAux_Display_println(display, s)
#define PRINTLNF(format, ...) \
    KernAux_Display_printlnf(display, format, __VA_ARGS__)

void KernAux_Multiboot2_Info_print(
    const struct KernAux_Multiboot2_Info *const multiboot2_info,
    const KernAux_Display display
) {
    KERNAUX_ASSERT(multiboot2_info);
    KERNAUX_ASSERT(display);

    unsigned long total_size, reserved1;
    KERNAUX_SAFECAST_TO_UL(total_size, multiboot2_info->total_size);
    KERNAUX_SAFECAST_TO_UL(reserved1,  multiboot2_info->reserved1);

    PRINTLN("Multiboot 2 info");
    PRINTLNF("  size: %lu", total_size);
    PRINTLNF("  reserved1: %lu", reserved1);

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

    if (!KernAux_Multiboot2_ITagBase_is_valid(tag_base)) return;

    PRINTLN("Multiboot 2 info tag");

    PRINTLNF("  type: %u (%s)",
        tag_base->type,
        KernAux_Multiboot2_ITag_to_str(tag_base->type)
    );

    unsigned long size;
    KERNAUX_SAFECAST_TO_UL(size, tag_base->size);
    PRINTLNF("  size: %lu", size);

    switch (tag_base->type) {
    case KERNAUX_MULTIBOOT2_ITAG_NONE:
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
        {
            const struct KernAux_Multiboot2_ITag_Module *const tag_module =
                (struct KernAux_Multiboot2_ITag_Module*)tag_base;

            unsigned long mod_start, mod_end;
            KERNAUX_SAFECAST_TO_UL(mod_start, tag_module->mod_start);
            KERNAUX_SAFECAST_TO_UL(mod_end,   tag_module->mod_end);

            PRINTLNF("  start: %lu", mod_start);
            PRINTLNF("  end: %lu", mod_end);
            PRINTLNF("  cmdline: %s", KERNAUX_MULTIBOOT2_DATA(tag_module));
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_BASIC_MEMORY_INFO:
        {
            const struct KernAux_Multiboot2_ITag_BasicMemoryInfo *const tag_bmi =
                (struct KernAux_Multiboot2_ITag_BasicMemoryInfo*)tag_base;

            unsigned long mem_lower, mem_upper;
            KERNAUX_SAFECAST_TO_UL(mem_lower, tag_bmi->mem_lower);
            KERNAUX_SAFECAST_TO_UL(mem_upper, tag_bmi->mem_upper);

            PRINTLNF("  mem lower: %lu", mem_lower);
            PRINTLNF("  mem upper: %lu", mem_upper);
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_BIOS_BOOT_DEVICE:
        {
            const struct KernAux_Multiboot2_ITag_BIOSBootDevice *const tag_bbd =
                (struct KernAux_Multiboot2_ITag_BIOSBootDevice*)tag_base;

            unsigned long bios_dev, partition, sub_partition;
            KERNAUX_SAFECAST_TO_UL(bios_dev,      tag_bbd->bios_dev);
            KERNAUX_SAFECAST_TO_UL(partition,     tag_bbd->partition);
            KERNAUX_SAFECAST_TO_UL(sub_partition, tag_bbd->sub_partition);

            PRINTLNF("  bios dev: %lu", bios_dev);
            PRINTLNF("  partition: %lu", partition);
            PRINTLNF("  sub_partition: %lu", sub_partition);
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_MEMORY_MAP:
        KernAux_Multiboot2_ITag_MemoryMap_print(
            (struct KernAux_Multiboot2_ITag_MemoryMap*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_VBE_INFO:
        {
            const struct KernAux_Multiboot2_ITag_VBEInfo *const tag_vbe =
                (struct KernAux_Multiboot2_ITag_VBEInfo*)tag_base;

            unsigned long vbe_mode, vbe_interface_seg, vbe_interface_off, vbe_interface_len;
            KERNAUX_SAFECAST_TO_UL(vbe_mode,          tag_vbe->vbe_mode);
            KERNAUX_SAFECAST_TO_UL(vbe_interface_seg, tag_vbe->vbe_interface_seg);
            KERNAUX_SAFECAST_TO_UL(vbe_interface_off, tag_vbe->vbe_interface_off);
            KERNAUX_SAFECAST_TO_UL(vbe_interface_len, tag_vbe->vbe_interface_len);

            PRINTLNF("  VBE mode: %lu",          vbe_mode);
            PRINTLNF("  VBE interface seg: %lu", vbe_interface_seg);
            PRINTLNF("  VBE interface off: %lu", vbe_interface_off);
            PRINTLNF("  VBE interface len: %lu", vbe_interface_len);
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_FRAMEBUFFER_INFO:
        {
            const struct KernAux_Multiboot2_ITag_FramebufferInfo *const tag_fb =
                (struct KernAux_Multiboot2_ITag_FramebufferInfo*)tag_base;

            unsigned long long framebuffer_addr;
            unsigned long framebuffer_pitch, framebuffer_width,
                          framebuffer_height, framebuffer_bpp,
                          framebuffer_type, reserved1;
            KERNAUX_SAFECAST_TO_ULL(framebuffer_addr,   tag_fb->framebuffer_addr);
            KERNAUX_SAFECAST_TO_UL (framebuffer_pitch,  tag_fb->framebuffer_pitch);
            KERNAUX_SAFECAST_TO_UL (framebuffer_width,  tag_fb->framebuffer_width);
            KERNAUX_SAFECAST_TO_UL (framebuffer_height, tag_fb->framebuffer_height);
            KERNAUX_SAFECAST_TO_UL (framebuffer_bpp,    tag_fb->framebuffer_bpp);
            KERNAUX_SAFECAST_TO_UL (framebuffer_type,   tag_fb->framebuffer_type);
            KERNAUX_SAFECAST_TO_UL (reserved1,          tag_fb->reserved1);

            PRINTLNF("  framebuffer addr: %llu",  framebuffer_addr);
            PRINTLNF("  framebuffer pitch: %lu",  framebuffer_pitch);
            PRINTLNF("  framebuffer width: %lu",  framebuffer_width);
            PRINTLNF("  framebuffer height: %lu", framebuffer_height);
            PRINTLNF("  framebuffer bpp: %lu",    framebuffer_bpp);
            PRINTLNF("  framebuffer type: %lu",   framebuffer_type);
            PRINTLNF("  reserved1: %lu",          reserved1);
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_ELF_SYMBOLS:
        KernAux_Multiboot2_ITag_ELFSymbols_print(
            (struct KernAux_Multiboot2_ITag_ELFSymbols*)tag_base,
            display
        );
        break;
    case KERNAUX_MULTIBOOT2_ITAG_APM_TABLE:
        {
            const struct KernAux_Multiboot2_ITag_APMTable *const tag_apm =
                (struct KernAux_Multiboot2_ITag_APMTable*)tag_base;

            unsigned long version, cseg, offset, cseg_16, dseg, flags, cseg_len,
                          cseg_16_len, dseg_len;
            KERNAUX_SAFECAST_TO_UL(version,     tag_apm->version);
            KERNAUX_SAFECAST_TO_UL(cseg,        tag_apm->cseg);
            KERNAUX_SAFECAST_TO_UL(offset,      tag_apm->offset);
            KERNAUX_SAFECAST_TO_UL(cseg_16,     tag_apm->cseg_16);
            KERNAUX_SAFECAST_TO_UL(dseg,        tag_apm->dseg);
            KERNAUX_SAFECAST_TO_UL(flags,       tag_apm->flags);
            KERNAUX_SAFECAST_TO_UL(cseg_len,    tag_apm->cseg_len);
            KERNAUX_SAFECAST_TO_UL(cseg_16_len, tag_apm->cseg_16_len);
            KERNAUX_SAFECAST_TO_UL(dseg_len,    tag_apm->dseg_len);

            PRINTLNF("  version: %lu",     version);
            PRINTLNF("  cseg: %lu",        cseg);
            PRINTLNF("  offset: %lu",      offset);
            PRINTLNF("  cseg 16: %lu",     cseg_16);
            PRINTLNF("  dseg: %lu",        dseg);
            PRINTLNF("  flags: %lu",       flags);
            PRINTLNF("  cseg len: %lu",    cseg_len);
            PRINTLNF("  cseg 16 len: %lu", cseg_16_len);
            PRINTLNF("  dseg len: %lu",    dseg_len);
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_EFI_32BIT_SYSTEM_TABLE_PTR:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_EFI_64BIT_SYSTEM_TABLE_PTR:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_SMBIOS_TABLES:
        {
            const struct KernAux_Multiboot2_ITag_SMBIOSTables *const tag_smbios =
                (struct KernAux_Multiboot2_ITag_SMBIOSTables*)tag_base;

            unsigned long major, minor,
                          reserved0, reserved1, reserved2,
                          reserved3, reserved4, reserved5;
            KERNAUX_SAFECAST_TO_UL(major,     tag_smbios->major);
            KERNAUX_SAFECAST_TO_UL(minor,     tag_smbios->minor);
            KERNAUX_SAFECAST_TO_UL(reserved0, tag_smbios->reserved1[0]);
            KERNAUX_SAFECAST_TO_UL(reserved1, tag_smbios->reserved1[1]);
            KERNAUX_SAFECAST_TO_UL(reserved2, tag_smbios->reserved1[2]);
            KERNAUX_SAFECAST_TO_UL(reserved3, tag_smbios->reserved1[3]);
            KERNAUX_SAFECAST_TO_UL(reserved4, tag_smbios->reserved1[4]);
            KERNAUX_SAFECAST_TO_UL(reserved5, tag_smbios->reserved1[5]);

            PRINTLNF("  major: %lu", major);
            PRINTLNF("  minor: %lu", minor);

            PRINTLNF(
                "  reserved1: {%lu, %lu, %lu, %lu, %lu, %lu}",
                reserved0, reserved1, reserved2,
                reserved3, reserved4, reserved5
            );
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_ACPI_OLD_RSDP:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_ACPI_NEW_RSDP:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_NETWORKING_INFO:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_EFI_MEMORY_MAP:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_EFI_BOOT_SERVICES_NOT_TERMINATED:
        break;
    case KERNAUX_MULTIBOOT2_ITAG_EFI_32BIT_IMAGE_HANDLE_PTR:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_EFI_64BIT_IMAGE_HANDLE_PTR:
        {
            // TODO: print
        }
        break;
    case KERNAUX_MULTIBOOT2_ITAG_IMAGE_LOAD_BASE_PHYS_ADDR:
        {
            unsigned long load_base_addr;
            KERNAUX_SAFECAST_TO_UL(
                load_base_addr, 
                ((struct KernAux_Multiboot2_ITag_ImageLoadBasePhysAddr*)
                    tag_base)->load_base_addr
            );
            PRINTLNF("  load base addr: %lu", load_base_addr);
        }
        break;
    }
}

void KernAux_Multiboot2_ITag_BootCmdLine_print(
    const struct KernAux_Multiboot2_ITag_BootCmdLine *const tag,
    const KernAux_Display display
) {
    KERNAUX_ASSERT(tag);
    KERNAUX_ASSERT(display);

    if (!KernAux_Multiboot2_ITag_BootCmdLine_is_valid(tag)) {
        PRINTLN("  invalid!");
        return;
    }

    PRINTLNF("  cmdline: %s", KERNAUX_MULTIBOOT2_DATA(tag));
}

void KernAux_Multiboot2_ITag_BootLoaderName_print(
    const struct KernAux_Multiboot2_ITag_BootLoaderName *const tag,
    const KernAux_Display display
) {
    KERNAUX_ASSERT(tag);
    KERNAUX_ASSERT(display);

    if (!KernAux_Multiboot2_ITag_BootLoaderName_is_valid(tag)) {
        PRINTLN("  invalid!");
        return;
    }

    PRINTLNF("  name: %s", KERNAUX_MULTIBOOT2_DATA(tag));
}

void KernAux_Multiboot2_ITag_MemoryMap_print(
    const struct KernAux_Multiboot2_ITag_MemoryMap *const tag,
    const KernAux_Display display
) {
    KERNAUX_ASSERT(tag);
    KERNAUX_ASSERT(display);

    if (!KernAux_Multiboot2_ITag_MemoryMap_is_valid(tag)) {
        PRINTLN("  invalid!");
        return;
    }

    unsigned long entry_size, entry_version;
    KERNAUX_SAFECAST_TO_UL(entry_size,    tag->entry_size);
    KERNAUX_SAFECAST_TO_UL(entry_version, tag->entry_version);

    PRINTLNF("  entry size: %lu",    entry_size);
    PRINTLNF("  entry version: %lu", entry_version);
    PRINTLN("  entries:");

    const struct KernAux_Multiboot2_ITag_MemoryMap_EntryBase *const entries =
        (struct KernAux_Multiboot2_ITag_MemoryMap_EntryBase*)
        KERNAUX_MULTIBOOT2_DATA((struct KernAux_Multiboot2_ITag_MemoryMap*)tag);

    for (
        size_t index = 0;
        index < (tag->base.size - sizeof(*tag)) / tag->entry_size;
        ++index
    ) {
        unsigned long long base_addr, length;
        unsigned long type, reserved1;
        KERNAUX_SAFECAST_TO_ULL(base_addr, entries[index].base_addr);
        KERNAUX_SAFECAST_TO_ULL(length,    entries[index].length);
        KERNAUX_SAFECAST_TO_ULL(type,      entries[index].type);
        KERNAUX_SAFECAST_TO_ULL(reserved1, entries[index].reserved1);

        PRINTLNF("    entry %zu", index);
        PRINTLNF("      base addr: %llu", base_addr);
        PRINTLNF("      length: %llu",    length);
        PRINTLNF("      type: %lu",       type);
        PRINTLNF("      reserved1: %lu",  reserved1);
    }
}

void KernAux_Multiboot2_ITag_ELFSymbols_print(
    const struct KernAux_Multiboot2_ITag_ELFSymbols *const tag,
    const KernAux_Display display
) {
    KERNAUX_ASSERT(tag);
    KERNAUX_ASSERT(display);

    if (!KernAux_Multiboot2_ITag_ELFSymbols_is_valid(tag)) {
        PRINTLN("  invalid!");
        return;
    }

    unsigned long num, ent_size, shndx, reserved1;
    KERNAUX_SAFECAST_TO_UL(num,       tag->num);
    KERNAUX_SAFECAST_TO_UL(ent_size,  tag->ent_size);
    KERNAUX_SAFECAST_TO_UL(shndx,     tag->shndx);
    KERNAUX_SAFECAST_TO_UL(reserved1, tag->reserved1);

    PRINTLNF("  num: %lu",       num);
    PRINTLNF("  entsize: %lu",   ent_size);
    PRINTLNF("  shndx: %lu",     shndx);
    PRINTLNF("  reserved1: %lu", reserved1);

    // TODO: implement this
}
