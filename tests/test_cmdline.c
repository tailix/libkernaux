#include <kernaux/cmdline.h>

#include <assert.h>
#include <string.h>

static const unsigned int ARGV_COUNT_MAX = 100;
static const unsigned int ARG_SIZE_MAX = 4096;

static void test(
    const char *cmdline,
    unsigned int argv_count_max,
    unsigned int arg_size_max,

    kernaux_bool expected_result,
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
    test(
        "",
        ARGV_COUNT_MAX,
        ARG_SIZE_MAX,

        KERNAUX_TRUE,
        "",
        0,
        argv0
    );

    test(
        "   ",
        ARGV_COUNT_MAX,
        ARG_SIZE_MAX,

        KERNAUX_TRUE,
        "",
        0,
        argv0
    );

    test(
        "foo",
        ARGV_COUNT_MAX,
        ARG_SIZE_MAX,

        KERNAUX_TRUE,
        "",
        1,
        argv_foo
    );

    test(
        "foo bar",
        ARGV_COUNT_MAX,
        ARG_SIZE_MAX,

        KERNAUX_TRUE,
        "",
        2,
        argv_foo_bar
    );

    test(
        " foo bar",
        ARGV_COUNT_MAX,
        ARG_SIZE_MAX,

        KERNAUX_TRUE,
        "",
        2,
        argv_foo_bar
    );

    test(
        "foo bar ",
        ARGV_COUNT_MAX,
        ARG_SIZE_MAX,

        KERNAUX_TRUE,
        "",
        2,
        argv_foo_bar
    );

    test(
        " foo bar ",
        ARGV_COUNT_MAX,
        ARG_SIZE_MAX,

        KERNAUX_TRUE,
        "",
        2,
        argv_foo_bar
    );

    test(
        "foo  bar",
        ARGV_COUNT_MAX,
        ARG_SIZE_MAX,

        KERNAUX_TRUE,
        "",
        2,
        argv_foo_bar
    );

    test(
        "  foo  bar",
        ARGV_COUNT_MAX,
        ARG_SIZE_MAX,

        KERNAUX_TRUE,
        "",
        2,
        argv_foo_bar
    );

    test(
        "foo  bar  ",
        ARGV_COUNT_MAX,
        ARG_SIZE_MAX,

        KERNAUX_TRUE,
        "",
        2,
        argv_foo_bar
    );

    test(
        "  foo  bar  ",
        ARGV_COUNT_MAX,
        ARG_SIZE_MAX,

        KERNAUX_TRUE,
        "",
        2,
        argv_foo_bar
    );

    test(
        "foo bar car",
        ARGV_COUNT_MAX,
        ARG_SIZE_MAX,

        KERNAUX_TRUE,
        "",
        3,
        argv_foo_bar_car
    );

    return 0;
}

void test(
    const char *const cmdline,
    const unsigned int argv_count_max,
    const unsigned int arg_size_max,

    const kernaux_bool expected_result,
    const char *const expected_error_msg,
    unsigned int expected_argc,
    const char *const *const expected_argv
) {
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

    for (unsigned int index = argc; index < ARGV_COUNT_MAX; ++index) {
        assert(argv[index] == KERNAUX_NULL);
    }
}
