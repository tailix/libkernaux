#ifndef KERNAUX_INCLUDED_MULTIBOOT2_HEADER_MACRO
#define KERNAUX_INCLUDED_MULTIBOOT2_HEADER_MACRO

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>
#include <kernaux/multiboot2.h>

#define KERNAUX_MULTIBOOT2_HFIELDS_COMMON(name, type) \
    struct {                                          \
        struct KernAux_Multiboot2_HTag_##type tag;    \
    } KERNAUX_PACKED name;

#ifdef __cplusplus
}
#endif

#endif
