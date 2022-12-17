#ifndef KERNAUX_INCLUDED_MULTIBOOT2_HEADER_IS_VALID
#define KERNAUX_INCLUDED_MULTIBOOT2_HEADER_IS_VALID

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/multiboot2.h>

bool KernAux_Multiboot2_Header_is_valid(
    const struct KernAux_Multiboot2_Header *multiboot2_header
);

bool KernAux_Multiboot2_HTagBase_is_valid(
    const struct KernAux_Multiboot2_HTagBase *tag_base
);

bool KernAux_Multiboot2_HTag_None_is_valid(
    const struct KernAux_Multiboot2_HTag_None *tag
);

bool KernAux_Multiboot2_HTag_InfoReq_is_valid(
    const struct KernAux_Multiboot2_HTag_InfoReq *tag
);

bool KernAux_Multiboot2_HTag_Addr_is_valid(
    const struct KernAux_Multiboot2_HTag_Addr *tag
);

bool KernAux_Multiboot2_HTag_EntryAddr_is_valid(
    const struct KernAux_Multiboot2_HTag_EntryAddr *tag
);

bool KernAux_Multiboot2_HTag_Flags_is_valid(
    const struct KernAux_Multiboot2_HTag_Flags *tag
);

bool KernAux_Multiboot2_HTag_Framebuffer_is_valid(
    const struct KernAux_Multiboot2_HTag_Framebuffer *tag
);

bool KernAux_Multiboot2_HTag_ModuleAlign_is_valid(
    const struct KernAux_Multiboot2_HTag_ModuleAlign *tag
);

bool KernAux_Multiboot2_HTag_EFIBootServices_is_valid(
    const struct KernAux_Multiboot2_HTag_EFIBootServices *tag
);

bool KernAux_Multiboot2_HTag_EFII386EntryAddr_is_valid(
    const struct KernAux_Multiboot2_HTag_EFII386EntryAddr *tag
);

bool KernAux_Multiboot2_HTag_EFIAmd64EntryAddr_is_valid(
    const struct KernAux_Multiboot2_HTag_EFIAmd64EntryAddr *tag
);

bool KernAux_Multiboot2_HTag_RelocatableHeader_is_valid(
    const struct KernAux_Multiboot2_HTag_RelocatableHeader *tag
);

#ifdef __cplusplus
}
#endif

#endif
