#ifndef KERNAUX_INCLUDED_MBR
#define KERNAUX_INCLUDED_MBR

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>

#include <stdbool.h>
#include <stdint.h>

#define KERNAUX_MBR_SIZE 512
#define KERNAUX_MBR_MAGIC 0xaa55
#define KERNAUX_MBR_ENTRIES 4

#define KERNAUX_MBR_BOOTSTRAP_SIZE \
    (KERNAUX_MBR_SIZE - sizeof(struct KernAux_Mbr_Info))

KERNAUX_PACKING_START

struct KernAux_Mbr_Entry {
    uint8_t  drive_attributes;
    unsigned first_sector_chs_addr : 24;
    uint8_t  partition_type;
    unsigned last_sector_chs_addr : 24;
    uint32_t first_sector_lba_addr;
    uint32_t sectors_count;
}
KERNAUX_PACKING_ATTR;

struct KernAux_Mbr_Info {
    uint32_t disk_id;
    uint16_t reserved;
    struct KernAux_Mbr_Entry entries[KERNAUX_MBR_ENTRIES];
    uint16_t magic;
}
KERNAUX_PACKING_ATTR;

struct KernAux_Mbr {
    uint8_t bootstrap[KERNAUX_MBR_BOOTSTRAP_SIZE];
    struct KernAux_Mbr_Info info;
}
KERNAUX_PACKING_ATTR;

KERNAUX_PACKING_END

bool KernAux_Mbr_is_valid(const struct KernAux_Mbr *mbr);
bool KernAux_Mbr_Info_is_valid(const struct KernAux_Mbr_Info *mbr_info);
bool KernAux_Mbr_Entry_is_valid(const struct KernAux_Mbr_Entry *mbr_entry);

#ifdef __cplusplus
}
#endif

#endif
