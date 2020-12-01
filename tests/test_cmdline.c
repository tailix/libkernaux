#include <kernaux/cmdline.h>

#include <assert.h>
#include <string.h>

static const unsigned int ARGV_COUNT_MAX = 1024;
static const unsigned int ARG_SIZE_MAX = 4096;

int main()
{
    char error_msg[KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX];
    unsigned int argc = 1234;
    char *argv[ARGV_COUNT_MAX];
    char buffer[ARGV_COUNT_MAX * ARG_SIZE_MAX];

    assert(kernaux_cmdline_parse(
        "",
        error_msg,
        &argc,
        argv,
        buffer,
        ARGV_COUNT_MAX,
        ARG_SIZE_MAX
    ));

    assert(strcmp(error_msg, "") == 0);
    assert(argc == 0);

    for (unsigned int index = 0; index < ARGV_COUNT_MAX; ++index) {
        assert(argv[index] == KERNAUX_NULL);
    }

    return 0;
}
