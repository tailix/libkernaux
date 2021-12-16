#ifndef KERNAUX_INCLUDED_ELF
#define KERNAUX_INCLUDED_ELF 1

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

struct KernAux_ELF_Header {
    unsigned magic_0x7F     : 8;
    unsigned magic_E        : 8;
    unsigned magic_L        : 8;
    unsigned magic_F        : 8;
    unsigned bitness        : 8;
    unsigned endianness     : 8;
    unsigned header_version : 8;
    unsigned os_abi         : 8;
    unsigned unused1        : 32;
    unsigned unused2        : 32;
    unsigned obj_type       : 16;
    unsigned isa            : 16;
    unsigned elf_version    : 32;
    unsigned entrypoint     : 32;
    unsigned prog_table_pos : 32;
    unsigned sect_table_pos : 32;
    unsigned arch_flags     : 32;
    unsigned header_size    : 16;
    unsigned prog_entr_size : 16;
    unsigned prog_entr_num  : 16;
    unsigned sect_entr_size : 16;
    unsigned sect_entr_num  : 16;
    unsigned sect_names_idx : 16;
}
__attribute__((packed));

struct KernAux_ELF_ProgramEntry {
    unsigned type      : 32;
    unsigned offset    : 32;
    unsigned virt_addr : 32;
    unsigned phys_addr : 32;
    unsigned file_size : 32;
    unsigned mem_size  : 32;
    unsigned flags     : 32;
    unsigned align     : 32;
}
__attribute__((packed));

struct KernAux_ELF_SectionEntry {
    unsigned name        : 32;
    unsigned type        : 32;
    unsigned flags       : 32;
    unsigned vaddr       : 32;
    unsigned file_offset : 32;
    unsigned file_size   : 32;
    unsigned link        : 32;
    unsigned info        : 32;
    unsigned alignment   : 32;
    unsigned ent_size    : 32;
}
__attribute__((packed));

struct KernAux_ELF_RelocationEntry {
    unsigned virt_addr : 32;
    unsigned info      : 32;
}
__attribute__((packed));

typedef struct KernAux_ELF_ProgramEntry KernAux_ELF_ProgramTable[];

typedef struct KernAux_ELF_SectionEntry KernAux_ELF_SectionTable[];

typedef struct KernAux_ELF_RelocationEntry KernAux_ELF_RelocationTable[];

bool KernAux_ELF_Header_is_valid(const struct KernAux_ELF_Header *header);

#ifdef __cplusplus
}
#endif

#endif
