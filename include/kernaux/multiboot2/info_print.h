#ifndef KERNAUX_INCLUDED_MULTIBOOT2_INFO_PRINT
#define KERNAUX_INCLUDED_MULTIBOOT2_INFO_PRINT

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/multiboot2.h>

void KernAux_Multiboot2_Info_print(
    const struct KernAux_Multiboot2_Info *multiboot2_info,
    KernAux_Display display
);

void KernAux_Multiboot2_ITagBase_print(
    const struct KernAux_Multiboot2_ITagBase *tag_base,
    KernAux_Display display
);

void KernAux_Multiboot2_ITag_None_print(
    const struct KernAux_Multiboot2_ITag_None *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_ITag_BootCmdLine_print(
    const struct KernAux_Multiboot2_ITag_BootCmdLine *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_ITag_BootLoaderName_print(
    const struct KernAux_Multiboot2_ITag_BootLoaderName *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_ITag_Module_print(
    const struct KernAux_Multiboot2_ITag_Module *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_ITag_BasicMemoryInfo_print(
    const struct KernAux_Multiboot2_ITag_BasicMemoryInfo *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_ITag_BIOSBootDevice_print(
    const struct KernAux_Multiboot2_ITag_BIOSBootDevice *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_ITag_MemoryMap_print(
    const struct KernAux_Multiboot2_ITag_MemoryMap *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_ITag_VBEInfo_print(
    const struct KernAux_Multiboot2_ITag_VBEInfo *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_ITag_FramebufferInfo_print(
    const struct KernAux_Multiboot2_ITag_FramebufferInfo *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_ITag_ELFSymbols_print(
    const struct KernAux_Multiboot2_ITag_ELFSymbols *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_ITag_APMTable_print(
    const struct KernAux_Multiboot2_ITag_APMTable *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_ITag_EFI32bitSystemTablePtr_print(
    const struct KernAux_Multiboot2_ITag_EFI32bitSystemTablePtr *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_ITag_EFI64bitSystemTablePtr_print(
    const struct KernAux_Multiboot2_ITag_EFI64bitSystemTablePtr *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_ITag_SMBIOSTables_print(
    const struct KernAux_Multiboot2_ITag_SMBIOSTables *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_ITag_ACPIOldRSDP_print(
    const struct KernAux_Multiboot2_ITag_ACPIOldRSDP *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_ITag_ACPINewRSDP_print(
    const struct KernAux_Multiboot2_ITag_ACPINewRSDP *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_ITag_NetworkingInfo_print(
    const struct KernAux_Multiboot2_ITag_NetworkingInfo *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_ITag_EFIMemoryMap_print(
    const struct KernAux_Multiboot2_ITag_EFIMemoryMap *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_ITag_EFIBootServicesNotTerminated_print(
    const struct KernAux_Multiboot2_ITag_EFIBootServicesNotTerminated *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_ITag_EFI32bitImageHandlePtr_print(
    const struct KernAux_Multiboot2_ITag_EFI32bitImageHandlePtr *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_ITag_EFI64bitImageHandlePtr_print(
    const struct KernAux_Multiboot2_ITag_EFI64bitImageHandlePtr *tag,
    KernAux_Display display
);

void KernAux_Multiboot2_ITag_ImageLoadBasePhysAddr_print(
    const struct KernAux_Multiboot2_ITag_ImageLoadBasePhysAddr *tag,
    KernAux_Display display
);

#ifdef __cplusplus
}
#endif

#endif
