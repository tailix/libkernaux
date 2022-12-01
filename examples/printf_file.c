#include <kernaux/printf.h>

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

static const char *const data = "foobar";

static char buffer[BUFFER_SIZE];
static size_t buffer_index = 0;

static void my_putchar(const char chr, void *const arg)
{
    assert(arg == data);
    if (buffer_index >= BUFFER_SIZE) abort();
    buffer[buffer_index++] = chr;
}

void example_main()
{
    const int result = kernaux_fprintf(
        my_putchar,
        (void*)data,
        "Hello, %s! Session ID: %u.",
        "Alex",
        123
    );
    assert((size_t)result == strlen(buffer));
    assert(strcmp(buffer, "Hello, Alex! Session ID: 123.") == 0);
}
