#include <kernaux/cmdline.h>

#include <assert.h>
#include <string.h>

static const size_t ARGV_COUNT_MAX = 100;
static const size_t ARG_SIZE_MAX = 4096;

static const char *const cmdline = "foo bar\\ baz \"car cdr\"";

int main()
{
    char error_msg[KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX];
    size_t argc;
    char *argv[ARGV_COUNT_MAX];
    char buffer[ARGV_COUNT_MAX * ARG_SIZE_MAX];

    assert(kernaux_cmdline(
        cmdline,
        error_msg,
        &argc,
        argv,
        buffer,
        ARGV_COUNT_MAX,
        ARG_SIZE_MAX
    ));

    assert(strcmp(error_msg, "") == 0);
    assert(argc == 3);
    assert(strcmp(argv[0], "foo") == 0);
    assert(strcmp(argv[1], "bar baz") == 0);
    assert(strcmp(argv[2], "car cdr") == 0);

    return 0;
}
