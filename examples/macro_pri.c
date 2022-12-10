#include <kernaux/macro.h>

#include <assert.h>
#include <stdint.h>
#include <string.h>

#ifdef WITH_PRINTF
#include <kernaux/printf.h>
#define SPRINTF kernaux_sprintf
#else
#include <stdio.h>
#define SPRINTF sprintf
#endif

void example_main()
{
    char buffer[64];

    SPRINTF(buffer, "%"KERNAUX_PRIu8,  (uint8_t)255u);
    assert(strcmp(buffer, "255") == 0);

    SPRINTF(buffer, "%"KERNAUX_PRIi8,  (int8_t)127);
    assert(strcmp(buffer, "127") == 0);

    SPRINTF(buffer, "%"KERNAUX_PRIu16, (uint16_t)65535u);
    assert(strcmp(buffer, "65535") == 0);

    SPRINTF(buffer, "%"KERNAUX_PRIi16, (int16_t)32767);
    assert(strcmp(buffer, "32767") == 0);

    // cppcheck-suppress invalidPrintfArgType_uint
    SPRINTF(buffer, "%"KERNAUX_PRIu32, (uint32_t)4294967295u);
    assert(strcmp(buffer, "4294967295") == 0);

    // cppcheck-suppress invalidPrintfArgType_sint
    SPRINTF(buffer, "%"KERNAUX_PRIi32, (int32_t)2147483647);
    assert(strcmp(buffer, "2147483647") == 0);

    // cppcheck-suppress invalidPrintfArgType_uint
    SPRINTF(buffer, "%"KERNAUX_PRIu64, (uint64_t)18446744073709551615ull);
    assert(strcmp(buffer, "18446744073709551615") == 0);

    // cppcheck-suppress invalidPrintfArgType_sint
    SPRINTF(buffer, "%"KERNAUX_PRIi64, (int64_t)9223372036854775807ll);
    assert(strcmp(buffer, "9223372036854775807") == 0);
}
