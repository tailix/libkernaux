#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/mbr.h>

#include <stdbool.h>
#include <stddef.h>

bool KernAux_Mbr_is_valid(const struct KernAux_Mbr *const mbr)
{
    KERNAUX_NOTNULL_RETVAL(mbr, false);

    return KernAux_Mbr_Info_is_valid(&mbr->info);
}

bool KernAux_Mbr_Info_is_valid(const struct KernAux_Mbr_Info *const mbr_info)
{
    KERNAUX_NOTNULL_RETVAL(mbr_info, false);

    if (mbr_info->magic != KERNAUX_MBR_MAGIC) return false;

    for (size_t index = 0; index < KERNAUX_MBR_ENTRIES; ++index) {
        if (!KernAux_Mbr_Entry_is_valid(&mbr_info->entries[index])) {
            return false;
        }
    }

    return true;
}

bool KernAux_Mbr_Entry_is_valid(const struct KernAux_Mbr_Entry *const mbr_entry)
{
    KERNAUX_NOTNULL_RETVAL(mbr_entry, false);

    // TODO: implement this
    return true;
}
