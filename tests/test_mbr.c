#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/mbr.h>

#include <assert.h>
#include <string.h>

static void create_valid_mbr(struct KernAux_Mbr *mbr);

void test_main()
{
    struct KernAux_Mbr mbr;

    create_valid_mbr(&mbr);

    assert(KernAux_Mbr_is_valid(&mbr));
    assert(KernAux_Mbr_Info_is_valid(&mbr.info));
    for (size_t index = 0; index < KERNAUX_MBR_ENTRIES; ++index) {
        assert(KernAux_Mbr_Entry_is_valid(&mbr.info.entries[index]));
    }

    create_valid_mbr(&mbr);
    mbr.info.magic = 123;

    assert(!KernAux_Mbr_is_valid(&mbr));
    assert(!KernAux_Mbr_Info_is_valid(&mbr.info));
    for (size_t index = 0; index < KERNAUX_MBR_ENTRIES; ++index) {
        assert(KernAux_Mbr_Entry_is_valid(&mbr.info.entries[index]));
    }

    // TODO: test partition table
}

void create_valid_mbr(struct KernAux_Mbr *const mbr)
{
    memset(mbr, 0, sizeof(*mbr));

    mbr->info.magic = KERNAUX_MBR_MAGIC;
    mbr->info.disk_id = 0xCAFEBABE;
    // TODO: fill partition table
}
