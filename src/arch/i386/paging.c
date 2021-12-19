#include <kernaux/arch/i386.h>

// TODO: There are some static asserts just for example.

__attribute__((unused))
static const int assert0[
    sizeof(struct KernAux_Arch_I386_PDE) == sizeof(uint32_t) ? 1 : -1
];

__attribute__((unused))
static const int assert1[
    sizeof(struct KernAux_Arch_I386_PTE) == sizeof(uint32_t) ? 1 : -1
];

__attribute__((unused))
static const int assert1[
    sizeof(struct KernAux_Arch_I386_PageDir) == 1024 * sizeof(uint32_t) ? 1 : -1
];

__attribute__((unused))
static const int assert1[
    sizeof(struct KernAux_Arch_I386_PageTable) == 1024 * sizeof(uint32_t) ? 1 : -1
];
