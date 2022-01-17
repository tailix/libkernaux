#ifndef KERNAUX_INCLUDED_MBR
#define KERNAUX_INCLUDED_MBR

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define KERNAUX_MBR_SIZE 512
#define KERNAUX_MBR_MAGIC 0xAA55
#define KERNAUX_MBR_ENTRIES 4

#define KERNAUX_MBR_BOOTSTRAP_SIZE \
    (KERNAUX_MBR_SIZE - sizeof(struct KernAux_Mbr_Info))

struct KernAux_Mbr_Entry {
    uint8_t  drive_attributes;
    unsigned start_chs_address : 24;
    uint8_t  partition_type;
    unsigned last_chs_address : 24;
    uint32_t start_lba;
    uint32_t sectors_count;
}
__attribute__((packed));

struct KernAux_Mbr_Info {
    uint32_t disk_id;
    uint16_t reserved;
    struct KernAux_Mbr_Entry entries[KERNAUX_MBR_ENTRIES];
    uint16_t magic;
}
__attribute__((packed));

struct KernAux_Mbr {
    uint8_t bootstrap[KERNAUX_MBR_BOOTSTRAP_SIZE];
    struct KernAux_Mbr_Info info;
}
__attribute__((packed));

#ifdef __cplusplus
}
#endif

#endif
