#ifndef KERNAUX_INCLUDED_ELF
#define KERNAUX_INCLUDED_ELF 1

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct KernAux_ELF_Header {
    unsigned char  magic_0x7F     : 8;
    unsigned char  magic_E        : 8;
    unsigned char  magic_L        : 8;
    unsigned char  magic_F        : 8;
    unsigned char  bitness        : 8;
    unsigned char  endianness     : 8;
    unsigned char  header_version : 8;
    unsigned char  os_abi         : 8;
    unsigned long  unused1        : 32;
    unsigned long  unused2        : 32;
    unsigned short obj_type       : 16;
    unsigned short isa            : 16;
    unsigned long  elf_version    : 32;
    unsigned long  entrypoint     : 32;
    unsigned long  prog_table_pos : 32;
    unsigned long  sect_table_pos : 32;
    unsigned long  arch_flags     : 32;
    unsigned short header_size    : 16;
    unsigned short prog_entr_size : 16;
    unsigned short prog_entr_num  : 16;
    unsigned short sect_entr_size : 16;
    unsigned short sect_entr_num  : 16;
    unsigned short sect_names_idx : 16;
}
__attribute__((packed));

struct KernAux_ELF_ProgramEntry {
    unsigned long type       : 32;
    unsigned long offset     : 32;
    unsigned long virt_addr  : 32;
    unsigned long phys_addr  : 32;
    unsigned long file_size  : 32;
    unsigned long mem_size   : 32;
    unsigned long flags      : 32;
    unsigned long align      : 32;
}
__attribute__((packed));

struct KernAux_ELF_SectionEntry {
    unsigned long name        : 32;
    unsigned long type        : 32;
    unsigned long flags       : 32;
    unsigned long vaddr       : 32;
    unsigned long file_offset : 32;
    unsigned long file_size   : 32;
    unsigned long link        : 32;
    unsigned long info        : 32;
    unsigned long alignment   : 32;
    unsigned long ent_size    : 32;
}
__attribute__((packed));

struct KernAux_ELF_RelocationEntry {
    unsigned long virt_addr : 32;
    unsigned long info      : 32;
}
__attribute__((packed));

typedef struct KernAux_ELF_ProgramEntry KernAux_ELF_ProgramTable[];

typedef struct KernAux_ELF_SectionEntry KernAux_ELF_SectionTable[];

typedef struct KernAux_ELF_RelocationEntry KernAux_ELF_RelocationTable[];

inline static bool KernAux_ELF_Header_is_valid(
    const struct KernAux_ELF_Header *header
);

bool KernAux_ELF_Header_is_valid(
    const struct KernAux_ELF_Header *const header
) {
    if (!(
        header->magic_0x7F     == 0x7F &&
        header->magic_E        == 'E'  &&
        header->magic_L        == 'L'  &&
        header->magic_F        == 'F'  &&
        header->header_version == 1    &&
        header->elf_version    == 1
    )) {
        return false;
    }

    if (!(
        header->bitness == 1 || // 32 bit
        header->bitness == 2    // 64 bit
    )) {
        return false;
    }

    if (!(
        header->endianness == 1 || // Little endian
        header->endianness == 2    // Big endian
    )) {
        return false;
    }

    if (!(
        header->os_abi >= 0    &&
        header->os_abi <= 0x12 &&
        header->os_abi != 0x05
    )) {
        return false;
    }

    if (!(
        header->obj_type == 0x00   || // NONE
        header->obj_type == 0x01   || // REL
        header->obj_type == 0x02   || // EXEC
        header->obj_type == 0x03   || // DYN
        header->obj_type == 0x04   || // CORE
        header->obj_type == 0xFE00 || // LOOS
        header->obj_type == 0xFEFF || // HIOS
        header->obj_type == 0xFF00 || // LOPROC
        header->obj_type == 0xFFFF    // HIPROC
    )) {
        return false;
    }

    return true;
}

#ifdef __cplusplus
}
#endif

#endif
