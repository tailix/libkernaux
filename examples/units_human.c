#include <kernaux/units.h>

#include <assert.h>
#include <string.h>

void example_main()
{
    char buffer[256];

    kernaux_units_human_raw(123, KERNAUX_UNIT_BIT, buffer, sizeof(buffer));
    assert(strcmp(buffer, "123 bit") == 0);

    kernaux_units_human_dec(123, KERNAUX_UNIT_BIT, KERNAUX_UNITPFX_KILO, buffer, sizeof(buffer));
    assert(strcmp(buffer, "123 kbit") == 0);
    kernaux_units_human_bin(123, KERNAUX_UNIT_BIT, KERNAUX_UNITPFX_KIBI, buffer, sizeof(buffer));
    assert(strcmp(buffer, "123 Kibit") == 0);

    kernaux_units_human_dec(123, KERNAUX_UNIT_BIT, KERNAUX_UNITPFX_MEGA, buffer, sizeof(buffer));
    assert(strcmp(buffer, "123 Mbit") == 0);
    kernaux_units_human_bin(123, KERNAUX_UNIT_BIT, KERNAUX_UNITPFX_MEBI, buffer, sizeof(buffer));
    assert(strcmp(buffer, "123 Mibit") == 0);

    kernaux_units_human_dec(123, KERNAUX_UNIT_BIT, KERNAUX_UNITPFX_GIGA, buffer, sizeof(buffer));
    assert(strcmp(buffer, "123 Gbit") == 0);
    kernaux_units_human_bin(123, KERNAUX_UNIT_BIT, KERNAUX_UNITPFX_GIBI, buffer, sizeof(buffer));
    assert(strcmp(buffer, "123 Gibit") == 0);

    kernaux_units_human_raw(123, KERNAUX_UNIT_BYTE, buffer, sizeof(buffer));
    assert(strcmp(buffer, "123 Byte") == 0);

    kernaux_units_human_dec(123, KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_KILO, buffer, sizeof(buffer));
    assert(strcmp(buffer, "123 kB") == 0);
    kernaux_units_human_bin(123, KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_KIBI, buffer, sizeof(buffer));
    assert(strcmp(buffer, "123 KiB") == 0);

    kernaux_units_human_dec(123, KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_MEGA, buffer, sizeof(buffer));
    assert(strcmp(buffer, "123 MB") == 0);
    kernaux_units_human_bin(123, KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_MEBI, buffer, sizeof(buffer));
    assert(strcmp(buffer, "123 MiB") == 0);

    kernaux_units_human_dec(123, KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_GIGA, buffer, sizeof(buffer));
    assert(strcmp(buffer, "123 GB") == 0);
    kernaux_units_human_bin(123, KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_GIBI, buffer, sizeof(buffer));
    assert(strcmp(buffer, "123 GiB") == 0);
}
