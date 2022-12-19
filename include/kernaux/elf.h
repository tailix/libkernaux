#ifndef KERNAUX_INCLUDED_ELF
#define KERNAUX_INCLUDED_ELF

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>

#include <stdint.h>

#include <kernaux/macro/packing_start.run>

struct KernAux_ELF_Header {
    uint8_t magic_0x7f;
    uint8_t magic_E;
    uint8_t magic_L;
    uint8_t magic_F;
    uint8_t bitness;
    uint8_t endianness;
    uint8_t header_version;
    uint8_t os_abi;
    uint32_t unused1;
    uint32_t unused2;
    uint16_t obj_type;
    uint16_t isa;
    uint32_t elf_version;
    uint32_t entrypoint;
    uint32_t prog_table_pos;
    uint32_t sect_table_pos;
    uint32_t arch_flags;
    uint16_t header_size;
    uint16_t prog_entr_size;
    uint16_t prog_entr_num;
    uint16_t sect_entr_size;
    uint16_t sect_entr_num;
    uint16_t sect_names_idx;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_ELF_Header, 52);

struct KernAux_ELF_ProgramEntry {
    uint32_t type;
    uint32_t offset;
    uint32_t virt_addr;
    uint32_t phys_addr;
    uint32_t file_size;
    uint32_t mem_size;
    uint32_t flags;
    uint32_t align;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_ELF_ProgramEntry, 32);

struct KernAux_ELF_SectionEntry {
    uint32_t name;
    uint32_t type;
    uint32_t flags;
    uint32_t vaddr;
    uint32_t file_offset;
    uint32_t file_size;
    uint32_t link;
    uint32_t info;
    uint32_t alignment;
    uint32_t ent_size;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_ELF_SectionEntry, 40);

struct KernAux_ELF_RelocationEntry {
    uint32_t virt_addr;
    uint32_t info;
}
KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(KernAux_ELF_RelocationEntry, 8);

#include <kernaux/macro/packing_end.run>

#ifdef __cplusplus
}
#endif

#endif
