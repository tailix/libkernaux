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

#ifdef __cplusplus
}
#endif

#endif
