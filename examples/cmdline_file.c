#include <kernaux/cmdline.h>
#include <kernaux/memory_file.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

#define ARG_COUNT_MAX 100
#define BUFFER_SIZE 4096

static const char *const cmdline = "foo bar\\ baz \"car cdr\"";

static void with_args_indices_array();
static void without_args_indices_array();

void example_main()
{
    with_args_indices_array();
    without_args_indices_array();
}

void with_args_indices_array()
{
    char error_msg[KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX];
    size_t argc;
    size_t argv[ARG_COUNT_MAX];
    char buffer[BUFFER_SIZE];

    struct KernAux_MemoryFile memory_file =
        KernAux_MemoryFile_create(buffer, BUFFER_SIZE, NULL);

    assert(kernaux_cmdline_file(
        cmdline,
        error_msg,
        &argc,
        &memory_file.file,
        argv,
        ARG_COUNT_MAX
    ));

    assert(strcmp(error_msg, "") == 0);
    assert(argc == 3);
    assert(strcmp(&buffer[argv[0]], "foo") == 0);
    assert(strcmp(&buffer[argv[1]], "bar baz") == 0);
    assert(strcmp(&buffer[argv[2]], "car cdr") == 0);
}

void without_args_indices_array()
{
    char error_msg[KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX];
    size_t argc;
    char buffer[BUFFER_SIZE];

    struct KernAux_MemoryFile memory_file =
        KernAux_MemoryFile_create(buffer, BUFFER_SIZE, NULL);

    assert(kernaux_cmdline_file(
        cmdline,
        error_msg,
        &argc,
        &memory_file.file,
        NULL,
        0
    ));

    assert(strcmp(error_msg, "") == 0);
    assert(argc == 3);
    assert(strcmp(&buffer[0], "foo") == 0);
    assert(strcmp(&buffer[4], "bar baz") == 0);
    assert(strcmp(&buffer[12], "car cdr") == 0);
}
