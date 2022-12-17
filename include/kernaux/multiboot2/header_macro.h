#ifndef KERNAUX_INCLUDED_MULTIBOOT2_HEADER_MACRO
#define KERNAUX_INCLUDED_MULTIBOOT2_HEADER_MACRO

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>
#include <kernaux/multiboot2.h>

#include <stdint.h>

#define KERNAUX_MULTIBOOT2_HEADER_CHECKSUM(arch, total_size) \
    ((uint32_t)(-(                                           \
        ((uint32_t)KERNAUX_MULTIBOOT2_HEADER_MAGIC) +        \
        ((uint32_t)(arch)) +                                 \
        ((uint32_t)(total_size))                             \
    )))

#define KERNAUX_MULTIBOOT2_HFIELDS_COMMON(name, type) \
    struct {                                          \
        struct KernAux_Multiboot2_HTag_##type tag;    \
    } KERNAUX_PACKED name;

#define KERNAUX_MULTIBOOT2_HFIELDS_INFO_REQ_ODD(     \
    name, mbi_tag_types_count, align_name            \
)                                                    \
    struct {                                         \
        struct KernAux_Multiboot2_HTag_InfoReq tag;  \
        uint32_t mbi_tag_types[mbi_tag_types_count]; \
    } KERNAUX_PACKED name;                           \
    uint8_t align_name[4];

#define KERNAUX_MULTIBOOT2_HFIELDS_INFO_REQ_EVEN(    \
    name, mbi_tag_types_count                        \
)                                                    \
    struct {                                         \
        struct KernAux_Multiboot2_HTag_InfoReq tag;  \
        uint32_t mbi_tag_types[mbi_tag_types_count]; \
    } KERNAUX_PACKED name;

#ifdef __cplusplus
}
#endif

#endif
