#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/elf.h>

bool KernAux_ELF_Header_is_valid(
    const struct KernAux_ELF_Header *const header
) {
    KERNAUX_NOTNULL(header);

    if (!(
        header->magic_0x7f     == 0x7f &&
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

    if (!(header->os_abi <= 0x12 && header->os_abi != 0x05)) {
        return false;
    }

    if (!(
        header->obj_type == 0x00   || // NONE
        header->obj_type == 0x01   || // REL
        header->obj_type == 0x02   || // EXEC
        header->obj_type == 0x03   || // DYN
        header->obj_type == 0x04   || // CORE
        header->obj_type == 0xfe00 || // LOOS
        header->obj_type == 0xfeff || // HIOS
        header->obj_type == 0xff00 || // LOPROC
        header->obj_type == 0xffff    // HIPROC
    )) {
        return false;
    }

    return true;
}
