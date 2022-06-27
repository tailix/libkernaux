#include <kernaux/cmdline.h>
#include <kernaux/memory_file.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

static const char *const cmdline = "foo bar\\ baz \"car cdr\"";

static char buffer[4096];

void example_main()
{
    char error_msg[KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX];
    size_t argc;
    struct KernAux_MemoryFile memory_file =
        KernAux_MemoryFile_create(buffer, sizeof(buffer), NULL);

    assert(kernaux_cmdline_file(
        cmdline,
        error_msg,
        &argc,
        &memory_file.file
    ));

    assert(strcmp(error_msg, "") == 0);
    assert(argc == 3);
    assert(strcmp(&buffer[0], "foo") == 0);
    assert(strcmp(&buffer[4], "bar baz") == 0);
    assert(strcmp(&buffer[12], "car cdr") == 0);
}
