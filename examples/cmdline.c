#include <kernaux/cmdline.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>

static const unsigned int ARGV_COUNT_MAX = 100;
static const unsigned int ARG_SIZE_MAX = 4096;

static const char *const cmdline = "foo bar\\ car";

int main()
{
    char error_msg[KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX];
    unsigned int argc;
    char *argv[ARGV_COUNT_MAX];
    char buffer[ARGV_COUNT_MAX * ARG_SIZE_MAX];

    assert(kernaux_cmdline_parse(
        cmdline,
        error_msg,
        &argc,
        argv,
        buffer,
        ARGV_COUNT_MAX,
        ARG_SIZE_MAX
    ));

    assert(strcmp(error_msg, "") == 0);
    assert(argc == 2);
    assert(strcmp(argv[0], "foo") == 0);
    assert(strcmp(argv[1], "bar car") == 0);

    printf("OK!\n");

    return 0;
}
