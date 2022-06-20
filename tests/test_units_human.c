#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/units.h>

#include <assert.h>
#include <stdint.h>
#include <string.h>

static void test_raw(
    unsigned long long value,
    enum KernAux_Unit unit,
    const char *result
);
static void test_dec(
    unsigned long long value,
    enum KernAux_Unit unit,
    enum KernAux_UnitPrefixDec prefix,
    const char *result
);
static void test_bin(
    unsigned long long value,
    enum KernAux_Unit unit,
    enum KernAux_UnitPrefixBin prefix,
    const char *result
);

void test_main()
{
    test_raw(0,          KERNAUX_UNIT_BIT,  "0 bit");
    test_raw(0,          KERNAUX_UNIT_BYTE, "0 Byte");
    test_raw(1,          KERNAUX_UNIT_BIT,  "1 bit");
    test_raw(1,          KERNAUX_UNIT_BYTE, "1 Byte");
    test_raw(2,          KERNAUX_UNIT_BIT,  "2 bit");
    test_raw(2,          KERNAUX_UNIT_BYTE, "2 Byte");
    test_raw(10,         KERNAUX_UNIT_BIT,  "10 bit");
    test_raw(10,         KERNAUX_UNIT_BYTE, "10 Byte");
    test_raw(UINT8_MAX,  KERNAUX_UNIT_BIT,  "255 bit");
    test_raw(UINT8_MAX,  KERNAUX_UNIT_BYTE, "255 Byte");
    test_raw(UINT16_MAX, KERNAUX_UNIT_BIT,  "65535 bit");
    test_raw(UINT16_MAX, KERNAUX_UNIT_BYTE, "65535 Byte");
    test_raw(UINT32_MAX, KERNAUX_UNIT_BIT,  "4294967295 bit");
    test_raw(UINT32_MAX, KERNAUX_UNIT_BYTE, "4294967295 Byte");
    test_raw(UINT64_MAX, KERNAUX_UNIT_BIT,  "18446744073709551615 bit");
    test_raw(UINT64_MAX, KERNAUX_UNIT_BYTE, "18446744073709551615 Byte");

    test_dec(0,          KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_KILO, "0 kbit");
    test_dec(0,          KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_KILO, "0 kB");
    test_dec(1,          KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_KILO, "1 kbit");
    test_dec(1,          KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_KILO, "1 kB");
    test_dec(2,          KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_KILO, "2 kbit");
    test_dec(2,          KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_KILO, "2 kB");
    test_dec(UINT8_MAX,  KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_KILO, "255 kbit");
    test_dec(UINT8_MAX,  KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_KILO, "255 kB");
    test_dec(UINT16_MAX, KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_KILO, "65535 kbit");
    test_dec(UINT16_MAX, KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_KILO, "65535 kB");
    test_dec(UINT32_MAX, KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_KILO, "4294967295 kbit");
    test_dec(UINT32_MAX, KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_KILO, "4294967295 kB");
    test_dec(UINT64_MAX, KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_KILO, "18446744073709551615 kbit");
    test_dec(UINT64_MAX, KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_KILO, "18446744073709551615 kB");

    test_dec(0,          KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_MEGA, "0 Mbit");
    test_dec(0,          KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_MEGA, "0 MB");
    test_dec(1,          KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_MEGA, "1 Mbit");
    test_dec(1,          KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_MEGA, "1 MB");
    test_dec(2,          KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_MEGA, "2 Mbit");
    test_dec(2,          KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_MEGA, "2 MB");
    test_dec(UINT8_MAX,  KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_MEGA, "255 Mbit");
    test_dec(UINT8_MAX,  KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_MEGA, "255 MB");
    test_dec(UINT16_MAX, KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_MEGA, "65535 Mbit");
    test_dec(UINT16_MAX, KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_MEGA, "65535 MB");
    test_dec(UINT32_MAX, KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_MEGA, "4294967295 Mbit");
    test_dec(UINT32_MAX, KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_MEGA, "4294967295 MB");
    test_dec(UINT64_MAX, KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_MEGA, "18446744073709551615 Mbit");
    test_dec(UINT64_MAX, KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_MEGA, "18446744073709551615 MB");

    test_dec(0,          KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_GIGA, "0 Gbit");
    test_dec(0,          KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_GIGA, "0 GB");
    test_dec(1,          KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_GIGA, "1 Gbit");
    test_dec(1,          KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_GIGA, "1 GB");
    test_dec(2,          KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_GIGA, "2 Gbit");
    test_dec(2,          KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_GIGA, "2 GB");
    test_dec(UINT8_MAX,  KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_GIGA, "255 Gbit");
    test_dec(UINT8_MAX,  KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_GIGA, "255 GB");
    test_dec(UINT16_MAX, KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_GIGA, "65535 Gbit");
    test_dec(UINT16_MAX, KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_GIGA, "65535 GB");
    test_dec(UINT32_MAX, KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_GIGA, "4294967295 Gbit");
    test_dec(UINT32_MAX, KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_GIGA, "4294967295 GB");
    test_dec(UINT64_MAX, KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_GIGA, "18446744073709551615 Gbit");
    test_dec(UINT64_MAX, KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_GIGA, "18446744073709551615 GB");

    test_bin(0,          KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_KIBI, "0 Kibit");
    test_bin(0,          KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_KIBI, "0 KiB");
    test_bin(1,          KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_KIBI, "1 Kibit");
    test_bin(1,          KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_KIBI, "1 KiB");
    test_bin(2,          KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_KIBI, "2 Kibit");
    test_bin(2,          KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_KIBI, "2 KiB");
    test_bin(UINT8_MAX,  KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_KIBI, "255 Kibit");
    test_bin(UINT8_MAX,  KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_KIBI, "255 KiB");
    test_bin(UINT16_MAX, KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_KIBI, "65535 Kibit");
    test_bin(UINT16_MAX, KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_KIBI, "65535 KiB");
    test_bin(UINT32_MAX, KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_KIBI, "4294967295 Kibit");
    test_bin(UINT32_MAX, KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_KIBI, "4294967295 KiB");
    test_bin(UINT64_MAX, KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_KIBI, "18446744073709551615 Kibit");
    test_bin(UINT64_MAX, KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_KIBI, "18446744073709551615 KiB");

    test_bin(0,          KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_MEBI, "0 Mibit");
    test_bin(0,          KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_MEBI, "0 MiB");
    test_bin(1,          KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_MEBI, "1 Mibit");
    test_bin(1,          KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_MEBI, "1 MiB");
    test_bin(2,          KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_MEBI, "2 Mibit");
    test_bin(2,          KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_MEBI, "2 MiB");
    test_bin(UINT8_MAX,  KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_MEBI, "255 Mibit");
    test_bin(UINT8_MAX,  KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_MEBI, "255 MiB");
    test_bin(UINT16_MAX, KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_MEBI, "65535 Mibit");
    test_bin(UINT16_MAX, KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_MEBI, "65535 MiB");
    test_bin(UINT32_MAX, KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_MEBI, "4294967295 Mibit");
    test_bin(UINT32_MAX, KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_MEBI, "4294967295 MiB");
    test_bin(UINT64_MAX, KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_MEBI, "18446744073709551615 Mibit");
    test_bin(UINT64_MAX, KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_MEBI, "18446744073709551615 MiB");

    test_bin(0,          KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_GIBI, "0 Gibit");
    test_bin(0,          KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_GIBI, "0 GiB");
    test_bin(1,          KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_GIBI, "1 Gibit");
    test_bin(1,          KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_GIBI, "1 GiB");
    test_bin(2,          KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_GIBI, "2 Gibit");
    test_bin(2,          KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_GIBI, "2 GiB");
    test_bin(UINT8_MAX,  KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_GIBI, "255 Gibit");
    test_bin(UINT8_MAX,  KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_GIBI, "255 GiB");
    test_bin(UINT16_MAX, KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_GIBI, "65535 Gibit");
    test_bin(UINT16_MAX, KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_GIBI, "65535 GiB");
    test_bin(UINT32_MAX, KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_GIBI, "4294967295 Gibit");
    test_bin(UINT32_MAX, KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_GIBI, "4294967295 GiB");
    test_bin(UINT64_MAX, KERNAUX_UNIT_BIT,  KERNAUX_UNITPFX_GIBI, "18446744073709551615 Gibit");
    test_bin(UINT64_MAX, KERNAUX_UNIT_BYTE, KERNAUX_UNITPFX_GIBI, "18446744073709551615 GiB");
}

void test_raw(
    const unsigned long long value,
    const enum KernAux_Unit unit,
    const char *const result
) {
    char buffer[64];
    assert(kernaux_units_human_raw(value, unit, buffer, sizeof(buffer)));
    assert(strcmp(buffer, result) == 0);
}

void test_dec(
    const unsigned long long value,
    const enum KernAux_Unit unit,
    const enum KernAux_UnitPrefixDec prefix,
    const char *const result
) {
    char buffer[64];
    assert(kernaux_units_human_dec(value, unit, prefix, buffer, sizeof(buffer)));
    assert(strcmp(buffer, result) == 0);
}

void test_bin(
    const unsigned long long value,
    const enum KernAux_Unit unit,
    const enum KernAux_UnitPrefixBin prefix,
    const char *const result
) {
    char buffer[64];
    assert(kernaux_units_human_bin(value, unit, prefix, buffer, sizeof(buffer)));
    assert(strcmp(buffer, result) == 0);
}
