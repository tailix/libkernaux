#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/multiboot2.h>

#include <stddef.h>
#include <stdint.h>

const char *KernAux_Multiboot2_Header_Arch_to_str(const uint32_t arch)
{
    switch (arch) {
    case KERNAUX_MULTIBOOT2_HEADER_ARCH_I386:
        return "i386";
    case KERNAUX_MULTIBOOT2_HEADER_ARCH_MIPS32:
        return "MIPS32";
    default:
        return NULL;
    }
}

const char *KernAux_Multiboot2_HTag_to_str(const uint16_t tag_type)
{
    switch (tag_type) {
    case KERNAUX_MULTIBOOT2_HTAG_NONE:
        return "none";
    case KERNAUX_MULTIBOOT2_HTAG_INFO_REQ:
        return "information request";
    case KERNAUX_MULTIBOOT2_HTAG_ADDR:
        return "address";
    case KERNAUX_MULTIBOOT2_HTAG_ENTRY_ADDR:
        return "entry address";
    case KERNAUX_MULTIBOOT2_HTAG_FLAGS:
        return "flags";
    case KERNAUX_MULTIBOOT2_HTAG_FRAMEBUFFER:
        return "framebuffer";
    case KERNAUX_MULTIBOOT2_HTAG_MODULE_ALIGN:
        return "module alignment";
    case KERNAUX_MULTIBOOT2_HTAG_EFI_BOOT_SERVICES:
        return "EFI boot services";
    case KERNAUX_MULTIBOOT2_HTAG_EFI_I386_ENTRY_ADDR:
        return "EFI i386 entry address";
    case KERNAUX_MULTIBOOT2_HTAG_EFI_AMD64_ENTRY_ADDR:
        return "EFI amd64 entry address";
    case KERNAUX_MULTIBOOT2_HTAG_RELOCATABLE_HEADER:
        return "relocatable header";
    default:
        return NULL;
    }
}

const char*
KernAux_Multiboot2_HTag_RelocatableHeader_Preference_to_str(uint32_t pref)
{
    switch (pref) {
    case KERNAUX_MULTIBOOT2_HTAG_RELOCATABLE_HEADER_PREFERENCE_NONE:
        return "none";
    case KERNAUX_MULTIBOOT2_HTAG_RELOCATABLE_HEADER_PREFERENCE_LOWEST:
        return "lowest";
    case KERNAUX_MULTIBOOT2_HTAG_RELOCATABLE_HEADER_PREFERENCE_HIGHEST:
        return "highest";
    default:
        return NULL;
    }
}
