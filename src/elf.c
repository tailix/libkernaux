#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/elf.h>
#include <kernaux/macro.h>

#include <stddef.h>

const char *KernAux_ELF_Section_Type_to_str(const uint32_t type)
{
    switch (type) {
    case KERNAUX_ELF_SECT_TYPE_NULL:
        return "NULL";
    case KERNAUX_ELF_SECT_TYPE_PROGBITS:
        return "PROGBITS";
    case KERNAUX_ELF_SECT_TYPE_SYMTAB:
        return "SYMTAB";
    case KERNAUX_ELF_SECT_TYPE_STRTAB:
        return "STRTAB";
    case KERNAUX_ELF_SECT_TYPE_RELA:
        return "RELA";
    case KERNAUX_ELF_SECT_TYPE_HASH:
        return "HASH";
    case KERNAUX_ELF_SECT_TYPE_DYNAMIC:
        return "DYNAMIC";
    case KERNAUX_ELF_SECT_TYPE_NOTE:
        return "NOTE";
    case KERNAUX_ELF_SECT_TYPE_NOBITS:
        return "NOBITS";
    case KERNAUX_ELF_SECT_TYPE_REL:
        return "REL";
    case KERNAUX_ELF_SECT_TYPE_SHLIB:
        return "SHLIB";
    case KERNAUX_ELF_SECT_TYPE_DYNSYM:
        return "DYNSYM";
    case KERNAUX_ELF_SECT_TYPE_LOPROC:
        return "LOPROC";
    case KERNAUX_ELF_SECT_TYPE_HIPROC:
        return "HIPROC";
    case KERNAUX_ELF_SECT_TYPE_LOUSER:
        return "LOUSER";
    case KERNAUX_ELF_SECT_TYPE_HIUSER:
        return "HIUSER";
    default:
        return NULL;
    }
}
