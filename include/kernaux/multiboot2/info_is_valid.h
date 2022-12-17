#ifndef KERNAUX_INCLUDED_MULTIBOOT2_INFO_IS_VALID
#define KERNAUX_INCLUDED_MULTIBOOT2_INFO_IS_VALID

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/multiboot2.h>

bool KernAux_Multiboot2_Info_is_valid(
    const struct KernAux_Multiboot2_Info *multiboot2_info
);

bool KernAux_Multiboot2_ITagBase_is_valid(
    const struct KernAux_Multiboot2_ITagBase *tag_base
);

bool KernAux_Multiboot2_ITag_None_is_valid(
    const struct KernAux_Multiboot2_ITag_None *tag
);

bool KernAux_Multiboot2_ITag_BootCmdLine_is_valid(
    const struct KernAux_Multiboot2_ITag_BootCmdLine *tag
);

bool KernAux_Multiboot2_ITag_BootLoaderName_is_valid(
    const struct KernAux_Multiboot2_ITag_BootLoaderName *tag
);

bool KernAux_Multiboot2_ITag_Module_is_valid(
    const struct KernAux_Multiboot2_ITag_Module *tag
);

bool KernAux_Multiboot2_ITag_BasicMemoryInfo_is_valid(
    const struct KernAux_Multiboot2_ITag_BasicMemoryInfo *tag
);

bool KernAux_Multiboot2_ITag_BIOSBootDevice_is_valid(
    const struct KernAux_Multiboot2_ITag_BIOSBootDevice *tag
);

bool KernAux_Multiboot2_ITag_MemoryMap_is_valid(
    const struct KernAux_Multiboot2_ITag_MemoryMap *tag
);

bool KernAux_Multiboot2_ITag_VBEInfo_is_valid(
    const struct KernAux_Multiboot2_ITag_VBEInfo *tag
);

bool KernAux_Multiboot2_ITag_FramebufferInfo_is_valid(
    const struct KernAux_Multiboot2_ITag_FramebufferInfo *tag
);

bool KernAux_Multiboot2_ITag_ELFSymbols_is_valid(
    const struct KernAux_Multiboot2_ITag_ELFSymbols *tag
);

bool KernAux_Multiboot2_ITag_APMTable_is_valid(
    const struct KernAux_Multiboot2_ITag_APMTable *tag
);

bool KernAux_Multiboot2_ITag_EFI32bitSystemTablePtr_is_valid(
    const struct KernAux_Multiboot2_ITag_EFI32bitSystemTablePtr *tag
);

bool KernAux_Multiboot2_ITag_EFI64bitSystemTablePtr_is_valid(
    const struct KernAux_Multiboot2_ITag_EFI64bitSystemTablePtr *tag
);

bool KernAux_Multiboot2_ITag_SMBIOSTables_is_valid(
    const struct KernAux_Multiboot2_ITag_SMBIOSTables *tag
);

bool KernAux_Multiboot2_ITag_ACPIOldRSDP_is_valid(
    const struct KernAux_Multiboot2_ITag_ACPIOldRSDP *tag
);

bool KernAux_Multiboot2_ITag_ACPINewRSDP_is_valid(
    const struct KernAux_Multiboot2_ITag_ACPINewRSDP *tag
);

bool KernAux_Multiboot2_ITag_NetworkingInfo_is_valid(
    const struct KernAux_Multiboot2_ITag_NetworkingInfo *tag
);

bool KernAux_Multiboot2_ITag_EFIMemoryMap_is_valid(
    const struct KernAux_Multiboot2_ITag_EFIMemoryMap *tag
);

bool KernAux_Multiboot2_ITag_EFIBootServicesNotTerminated_is_valid(
    const struct KernAux_Multiboot2_ITag_EFIBootServicesNotTerminated *tag
);

bool KernAux_Multiboot2_ITag_EFI32bitImageHandlePtr_is_valid(
    const struct KernAux_Multiboot2_ITag_EFI32bitImageHandlePtr *tag
);

bool KernAux_Multiboot2_ITag_EFI64bitImageHandlePtr_is_valid(
    const struct KernAux_Multiboot2_ITag_EFI64bitImageHandlePtr *tag
);

bool KernAux_Multiboot2_ITag_ImageLoadBasePhysAddr_is_valid(
    const struct KernAux_Multiboot2_ITag_ImageLoadBasePhysAddr *tag
);

#ifdef __cplusplus
}
#endif

#endif
