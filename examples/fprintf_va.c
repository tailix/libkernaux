#define KERNAUX_ACCESS_PROTECTED

#include <kernaux/generic/file.h>
#include <kernaux/printf.h>

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

static char buffer[BUFFER_SIZE];
static size_t buffer_index = 0;

static int my_putc(__attribute__((unused)) void *const file, unsigned char c)
{
    if (buffer_index >= BUFFER_SIZE) abort();
    buffer[buffer_index++] = c;
    return 1;
}

static const struct KernAux_File file = {
    .putc = my_putc,
    .puts = NULL,
    .write = NULL,
};

static int my_printf(const char *const format, ...)
{
    va_list va;
    va_start(va, format);
    const int result = kernaux_vfprintf(&file, format, va);
    va_end(va);
    return result;
}

void example_main()
{
    const int result = my_printf("Hello, %s! Session ID: %u.", "Alex", 123);
    assert((size_t)result == strlen(buffer));
    assert(strcmp(buffer, "Hello, Alex! Session ID: 123.") == 0);
}
