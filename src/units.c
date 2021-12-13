#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/units.h>

#include <kernaux/stdlib.h>

bool kernaux_units_human_raw(
    const size_t value,
    const enum KernAux_Unit unit,
    char *buffer,
    const size_t buffer_size
) {
    kernaux_itoa(value, buffer, 10);
    while (*buffer != '\0') ++buffer;
    *(buffer++) = ' ';

    switch (unit) {
    case KERNAUX_UNIT_BIT:
        *(buffer++) = 'b';
        *(buffer++) = 'i';
        *(buffer++) = 't';
        break;
    case KERNAUX_UNIT_BYTE:
        *(buffer++) = 'B';
        *(buffer++) = 'y';
        *(buffer++) = 't';
        *(buffer++) = 'e';
        break;
    }
    *(buffer++) = '\0';
}

bool kernaux_units_human_dec(
    const size_t value,
    const enum KernAux_Unit unit,
    const enum KernAux_UnitPrefixDec prefix,
    char *buffer,
    const size_t buffer_size
) {
    kernaux_itoa(value, buffer, 10);
    while (*buffer != '\0') ++buffer;
    *(buffer++) = ' ';

    switch (prefix) {
    case KERNAUX_UNITPFX_KILO:
        *(buffer++) = 'k';
        break;
    case KERNAUX_UNITPFX_MEGA:
        *(buffer++) = 'M';
        break;
    case KERNAUX_UNITPFX_GIGA:
        *(buffer++) = 'G';
        break;
    }

    switch (unit) {
    case KERNAUX_UNIT_BIT:
        *(buffer++) = 'b';
        *(buffer++) = 'i';
        *(buffer++) = 't';
        break;
    case KERNAUX_UNIT_BYTE:
        *(buffer++) = 'B';
        break;
    }
    *(buffer++) = '\0';
}

bool kernaux_units_human_bin(
    const size_t value,
    const enum KernAux_Unit unit,
    const enum KernAux_UnitPrefixBin prefix,
    char *buffer,
    const size_t buffer_size
) {
    kernaux_itoa(value, buffer, 10);
    while (*buffer != '\0') ++buffer;
    *(buffer++) = ' ';

    switch (prefix) {
    case KERNAUX_UNITPFX_KIBI:
        *(buffer++) = 'K';
        *(buffer++) = 'i';
        break;
    case KERNAUX_UNITPFX_MEBI:
        *(buffer++) = 'M';
        *(buffer++) = 'i';
        break;
    case KERNAUX_UNITPFX_GIBI:
        *(buffer++) = 'G';
        *(buffer++) = 'i';
        break;
    }

    switch (unit) {
    case KERNAUX_UNIT_BIT:
        *(buffer++) = 'b';
        *(buffer++) = 'i';
        *(buffer++) = 't';
        break;
    case KERNAUX_UNIT_BYTE:
        *(buffer++) = 'B';
        break;
    }
    *(buffer++) = '\0';
}
