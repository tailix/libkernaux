#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "cmdline_test.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static const char *const argv_spaceX3_X3[] = {"   ", "   ", "   "};
static const char *const argv_backslashX3_X3[] = {"\\\\\\", "\\\\\\", "\\\\\\"};
static const char *const argv_quotmarkX3_X3[] = {"\"\"\"", "\"\"\"", "\"\"\""};

static const char *const argv_aX50[] = {
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
};

static const char *const argv_a_X1[] = { "a" };
static const char *const argv_a_X2[] = { "a", "a" };
static const char *const argv_a_X3[] = { "a", "a", "a" };
static const char *const argv_a_X4[] = { "a", "a", "a", "a" };
static const char *const argv_a_X5[] = { "a", "a", "a", "a", "a" };
static const char *const argv_a_X6[] = { "a", "a", "a", "a", "a", "a" };

void test_main()
{
    test("\\ \\ \\  \\ \\ \\  \\ \\ \\ ",          3, 0,  true, "", 3, argv_spaceX3_X3);
    test("\\\\\\\\\\\\ \\\\\\\\\\\\ \\\\\\\\\\\\", 3, 0,  true, "", 3, argv_backslashX3_X3);
    test("\\\"\\\"\\\" \\\"\\\"\\\" \\\"\\\"\\\"", 3, 0,  true, "", 3, argv_quotmarkX3_X3);
    test("\\ \\ \\  \\ \\ \\  \\ \\ \\ ",          0, 12, true, "", 3, argv_spaceX3_X3);
    test("\\\\\\\\\\\\ \\\\\\\\\\\\ \\\\\\\\\\\\", 0, 12, true, "", 3, argv_backslashX3_X3);
    test("\\\"\\\"\\\" \\\"\\\"\\\" \\\"\\\"\\\"", 0, 12, true, "", 3, argv_quotmarkX3_X3);
    test("\\ \\ \\  \\ \\ \\  \\ \\ \\ ",          3, 12, true, "", 3, argv_spaceX3_X3);
    test("\\\\\\\\\\\\ \\\\\\\\\\\\ \\\\\\\\\\\\", 3, 12, true, "", 3, argv_backslashX3_X3);
    test("\\\"\\\"\\\" \\\"\\\"\\\" \\\"\\\"\\\"", 3, 12, true, "", 3, argv_quotmarkX3_X3);

    test("\\ \\ \\  \\ \\ \\  \\ \\ \\ ",          2, 0,  false, "too many args",          0, NULL);
    test("\\\\\\\\\\\\ \\\\\\\\\\\\ \\\\\\\\\\\\", 2, 0,  false, "too many args",          0, NULL);
    test("\\\"\\\"\\\" \\\"\\\"\\\" \\\"\\\"\\\"", 2, 0,  false, "too many args",          0, NULL);
    test("\\ \\ \\  \\ \\ \\  \\ \\ \\ ",          0, 11, false, "EOF or buffer overflow", 0, NULL);
    test("\\\\\\\\\\\\ \\\\\\\\\\\\ \\\\\\\\\\\\", 0, 11, false, "EOF or buffer overflow", 0, NULL);
    test("\\\"\\\"\\\" \\\"\\\"\\\" \\\"\\\"\\\"", 0, 11, false, "EOF or buffer overflow", 0, NULL);
    test("\\ \\ \\  \\ \\ \\  \\ \\ \\ ",          2, 11, false, "too many args",          0, NULL);
    test("\\\\\\\\\\\\ \\\\\\\\\\\\ \\\\\\\\\\\\", 2, 11, false, "too many args",          0, NULL);
    test("\\\"\\\"\\\" \\\"\\\"\\\" \\\"\\\"\\\"", 2, 11, false, "too many args",          0, NULL);

    test("\\",     0, 0, false, "EOL after backslash", 0, NULL);
    test(" \\",    0, 0, false, "EOL after backslash", 0, NULL);
    test("\\ \\",  0, 0, false, "EOL after backslash", 0, NULL);
    test("\\\\\\", 0, 0, false, "EOL after backslash", 0, NULL);
    test("\\\"\\", 0, 0, false, "EOL after backslash", 0, NULL);
    test("foo\\",  0, 0, false, "EOL after backslash", 0, NULL);

    test("\"\\",     0, 0, false, "EOL after backslash inside quote", 0, NULL);
    test("\" \\",    0, 0, false, "EOL after backslash inside quote", 0, NULL);
    test("\"\\ \\",  0, 0, false, "EOL after backslash inside quote", 0, NULL);
    test("\"\\\\\\", 0, 0, false, "EOL after backslash inside quote", 0, NULL);
    test("\"\\\"\\", 0, 0, false, "EOL after backslash inside quote", 0, NULL);
    test("\"foo\\",  0, 0, false, "EOL after backslash inside quote", 0, NULL);

    test("foo\"",    0, 0, false, "unescaped quotation mark", 0, NULL);
    test("foo\"bar", 0, 0, false, "unescaped quotation mark", 0, NULL);

    test("\"",    0, 0, false, "EOL inside quote", 0, NULL);
    test("\"foo", 0, 0, false, "EOL inside quote", 0, NULL);

    test(
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
        0,
        0,
        true,
        "",
        1,
        argv_aX50
    );

    test("a",                    1,  0, true,  "",              1, argv_a_X1);
    test("a ",                   1,  0, true,  "",              1, argv_a_X1);
    test("a a",                  1,  0, false, "too many args", 0, NULL);
    test("a a ",                 1,  0, false, "too many args", 0, NULL);
    test("a a",                  2,  0, true,  "",              2, argv_a_X2);
    test("a a ",                 2,  0, true,  "",              2, argv_a_X2);
    test("a a a",                2,  0, false, "too many args", 0, NULL);
    test("a a a ",               2,  0, false, "too many args", 0, NULL);
    test("a a a",                3,  0, true,  "",              3, argv_a_X3);
    test("a a a ",               3,  0, true,  "",              3, argv_a_X3);
    test("a a a a",              3,  0, false, "too many args", 0, NULL);
    test("a a a a ",             3,  0, false, "too many args", 0, NULL);
    test("a a a a",              4,  0, true,  "",              4, argv_a_X4);
    test("a a a a ",             4,  0, true,  "",              4, argv_a_X4);
    test("a a a a a",            4,  0, false, "too many args", 0, NULL);
    test("a a a a a ",           4,  0, false, "too many args", 0, NULL);
    test("a a a a a",            5,  0, true,  "",              5, argv_a_X5);
    test("a a a a a ",           5,  0, true,  "",              5, argv_a_X5);
    test("a a a a a a",          5,  0, false, "too many args", 0, NULL);
    test("a a a a a a ",         5,  0, false, "too many args", 0, NULL);
    test("a a a a a a",          6,  0, true,  "",              6, argv_a_X6);
    test("a a a a a a ",         6,  0, true,  "",              6, argv_a_X6);

    {
        char *const buffer = malloc(4096);
        memset(buffer, 'a', 4096 - 1);
        buffer[4096 - 1] = '\0';
        // 4095 of "a"
        test(buffer, 256, 4096, true, "", 1, NULL);
        free(buffer);
    }

    {
        char *const buffer = malloc(4096 + 1);
        memset(buffer, 'a', 4096);
        buffer[4096] = '\0';
        // 4096 of "a"
        test(buffer, 256, 4096, false, "EOF or buffer overflow", 0, NULL);
        free(buffer);
    }
}
