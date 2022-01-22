#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

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

static const char *const argv_empty[] = {""};
static const char *const argv_empty_X2[] = {"", ""};
static const char *const argv_empty_X3[] = {"", "", ""};

static const char *const argv_foo[] = {"foo"};
static const char *const argv_foo_bar[] = {"foo", "bar"};
static const char *const argv_foo_bar_car[] = {"foo", "bar", "car"};

static const char *const argv_spaceX3_X3[] = {"   ", "   ", "   "};
static const char *const argv_backslashX3_X3[] = {"\\\\\\", "\\\\\\", "\\\\\\"};
static const char *const argv_quotmarkX3_X3[] = {"\"\"\"", "\"\"\"", "\"\"\""};

static const char *const argv_foospacebar_car[] = {"foo bar", "car"};
static const char *const argv_foo_barspacecar[] = {"foo", "bar car"};

static const char *const argv_space[] = {" "};
static const char *const argv_backslash[] = {"\\"};
static const char *const argv_quotmark[] = {"\""};
static const char *const argv_foospace[] = {"foo "};
static const char *const argv_foobackslash[] = {"foo\\"};
static const char *const argv_fooquotmark[] = {"foo\""};
static const char *const argv_spacefoo[] = {" foo"};
static const char *const argv_backslashfoo[] = {"\\foo"};
static const char *const argv_quotmarkfoo[] = {"\"foo"};
static const char *const argv_spacefoospace[] = {" foo "};
static const char *const argv_backslashfoobackslash[] = {"\\foo\\"};
static const char *const argv_quotmarkfooquotmark[] = {"\"foo\""};
static const char *const argv_foospacebar[] = {"foo bar"};
static const char *const argv_foobackslashbar[] = {"foo\\bar"};
static const char *const argv_fooquotmarkbar[] = {"foo\"bar"};
static const char *const argv_spacefoo_bar[] = {" foo", "bar"};
static const char *const argv_backslashfoo_bar[] = {"\\foo", "bar"};
static const char *const argv_quotmarkfoo_bar[] = {"\"foo", "bar"};
static const char *const argv_foospace_bar[] = {"foo ", "bar"};
static const char *const argv_foobackslash_bar[] = {"foo\\", "bar"};
static const char *const argv_fooquotmark_bar[] = {"foo\"", "bar"};
static const char *const argv_spacefoospace_bar[] = {" foo ", "bar"};
static const char *const argv_backslashfoobackslash_bar[] = {"\\foo\\", "bar"};
static const char *const argv_quotmarkfooquotmark_bar[] = {"\"foo\"", "bar"};
static const char *const argv_foo_spacebar[] = {"foo", " bar"};
static const char *const argv_foo_backslashbar[] = {"foo", "\\bar"};
static const char *const argv_foo_quotmarkbar[] = {"foo", "\"bar"};
static const char *const argv_foo_barspace[] = {"foo", "bar "};
static const char *const argv_foo_barbackslash[] = {"foo", "bar\\"};
static const char *const argv_foo_barquotmark[] = {"foo", "bar\""};
static const char *const argv_foo_spacebarspace[] = {"foo", " bar "};
static const char *const argv_foo_backslashbarbackslash[] = {"foo", "\\bar\\"};
static const char *const argv_foo_quotmarkbarquotmark[] = {"foo", "\"bar\""};

int main()
{
    test("",             0, 0, true, "", 0, NULL);
    test("   ",          0, 0, true, "", 0, NULL);
    test("foo",          0, 0, true, "", 1, argv_foo);
    test("foo bar",      0, 0, true, "", 2, argv_foo_bar);
    test(" foo bar",     0, 0, true, "", 2, argv_foo_bar);
    test("foo bar ",     0, 0, true, "", 2, argv_foo_bar);
    test(" foo bar ",    0, 0, true, "", 2, argv_foo_bar);
    test("foo  bar",     0, 0, true, "", 2, argv_foo_bar);
    test("  foo  bar",   0, 0, true, "", 2, argv_foo_bar);
    test("foo  bar  ",   0, 0, true, "", 2, argv_foo_bar);
    test("  foo  bar  ", 0, 0, true, "", 2, argv_foo_bar);
    test("foo bar car",  0, 0, true, "", 3, argv_foo_bar_car);

    test("\"\"",                    0, 0, true, "", 1, argv_empty);
    test("\"\" \"\"",               0, 0, true, "", 2, argv_empty_X2);
    test("\"\" \"\" \"\"",          0, 0, true, "", 3, argv_empty_X3);
    test("\"foo\"",                 0, 0, true, "", 1, argv_foo);
    test("\"foo\" \"bar\"",         0, 0, true, "", 2, argv_foo_bar);
    test(" \"foo\" \"bar\"",        0, 0, true, "", 2, argv_foo_bar);
    test("\"foo\" \"bar\" ",        0, 0, true, "", 2, argv_foo_bar);
    test(" \"foo\" \"bar\" ",       0, 0, true, "", 2, argv_foo_bar);
    test("\"foo\"  \"bar\"",        0, 0, true, "", 2, argv_foo_bar);
    test("\"foo\"  \"bar\"  ",      0, 0, true, "", 2, argv_foo_bar);
    test("  \"foo\"  \"bar\"",      0, 0, true, "", 2, argv_foo_bar);
    test("  \"foo\"  \"bar\"  ",    0, 0, true, "", 2, argv_foo_bar);
    test("\"foo\" \"bar\" \"car\"", 0, 0, true, "", 3, argv_foo_bar_car);

    test("foo bar car", 3, 0,  true, "", 3, argv_foo_bar_car);
    test("foo bar car", 0, 12, true, "", 3, argv_foo_bar_car);
    test("foo bar car", 3, 12, true, "", 3, argv_foo_bar_car);

    test("foo bar car", 2, 0,  false, "too many args",   0, NULL);
    test("foo bar car", 0, 11, false, "buffer overflow", 0, NULL);
    test("foo bar car", 2, 11, false, "too many args",   0, NULL);

    test("\"foo\" \"bar\" \"car\"", 3, 0,  true, "", 3, argv_foo_bar_car);
    test("\"foo\" \"bar\" \"car\"", 0, 12, true, "", 3, argv_foo_bar_car);
    test("\"foo\" \"bar\" \"car\"", 3, 12, true, "", 3, argv_foo_bar_car);

    test("\"foo\" \"bar\" \"car\"", 2, 0,  false, "too many args",   0, NULL);
    test("\"foo\" \"bar\" \"car\"", 0, 11, false, "buffer overflow", 0, NULL);
    test("\"foo\" \"bar\" \"car\"", 2, 11, false, "too many args",   0, NULL);

    test("\\ ",                 0, 0, true, "", 1, argv_space);
    test("\"\\ \"",             0, 0, true, "", 1, argv_space);
    test("\\\\",                0, 0, true, "", 1, argv_backslash);
    test("\"\\\\\"",            0, 0, true, "", 1, argv_backslash);
    test("\\\"",                0, 0, true, "", 1, argv_quotmark);
    test("\"\\\"\"",            0, 0, true, "", 1, argv_quotmark);
    test("foo\\ ",              0, 0, true, "", 1, argv_foospace);
    test("\"foo\\ \"",          0, 0, true, "", 1, argv_foospace);
    test("foo\\\\",             0, 0, true, "", 1, argv_foobackslash);
    test("\"foo\\\\\"",         0, 0, true, "", 1, argv_foobackslash);
    test("foo\\\"",             0, 0, true, "", 1, argv_fooquotmark);
    test("\"foo\\\"\"",         0, 0, true, "", 1, argv_fooquotmark);
    test("\\ foo",              0, 0, true, "", 1, argv_spacefoo);
    test("\"\\ foo\"",          0, 0, true, "", 1, argv_spacefoo);
    test("\\\\foo",             0, 0, true, "", 1, argv_backslashfoo);
    test("\"\\\\foo\"",         0, 0, true, "", 1, argv_backslashfoo);
    test("\\\"foo",             0, 0, true, "", 1, argv_quotmarkfoo);
    test("\"\\\"foo\"",         0, 0, true, "", 1, argv_quotmarkfoo);
    test("\\ foo\\ ",           0, 0, true, "", 1, argv_spacefoospace);
    test("\"\\ foo\\ \"",       0, 0, true, "", 1, argv_spacefoospace);
    test("\\\\foo\\\\",         0, 0, true, "", 1, argv_backslashfoobackslash);
    test("\"\\\\foo\\\\\"",     0, 0, true, "", 1, argv_backslashfoobackslash);
    test("\\\"foo\\\"",         0, 0, true, "", 1, argv_quotmarkfooquotmark);
    test("\"\\\"foo\\\"\"",     0, 0, true, "", 1, argv_quotmarkfooquotmark);
    test("foo\\ bar",           0, 0, true, "", 1, argv_foospacebar);
    test("\"foo\\ bar\"",       0, 0, true, "", 1, argv_foospacebar);
    test("foo\\\\bar",          0, 0, true, "", 1, argv_foobackslashbar);
    test("\"foo\\\\bar\"",      0, 0, true, "", 1, argv_foobackslashbar);
    test("foo\\\"bar",          0, 0, true, "", 1, argv_fooquotmarkbar);
    test("\"foo\\\"bar\"",      0, 0, true, "", 1, argv_fooquotmarkbar);
    test("\\ foo bar",          0, 0, true, "", 2, argv_spacefoo_bar);
    test("\"\\ foo\" bar",      0, 0, true, "", 2, argv_spacefoo_bar);
    test("\\\\foo bar",         0, 0, true, "", 2, argv_backslashfoo_bar);
    test("\"\\\\foo\" bar",     0, 0, true, "", 2, argv_backslashfoo_bar);
    test("\\\"foo bar",         0, 0, true, "", 2, argv_quotmarkfoo_bar);
    test("\"\\\"foo\" bar",     0, 0, true, "", 2, argv_quotmarkfoo_bar);
    test("foo\\  bar",          0, 0, true, "", 2, argv_foospace_bar);
    test("\"foo\\ \" bar",      0, 0, true, "", 2, argv_foospace_bar);
    test("foo\\\\ bar",         0, 0, true, "", 2, argv_foobackslash_bar);
    test("\"foo\\\\\" bar",     0, 0, true, "", 2, argv_foobackslash_bar);
    test("foo\\\" bar",         0, 0, true, "", 2, argv_fooquotmark_bar);
    test("\"foo\\\"\" bar",     0, 0, true, "", 2, argv_fooquotmark_bar);
    test("\\ foo\\  bar",       0, 0, true, "", 2, argv_spacefoospace_bar);
    test("\"\\ foo\\ \" bar",   0, 0, true, "", 2, argv_spacefoospace_bar);
    test("\\\\foo\\\\ bar",     0, 0, true, "", 2, argv_backslashfoobackslash_bar);
    test("\"\\\\foo\\\\\" bar", 0, 0, true, "", 2, argv_backslashfoobackslash_bar);
    test("\\\"foo\\\" bar",     0, 0, true, "", 2, argv_quotmarkfooquotmark_bar);
    test("\"\\\"foo\\\"\" bar", 0, 0, true, "", 2, argv_quotmarkfooquotmark_bar);
    test("foo \\ bar",          0, 0, true, "", 2, argv_foo_spacebar);
    test("foo \"\\ bar\"",      0, 0, true, "", 2, argv_foo_spacebar);
    test("foo \\\\bar",         0, 0, true, "", 2, argv_foo_backslashbar);
    test("foo \"\\\\bar\"",     0, 0, true, "", 2, argv_foo_backslashbar);
    test("foo \\\"bar",         0, 0, true, "", 2, argv_foo_quotmarkbar);
    test("foo \"\\\"bar\"",     0, 0, true, "", 2, argv_foo_quotmarkbar);
    test("foo bar\\ ",          0, 0, true, "", 2, argv_foo_barspace);
    test("foo \"bar\\ \"",      0, 0, true, "", 2, argv_foo_barspace);
    test("foo bar\\\\",         0, 0, true, "", 2, argv_foo_barbackslash);
    test("foo \"bar\\\\\"",     0, 0, true, "", 2, argv_foo_barbackslash);
    test("foo bar\\\"",         0, 0, true, "", 2, argv_foo_barquotmark);
    test("foo \"bar\\\"\"",     0, 0, true, "", 2, argv_foo_barquotmark);
    test("foo \\ bar\\ ",       0, 0, true, "", 2, argv_foo_spacebarspace);
    test("foo \"\\ bar\\ \"",   0, 0, true, "", 2, argv_foo_spacebarspace);
    test("foo \\\\bar\\\\",     0, 0, true, "", 2, argv_foo_backslashbarbackslash);
    test("foo \"\\\\bar\\\\\"", 0, 0, true, "", 2, argv_foo_backslashbarbackslash);
    test("foo \\\"bar\\\"",     0, 0, true, "", 2, argv_foo_quotmarkbarquotmark);
    test("foo \"\\\"bar\\\"\"", 0, 0, true, "", 2, argv_foo_quotmarkbarquotmark);

    test("foo\\ bar car",       0, 0, true, "", 2, argv_foospacebar_car);
    test("\"foo bar\" car",     0, 0, true, "", 2, argv_foospacebar_car);
    test("\"foo bar\" \"car\"", 0, 0, true, "", 2, argv_foospacebar_car);
    test("foo bar\\ car",       0, 0, true, "", 2, argv_foo_barspacecar);
    test("foo \"bar car\"",     0, 0, true, "", 2, argv_foo_barspacecar);
    test("\"foo\" \"bar car\"", 0, 0, true, "", 2, argv_foo_barspacecar);

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
        NULL
    );

    test("a",                    1,  0, true,  "",              1, NULL);
    test("a a",                  1,  0, false, "too many args", 0, NULL);
    test("a a ",                 1,  0, false, "too many args", 0, NULL);
    test("a a",                  2,  0, true,  "",              2, NULL);
    test("a a ",                 2,  0, true,  "",              2, NULL);
    test("a a a",                2,  0, false, "too many args", 0, NULL);
    test("a a a ",               2,  0, false, "too many args", 0, NULL);
    test("a a a",                3,  0, true,  "",              3, NULL);
    test("a a a ",               3,  0, true,  "",              3, NULL);
    test("a a a a",              3,  0, false, "too many args", 0, NULL);
    test("a a a a ",             3,  0, false, "too many args", 0, NULL);
    test("a a a a",              4,  0, true,  "",              4, NULL);
    test("a a a a ",             4,  0, true,  "",              4, NULL);
    test("a a a a a",            4,  0, false, "too many args", 0, NULL);
    test("a a a a a ",           4,  0, false, "too many args", 0, NULL);
    test("a a a a a",            5,  0, true,  "",              5, NULL);
    test("a a a a a ",           5,  0, true,  "",              5, NULL);
    test("a a a a a a",          5,  0, false, "too many args", 0, NULL);
    test("a a a a a a ",         5,  0, false, "too many args", 0, NULL);
    test("a a a a a a",          6,  0, true,  "",              6, NULL);
    test("a a a a a a ",         6,  0, true,  "",              6, NULL);

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

    memset(error_msg, 'a', KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX);
    memset(argv,      'a', sizeof(char*) * argv_count_max);
    memset(buffer,    'a', buffer_size);

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
