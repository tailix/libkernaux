#ifndef KERNAUX_INCLUDED_UNITS
#define KERNAUX_INCLUDED_UNITS

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

enum KernAux_Unit {
    KERNAUX_UNIT_BIT,
    KERNAUX_UNIT_BYTE,
};

enum KernAux_UnitPrefixDec {
    KERNAUX_UNITPFX_KILO,
    KERNAUX_UNITPFX_MEGA,
    KERNAUX_UNITPFX_GIGA,
};

enum KernAux_UnitPrefixBin {
    KERNAUX_UNITPFX_KIBI,
    KERNAUX_UNITPFX_MEBI,
    KERNAUX_UNITPFX_GIBI,
};

bool kernaux_units_human_raw(uint64_t value, enum KernAux_Unit unit,
                             char *buffer, size_t buffer_size);
bool kernaux_units_human_dec(uint64_t value, enum KernAux_Unit unit,
                             enum KernAux_UnitPrefixDec prefix,
                             char *buffer, size_t buffer_size);
bool kernaux_units_human_bin(uint64_t value, enum KernAux_Unit unit,
                             enum KernAux_UnitPrefixBin prefix,
                             char *buffer, size_t buffer_size);

#ifdef __cplusplus
}
#endif

#endif
