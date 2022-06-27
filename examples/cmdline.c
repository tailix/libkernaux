#include <kernaux/cmdline.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

#define ARG_COUNT_MAX 100
#define BUFFER_SIZE 4096

static const char *const cmdline = "foo bar\\ baz \"car cdr\"";

void example_main()
{
    char error_msg[KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX];
    size_t argc;
    char *argv[ARG_COUNT_MAX];
    char buffer[BUFFER_SIZE];

    assert(kernaux_cmdline(
        cmdline,
        error_msg,
        &argc,
        argv,
        buffer,
        ARG_COUNT_MAX,
        BUFFER_SIZE
    ));

    assert(strcmp(error_msg, "") == 0);
    assert(argc == 3);
    assert(strcmp(argv[0], "foo") == 0);
    assert(strcmp(argv[1], "bar baz") == 0);
    assert(strcmp(argv[2], "car cdr") == 0);
}
