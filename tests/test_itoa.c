#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/itoa.h>

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

int main()
{
    {
        char buffer[10];

        kernaux_itoa(495, buffer, 'd');

        assert(buffer[0] == '4');
        assert(buffer[1] == '9');
        assert(buffer[2] == '5');
        assert(buffer[3] == '\0');
    }

    {
        char buffer[10];

        kernaux_itoa(-7012, buffer, 'd');

        assert(buffer[0] == '-');
        assert(buffer[1] == '7');
        assert(buffer[2] == '0');
        assert(buffer[3] == '1');
        assert(buffer[4] == '2');
        assert(buffer[5] == '\0');
    }

    char buffer[KERNAUX_ITOA_BUFFER_SIZE];

    for (
        size_t index = 0;
        index < sizeof(utoa10_cases) / sizeof(utoa10_cases[0]);
        ++index
    ) {
        kernaux_utoa10(utoa10_cases[index].value, buffer);
        assert(strcmp(buffer, utoa10_cases[index].result) == 0);
    }

    return 0;
}
