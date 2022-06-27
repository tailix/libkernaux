#include <kernaux/cmdline.h>
#include <kernaux/memory_file.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

#define ARGV_COUNT_MAX 100
#define BUFFER_SIZE 4096

static const char *const cmdline = "foo bar\\ baz \"car cdr\"";

void example_main()
{
    char error_msg[KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX];
    size_t argc;
    size_t argv[ARGV_COUNT_MAX];
    char buffer[BUFFER_SIZE];

    struct KernAux_MemoryFile memory_file =
        KernAux_MemoryFile_create(buffer, BUFFER_SIZE, NULL);

    assert(kernaux_cmdline_file(
        cmdline,
        error_msg,
        &argc,
        &memory_file.file,
        argv,
        ARGV_COUNT_MAX
    ));

    assert(strcmp(error_msg, "") == 0);
    assert(argc == 3);
    assert(strcmp(&buffer[argv[0]], "foo") == 0);
    assert(strcmp(&buffer[argv[1]], "bar baz") == 0);
    assert(strcmp(&buffer[argv[2]], "car cdr") == 0);
}
