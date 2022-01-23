#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/ntoa.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

static const struct {
    uint64_t value;
    const char *result;
} utoa10_cases[] = {
    { 0,                        "0" },
    { 1,                        "1" },
    { 2,                        "2" },
    { 9,                        "9" },
    { 10,                       "10" },
    { 11,                       "11" },
    { 12,                       "12" },
    { 19,                       "19" },
    { 20,                       "20" },
    { 21,                       "21" },
    { 99,                       "99" },
    { 100,                      "100" },
    { 101,                      "101" },
    { 199,                      "199" },
    { 200,                      "200" },
    { 201,                      "201" },
    { 999,                      "999" },
    { 1000,                     "1000" },
    { 1001,                     "1001" },
    { 1999,                     "1999" },
    { 2000,                     "2000" },
    { 2001,                     "2001" },
    { 9999,                     "9999" },
    { 10000,                    "10000" },
    { 10001,                    "10001" },
    { UINT16_MAX,               "65535" },
    { UINT16_MAX + 1,           "65536" },
    { UINT32_MAX,               "4294967295" },
    { (uint64_t)UINT32_MAX + 1, "4294967296" },
    { UINT64_MAX - 6,           "18446744073709551609" },
    { UINT64_MAX - 5,           "18446744073709551610" },
    { UINT64_MAX - 1,           "18446744073709551614" },
    { UINT64_MAX,               "18446744073709551615" },
};

static const struct {
    int64_t value;
    const char *result;
} itoa10_cases[] = {
    { 0,                       "0" },
    { 1,                       "1" },
    { -1,                      "-1" },
    { 2,                       "2" },
    { -2,                      "-2" },
    { 9,                       "9" },
    { -9,                      "-9" },
    { 10,                      "10" },
    { -10,                     "-10" },
    { 11,                      "11" },
    { -11,                     "-11" },
    { 12,                      "12" },
    { 19,                      "19" },
    { 20,                      "20" },
    { 21,                      "21" },
    { 99,                      "99" },
    { 100,                     "100" },
    { 101,                     "101" },
    { 199,                     "199" },
    { 200,                     "200" },
    { 201,                     "201" },
    { 999,                     "999" },
    { 1000,                    "1000" },
    { 1001,                    "1001" },
    { 1999,                    "1999" },
    { 2000,                    "2000" },
    { 2001,                    "2001" },
    { 9999,                    "9999" },
    { 10000,                   "10000" },
    { 10001,                   "10001" },
    { UINT16_MAX,              "65535" },
    { UINT16_MAX + 1,          "65536" },
    { UINT32_MAX,              "4294967295" },
    { (int64_t)UINT32_MAX + 1, "4294967296" },
    { INT64_MAX - 8,           "9223372036854775799" },
    { INT64_MIN + 9,           "-9223372036854775799" },
    { INT64_MAX - 7,           "9223372036854775800" },
    { INT64_MIN + 8,           "-9223372036854775800" },
    { INT64_MAX - 1,           "9223372036854775806" },
    { INT64_MIN + 1,           "-9223372036854775807" },
    { INT64_MAX,               "9223372036854775807" },
    { INT64_MIN,               "-9223372036854775808" },
};

static const struct {
    uint64_t value;
    const char *result;
} utoa16_cases[] = {
    { 0x0,   "0"   }, { 0x1,   "1"   },
    { 0x2,   "2"   }, { 0x9,   "9"   },
    { 0xa,   "a"   }, { 0xb,   "b"   },
    { 0xc,   "c"   }, { 0xd,   "d"   },
    { 0xe,   "e"   }, { 0xf,   "f"   },
    { 0x10,  "10"  }, { 0x11,  "11"  },
    { 0x12,  "12"  }, { 0x19,  "19"  },
    { 0x1a,  "1a"  }, { 0x1b,  "1b"  },
    { 0x1c,  "1c"  }, { 0x1d,  "1d"  },
    { 0x1e,  "1e"  }, { 0x1f,  "1f"  },
    { 0x20,  "20"  }, { 0x21,  "21"  },
    { 0x22,  "22"  }, { 0x29,  "29"  },
    { 0x2a,  "2a"  }, { 0x2b,  "2b"  },
    { 0x2c,  "2c"  }, { 0x2d,  "2d"  },
    { 0x2e,  "2e"  }, { 0x2f,  "2f"  },
    { 0x90,  "90"  }, { 0x91,  "91"  },
    { 0x92,  "92"  }, { 0x99,  "99"  },
    { 0x9a,  "9a"  }, { 0x9b,  "9b"  },
    { 0x9c,  "9c"  }, { 0x9d,  "9d"  },
    { 0x9e,  "9e"  }, { 0x9f,  "9f"  },
    { 0xa0,  "a0"  }, { 0xa1,  "a1"  },
    { 0xa2,  "a2"  }, { 0xa9,  "a9"  },
    { 0xaa,  "aa"  }, { 0xab,  "ab"  },
    { 0xac,  "ac"  }, { 0xad,  "ad"  },
    { 0xae,  "ae"  }, { 0xaf,  "af"  },
    { 0xb0,  "b0"  }, { 0xb1,  "b1"  },
    { 0xb2,  "b2"  }, { 0xb9,  "b9"  },
    { 0xba,  "ba"  }, { 0xbb,  "bb"  },
    { 0xbc,  "bc"  }, { 0xbd,  "bd"  },
    { 0xbe,  "be"  }, { 0xbf,  "bf"  },
    { 0xc0,  "c0"  }, { 0xc1,  "c1"  },
    { 0xc2,  "c2"  }, { 0xc9,  "c9"  },
    { 0xca,  "ca"  }, { 0xcb,  "cb"  },
    { 0xcc,  "cc"  }, { 0xcd,  "cd"  },
    { 0xce,  "ce"  }, { 0xcf,  "cf"  },
    { 0xd0,  "d0"  }, { 0xd1,  "d1"  },
    { 0xd2,  "d2"  }, { 0xd9,  "d9"  },
    { 0xda,  "da"  }, { 0xdb,  "db"  },
    { 0xdc,  "dc"  }, { 0xdd,  "dd"  },
    { 0xde,  "de"  }, { 0xdf,  "df"  },
    { 0xe0,  "e0"  }, { 0xe1,  "e1"  },
    { 0xe2,  "e2"  }, { 0xe9,  "e9"  },
    { 0xea,  "ea"  }, { 0xeb,  "eb"  },
    { 0xec,  "ec"  }, { 0xed,  "ed"  },
    { 0xee,  "ee"  }, { 0xef,  "ef"  },
    { 0xf0,  "f0"  }, { 0xf1,  "f1"  },
    { 0xf2,  "f2"  }, { 0xf9,  "f9"  },
    { 0xfa,  "fa"  }, { 0xfb,  "fb"  },
    { 0xfc,  "fc"  }, { 0xfd,  "fd"  },
    { 0xfe,  "fe"  }, { 0xff,  "ff"  },
    { 0x100, "100" }, { 0x101, "101" },
    { 0x109, "109" }, { 0x10a, "10a" },
    { 0x10f, "10f" },
    { 0x110, "110" }, { 0x111, "111" },
    { 0x119, "119" }, { 0x11a, "11a" },
    { 0x11f, "11f" }, { 0x120, "120" },
    { 0x1ff, "1ff" }, { 0x200, "200" },
    { 0xfff, "fff" }, { 0x1000, "1000" },
    { UINT16_MAX,               "ffff" },
    { UINT16_MAX + 1,           "10000" },
    { UINT32_MAX,               "ffffffff" },
    { (uint64_t)UINT32_MAX + 1, "100000000" },
    { UINT64_MAX - 6,           "fffffffffffffff9" },
    { UINT64_MAX - 5,           "fffffffffffffffa" },
    { UINT64_MAX - 1,           "fffffffffffffffe" },
    { UINT64_MAX,               "ffffffffffffffff" },
};

static const struct {
    int64_t value;
    const char *result;
} itoa16_cases[] = {
    { 0x0,   "0"   }, { 0x1,   "1"   },
    { 0x2,   "2"   }, { 0x9,   "9"   },
    { 0xa,   "a"   }, { 0xb,   "b"   },
    { 0xc,   "c"   }, { 0xd,   "d"   },
    { 0xe,   "e"   }, { 0xf,   "f"   },
    { 0x10,  "10"  }, { 0x11,  "11"  },
    { 0x12,  "12"  }, { 0x19,  "19"  },
    { 0x1a,  "1a"  }, { 0x1b,  "1b"  },
    { 0x1c,  "1c"  }, { 0x1d,  "1d"  },
    { 0x1e,  "1e"  }, { 0x1f,  "1f"  },
    { 0x20,  "20"  }, { 0x21,  "21"  },
    { 0x22,  "22"  }, { 0x29,  "29"  },
    { 0x2a,  "2a"  }, { 0x2b,  "2b"  },
    { 0x2c,  "2c"  }, { 0x2d,  "2d"  },
    { 0x2e,  "2e"  }, { 0x2f,  "2f"  },
    { 0x90,  "90"  }, { 0x91,  "91"  },
    { 0x92,  "92"  }, { 0x99,  "99"  },
    { 0x9a,  "9a"  }, { 0x9b,  "9b"  },
    { 0x9c,  "9c"  }, { 0x9d,  "9d"  },
    { 0x9e,  "9e"  }, { 0x9f,  "9f"  },
    { 0xa0,  "a0"  }, { 0xa1,  "a1"  },
    { 0xa2,  "a2"  }, { 0xa9,  "a9"  },
    { 0xaa,  "aa"  }, { 0xab,  "ab"  },
    { 0xac,  "ac"  }, { 0xad,  "ad"  },
    { 0xae,  "ae"  }, { 0xaf,  "af"  },
    { 0xb0,  "b0"  }, { 0xb1,  "b1"  },
    { 0xb2,  "b2"  }, { 0xb9,  "b9"  },
    { 0xba,  "ba"  }, { 0xbb,  "bb"  },
    { 0xbc,  "bc"  }, { 0xbd,  "bd"  },
    { 0xbe,  "be"  }, { 0xbf,  "bf"  },
    { 0xc0,  "c0"  }, { 0xc1,  "c1"  },
    { 0xc2,  "c2"  }, { 0xc9,  "c9"  },
    { 0xca,  "ca"  }, { 0xcb,  "cb"  },
    { 0xcc,  "cc"  }, { 0xcd,  "cd"  },
    { 0xce,  "ce"  }, { 0xcf,  "cf"  },
    { 0xd0,  "d0"  }, { 0xd1,  "d1"  },
    { 0xd2,  "d2"  }, { 0xd9,  "d9"  },
    { 0xda,  "da"  }, { 0xdb,  "db"  },
    { 0xdc,  "dc"  }, { 0xdd,  "dd"  },
    { 0xde,  "de"  }, { 0xdf,  "df"  },
    { 0xe0,  "e0"  }, { 0xe1,  "e1"  },
    { 0xe2,  "e2"  }, { 0xe9,  "e9"  },
    { 0xea,  "ea"  }, { 0xeb,  "eb"  },
    { 0xec,  "ec"  }, { 0xed,  "ed"  },
    { 0xee,  "ee"  }, { 0xef,  "ef"  },
    { 0xf0,  "f0"  }, { 0xf1,  "f1"  },
    { 0xf2,  "f2"  }, { 0xf9,  "f9"  },
    { 0xfa,  "fa"  }, { 0xfb,  "fb"  },
    { 0xfc,  "fc"  }, { 0xfd,  "fd"  },
    { 0xfe,  "fe"  }, { 0xff,  "ff"  },
    { 0x100, "100" }, { 0x101, "101" },
    { 0x109, "109" }, { 0x10a, "10a" },
    { 0x10f, "10f" },
    { 0x110, "110" }, { 0x111, "111" },
    { 0x119, "119" }, { 0x11a, "11a" },
    { 0x11f, "11f" }, { 0x120, "120" },
    { 0x1ff, "1ff" }, { 0x200, "200" },
    { 0xfff, "fff" }, { 0x1000, "1000" },
    { UINT16_MAX,               "ffff" },
    { UINT16_MAX + 1,           "10000" },
    { UINT32_MAX,               "ffffffff" },
    { (uint64_t)UINT32_MAX + 1, "100000000" },
    { INT64_MIN + 7,            "-7ffffffffffffff9" },
    { INT64_MAX - 6,            "7ffffffffffffff9" },
    { INT64_MIN + 6,            "-7ffffffffffffffa" },
    { INT64_MAX - 5,            "7ffffffffffffffa" },
    { INT64_MIN + 2,            "-7ffffffffffffffe" },
    { INT64_MAX - 1,            "7ffffffffffffffe" },
    { INT64_MIN + 1,            "-7fffffffffffffff" },
    { INT64_MAX,                "7fffffffffffffff" },
    { INT64_MIN,                "-8000000000000000" },
};

int main()
{
    {
        char buffer[KERNAUX_UTOA10_BUFFER_SIZE];

        for (
            size_t index = 0;
            index < sizeof(utoa10_cases) / sizeof(utoa10_cases[0]);
            ++index
        ) {
            kernaux_utoa10(utoa10_cases[index].value, buffer);
            assert(strcmp(buffer, utoa10_cases[index].result) == 0);
        }
    }

    {
        char buffer[KERNAUX_ITOA10_BUFFER_SIZE];

        for (
            size_t index = 0;
            index < sizeof(itoa10_cases) / sizeof(itoa10_cases[0]);
            ++index
        ) {
            const int64_t value = itoa10_cases[index].value;

            kernaux_itoa10(value, buffer);
            assert(strcmp(buffer, itoa10_cases[index].result) == 0);

            if (value <= 0) continue;

            kernaux_itoa10(-value, buffer);
            assert(buffer[0] == '-');
            assert(strcmp(&buffer[1], itoa10_cases[index].result) == 0);
        }
    }

    {
        char buffer[KERNAUX_UTOA16_BUFFER_SIZE];

        for (
            size_t index = 0;
            index < sizeof(utoa16_cases) / sizeof(utoa16_cases[0]);
            ++index
        ) {
            kernaux_utoa16(utoa16_cases[index].value, buffer);
            assert(strcmp(buffer, utoa16_cases[index].result) == 0);
        }
    }

    {
        char buffer[KERNAUX_ITOA16_BUFFER_SIZE];

        for (
            size_t index = 0;
            index < sizeof(itoa16_cases) / sizeof(itoa16_cases[0]);
            ++index
        ) {
            const int64_t value = itoa16_cases[index].value;

            kernaux_itoa16(value, buffer);
            assert(strcmp(buffer, itoa16_cases[index].result) == 0);

            if (value <= 0) continue;

            kernaux_itoa16(-value, buffer);
            assert(buffer[0] == '-');
            assert(strcmp(&buffer[1], itoa16_cases[index].result) == 0);
        }
    }

    return 0;
}
