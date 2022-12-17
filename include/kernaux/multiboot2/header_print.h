#ifndef KERNAUX_INCLUDED_MULTIBOOT2_HEADER_PRINT
#define KERNAUX_INCLUDED_MULTIBOOT2_HEADER_PRINT

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/multiboot2.h>

void KernAux_Multiboot2_Header_print(
    const struct KernAux_Multiboot2_Header *multiboot2_header,
    KernAux_Display display
);

void KernAux_Multiboot2_HTagBase_print(
    const struct KernAux_Multiboot2_HTagBase *tag_base,
    KernAux_Display display
);

void KernAux_Multiboot2_HTag_None_print(
    const struct KernAux_Multiboot2_HTag_None *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_HTag_InfoReq_print(
    const struct KernAux_Multiboot2_HTag_InfoReq *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_HTag_Addr_print(
    const struct KernAux_Multiboot2_HTag_Addr *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_HTag_EntryAddr_print(
    const struct KernAux_Multiboot2_HTag_EntryAddr *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_HTag_Flags_print(
    const struct KernAux_Multiboot2_HTag_Flags *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_HTag_Framebuffer_print(
    const struct KernAux_Multiboot2_HTag_Framebuffer *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_HTag_ModuleAlign_print(
    const struct KernAux_Multiboot2_HTag_ModuleAlign *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_HTag_EFIBootServices_print(
    const struct KernAux_Multiboot2_HTag_EFIBootServices *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_HTag_EFII386EntryAddr_print(
    const struct KernAux_Multiboot2_HTag_EFII386EntryAddr *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_HTag_EFIAmd64EntryAddr_print(
    const struct KernAux_Multiboot2_HTag_EFIAmd64EntryAddr *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_HTag_RelocatableHeader_print(
    const struct KernAux_Multiboot2_HTag_RelocatableHeader *tag,
    KernAux_Display display
);

#ifdef __cplusplus
}
#endif

#endif
