#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "assert.h"

#include <kernaux/ntoa.h>
#include <kernaux/units.h>

#include <string.h>

#define TMP_BUFFER_SIZE (64)

bool kernaux_units_human_raw(
    const uint64_t value,
    const enum KernAux_Unit unit,
    char *const buffer,
    const size_t buffer_size
) {
    KERNAUX_NOTNULL(buffer);
    KERNAUX_ASSERT(buffer_size > 0);

    char tmp_buffer[TMP_BUFFER_SIZE];
    char *tmp = tmp_buffer;

    kernaux_utoa10(value, tmp);
    while (*tmp != '\0') ++tmp;
    *(tmp++) = ' ';

    switch (unit) {
    case KERNAUX_UNIT_BIT:
        *(tmp++) = 'b';
        *(tmp++) = 'i';
        *(tmp++) = 't';
        break;
    case KERNAUX_UNIT_BYTE:
        *(tmp++) = 'B';
        *(tmp++) = 'y';
        *(tmp++) = 't';
        *(tmp++) = 'e';
        break;
    }

    *(tmp++) = '\0';

    const size_t tmp_size = strlen(tmp_buffer) + 1;
    if (tmp_size > buffer_size) return false;

    strcpy(buffer, tmp_buffer);
    return true;
}

bool kernaux_units_human_dec(
    const uint64_t value,
    const enum KernAux_Unit unit,
    const enum KernAux_UnitPrefixDec prefix,
    char *const buffer,
    const size_t buffer_size
) {
    KERNAUX_NOTNULL(buffer);
    KERNAUX_ASSERT(buffer_size > 0);

    char tmp_buffer[TMP_BUFFER_SIZE];
    char *tmp = tmp_buffer;

    kernaux_utoa10(value, tmp);
    while (*tmp != '\0') ++tmp;
    *(tmp++) = ' ';

    switch (prefix) {
    case KERNAUX_UNITPFX_KILO:
        *(tmp++) = 'k';
        break;
    case KERNAUX_UNITPFX_MEGA:
        *(tmp++) = 'M';
        break;
    case KERNAUX_UNITPFX_GIGA:
        *(tmp++) = 'G';
        break;
    }

    switch (unit) {
    case KERNAUX_UNIT_BIT:
        *(tmp++) = 'b';
        *(tmp++) = 'i';
        *(tmp++) = 't';
        break;
    case KERNAUX_UNIT_BYTE:
        *(tmp++) = 'B';
        break;
    }

    *(tmp++) = '\0';

    const size_t tmp_size = strlen(tmp_buffer) + 1;
    if (tmp_size > buffer_size) return false;

    strcpy(buffer, tmp_buffer);
    return true;
}

bool kernaux_units_human_bin(
    const uint64_t value,
    const enum KernAux_Unit unit,
    const enum KernAux_UnitPrefixBin prefix,
    char *const buffer,
    const size_t buffer_size
) {
    char tmp_buffer[TMP_BUFFER_SIZE];
    char *tmp = tmp_buffer;

    kernaux_utoa10(value, tmp);
    while (*tmp != '\0') ++tmp;
    *(tmp++) = ' ';

    switch (prefix) {
    case KERNAUX_UNITPFX_KIBI:
        *(tmp++) = 'K';
        *(tmp++) = 'i';
        break;
    case KERNAUX_UNITPFX_MEBI:
        *(tmp++) = 'M';
        *(tmp++) = 'i';
        break;
    case KERNAUX_UNITPFX_GIBI:
        *(tmp++) = 'G';
        *(tmp++) = 'i';
        break;
    }

    switch (unit) {
    case KERNAUX_UNIT_BIT:
        *(tmp++) = 'b';
        *(tmp++) = 'i';
        *(tmp++) = 't';
        break;
    case KERNAUX_UNIT_BYTE:
        *(tmp++) = 'B';
        break;
    }

    *(tmp++) = '\0';

    const size_t tmp_size = strlen(tmp_buffer) + 1;
    if (tmp_size > buffer_size) return false;

    strcpy(buffer, tmp_buffer);
    return true;
}
