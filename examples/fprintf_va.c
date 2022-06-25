#include <kernaux/printf.h>

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

static const char *const data = "foobar";

static char buffer[BUFFER_SIZE];
static size_t buffer_index = 0;

static void my_putchar(const char chr, void *arg)
{
    assert(arg == data);
    if (buffer_index >= BUFFER_SIZE) abort();
    buffer[buffer_index++] = chr;
}

static int my_printf(const char *const format, ...)
{
    va_list va;
    va_start(va, format);
    struct KernAux_OldFile file = KernAux_OldFile_create(my_putchar);
    const int result = kernaux_vfprintf(&file, (char*)data, format, va);
    va_end(va);
    return result;
}

void example_main()
{
    const int result = my_printf("Hello, %s! Session ID: %u.", "Alex", 123);
    assert((size_t)result == strlen(buffer));
    assert(strcmp(buffer, "Hello, Alex! Session ID: 123.") == 0);
}
