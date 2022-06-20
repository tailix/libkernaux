#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "helper.h"

#include <kernaux/cmdline.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define ARGV_COUNT_MAX 100
#define BUFFER_SIZE 4096

static void test(
    const char *cmdline,
    size_t argv_count_max,
    size_t buffer_size,

    bool expected_result,
    const char *expected_error_msg,
    size_t expected_argc,
    const char *const *const expected_argv
);

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

int main()
{
    setup_assert_abort();

    test("\\ \\ \\  \\ \\ \\  \\ \\ \\ ",          3, 0,  true, "", 3, argv_spaceX3_X3);
    test("\\\\\\\\\\\\ \\\\\\\\\\\\ \\\\\\\\\\\\", 3, 0,  true, "", 3, argv_backslashX3_X3);
    test("\\\"\\\"\\\" \\\"\\\"\\\" \\\"\\\"\\\"", 3, 0,  true, "", 3, argv_quotmarkX3_X3);
    test("\\ \\ \\  \\ \\ \\  \\ \\ \\ ",          0, 12, true, "", 3, argv_spaceX3_X3);
    test("\\\\\\\\\\\\ \\\\\\\\\\\\ \\\\\\\\\\\\", 0, 12, true, "", 3, argv_backslashX3_X3);
    test("\\\"\\\"\\\" \\\"\\\"\\\" \\\"\\\"\\\"", 0, 12, true, "", 3, argv_quotmarkX3_X3);
    test("\\ \\ \\  \\ \\ \\  \\ \\ \\ ",          3, 12, true, "", 3, argv_spaceX3_X3);
    test("\\\\\\\\\\\\ \\\\\\\\\\\\ \\\\\\\\\\\\", 3, 12, true, "", 3, argv_backslashX3_X3);
    test("\\\"\\\"\\\" \\\"\\\"\\\" \\\"\\\"\\\"", 3, 12, true, "", 3, argv_quotmarkX3_X3);

    test("\\ \\ \\  \\ \\ \\  \\ \\ \\ ",          2, 0,  false, "too many args",   0, NULL);
    test("\\\\\\\\\\\\ \\\\\\\\\\\\ \\\\\\\\\\\\", 2, 0,  false, "too many args",   0, NULL);
    test("\\\"\\\"\\\" \\\"\\\"\\\" \\\"\\\"\\\"", 2, 0,  false, "too many args",   0, NULL);
    test("\\ \\ \\  \\ \\ \\  \\ \\ \\ ",          0, 11, false, "buffer overflow", 0, NULL);
    test("\\\\\\\\\\\\ \\\\\\\\\\\\ \\\\\\\\\\\\", 0, 11, false, "buffer overflow", 0, NULL);
    test("\\\"\\\"\\\" \\\"\\\"\\\" \\\"\\\"\\\"", 0, 11, false, "buffer overflow", 0, NULL);
    test("\\ \\ \\  \\ \\ \\  \\ \\ \\ ",          2, 11, false, "too many args",   0, NULL);
    test("\\\\\\\\\\\\ \\\\\\\\\\\\ \\\\\\\\\\\\", 2, 11, false, "too many args",   0, NULL);
    test("\\\"\\\"\\\" \\\"\\\"\\\" \\\"\\\"\\\"", 2, 11, false, "too many args",   0, NULL);

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
        test(buffer, 256, 4096, false, "buffer overflow", 0, NULL);
        free(buffer);
    }

    return 0;
}

void test(
    const char *const cmdline,
    size_t argv_count_max,
    size_t buffer_size,

    const bool expected_result,
    const char *const expected_error_msg,
    size_t expected_argc,
    const char *const *const expected_argv
) {
    if (argv_count_max == 0) argv_count_max = ARGV_COUNT_MAX;
    if (buffer_size    == 0) buffer_size    = BUFFER_SIZE;

    char *error_msg = malloc(KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX);
    size_t argc = 1234;
    char **const argv = malloc(sizeof(char*) * argv_count_max);
    char *const buffer = malloc(buffer_size);

    assert(error_msg);
    assert(argv);
    assert(buffer);

    memset(error_msg, 'x', KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX);
    memset(argv,      'x', sizeof(char*) * argv_count_max);
    memset(buffer,    'x', buffer_size);

    assert(
        kernaux_cmdline(
            cmdline,
            error_msg,
            &argc,
            argv,
            buffer,
            argv_count_max,
            buffer_size
        ) == !!expected_result
    );

    assert(strcmp(error_msg, expected_error_msg) == 0);
    assert(argc == expected_argc);

    if (expected_argv) {
        for (size_t index = 0; index < argc; ++index) {
            assert(strcmp(argv[index], expected_argv[index]) == 0);
        }
    }

    for (size_t index = argc; index < argv_count_max; ++index) {
        assert(argv[index] == NULL);
    }

    free(error_msg);
    free(argv);
    free(buffer);
}
