#include <kernaux/cmdline.h>
#include <kernaux/generic/file.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

static const char *const cmdline = "foo bar\\ baz \"car cdr\"";

static int file_putc(void *file, unsigned char c);

static char buffer[4096];
static size_t file_pos = 0;

static struct KernAux_File file = {
    .putc = file_putc,
    .puts = NULL,
    .write = NULL,
};

int file_putc(void *file, unsigned char c)
{
    if (file_pos >= sizeof(buffer)) return KERNAUX_EOF;
    buffer[file_pos++] = c;
    return c;
}

void example_main()
{
    char error_msg[KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX];
    size_t argc;

    assert(kernaux_cmdline_file(
        cmdline,
        error_msg,
        &argc,
        &file
    ));

    assert(strcmp(error_msg, "") == 0);
    assert(argc == 3);
    assert(strcmp(&buffer[0], "foo") == 0);
    assert(strcmp(&buffer[4], "bar baz") == 0);
    assert(strcmp(&buffer[12], "car cdr") == 0);
}
