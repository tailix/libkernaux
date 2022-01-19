#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/ntoa.h>

#include <assert.h>
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

int main()
{
    char buffer[KERNAUX_ITOA_BUFFER_SIZE];

    for (
        size_t index = 0;
        index < sizeof(utoa10_cases) / sizeof(utoa10_cases[0]);
        ++index
    ) {
        kernaux_utoa10(utoa10_cases[index].value, buffer);
        assert(strcmp(buffer, utoa10_cases[index].result) == 0);
    }

    for (
        size_t index = 0;
        index < sizeof(itoa10_cases) / sizeof(itoa10_cases[0]);
        ++index
    ) {
        kernaux_itoa10(itoa10_cases[index].value, buffer);
        assert(strcmp(buffer, itoa10_cases[index].result) == 0);
    }

    return 0;
}
