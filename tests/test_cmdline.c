#include <kernaux/cmdline.h>

#include <assert.h>
#include <stdbool.h>
#include <string.h>

static const unsigned int ARGV_COUNT_MAX = 100;
static const unsigned int ARG_SIZE_MAX = 4096;

static void test(
    const char *cmdline,
    unsigned int argv_count_max,
    unsigned int arg_size_max,

    bool expected_result,
    const char *expected_error_msg,
    unsigned int expected_argc,
    const char *const *const expected_argv
);

static const char *const argv0[] = {};

static const char *const argv_foo[] = {"foo"};

static const char *const argv_foo_bar[] = {"foo", "bar"};

static const char *const argv_foo_bar_car[] = {"foo", "bar", "car"};

int main()
{
    test("", 0, 0, true, "", 0, argv0);
    test("   ", 0, 0, true, "", 0, argv0);
    test("foo", 0, 0, true, "", 1, argv_foo);
    test("foo bar", 0, 0, true, "", 2, argv_foo_bar);
    test(" foo bar", 0, 0, true, "", 2, argv_foo_bar);
    test("foo bar ", 0, 0, true, "", 2, argv_foo_bar);
    test(" foo bar ", 0, 0, true, "", 2, argv_foo_bar);
    test("foo  bar", 0, 0, true, "", 2, argv_foo_bar);
    test("  foo  bar", 0, 0, true, "", 2, argv_foo_bar);
    test("foo  bar  ", 0, 0, true, "", 2, argv_foo_bar);
    test("  foo  bar  ", 0, 0, true, "", 2, argv_foo_bar);
    test("foo bar car", 0, 0, true, "", 3, argv_foo_bar_car);

    test("foo bar car", 3, 4, true, "", 3, argv_foo_bar_car);

    test("foo bar car", 2, 0, false, "too many args", 0, argv0);
    test("foo bar car", 0, 3, false, "arg too long", 0, argv0);

    return 0;
}

void test(
    const char *const cmdline,
    unsigned int argv_count_max,
    unsigned int arg_size_max,

    const bool expected_result,
    const char *const expected_error_msg,
    unsigned int expected_argc,
    const char *const *const expected_argv
) {
    if (argv_count_max == 0) {
        argv_count_max = ARGV_COUNT_MAX;
    }

    if (arg_size_max == 0) {
        arg_size_max = ARG_SIZE_MAX;
    }

    char error_msg[KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX];
    unsigned int argc = 1234;
    char *argv[argv_count_max];
    char buffer[argv_count_max * arg_size_max];

    assert(
        kernaux_cmdline_parse(
            cmdline,
            error_msg,
            &argc,
            argv,
            buffer,
            argv_count_max,
            arg_size_max
        ) == !!expected_result
    );

    assert(strcmp(error_msg, expected_error_msg) == 0);
    assert(argc == expected_argc);

    for (unsigned int index = 0; index < argc; ++index) {
        assert(strcmp(argv[index], expected_argv[index]) == 0);
    }

    for (unsigned int index = argc; index < argv_count_max; ++index) {
        assert(argv[index] == KERNAUX_NULL);
    }
}
