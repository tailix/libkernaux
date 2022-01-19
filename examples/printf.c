#include <kernaux/printf.h>

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

static char buffer[BUFFER_SIZE];
static size_t buffer_index = 0;

static void my_putchar(const char chr, void *arg __attribute__((unused)))
{
    if (buffer_index >= BUFFER_SIZE) abort();
    buffer[buffer_index++] = chr;
}

int main()
{
    kernaux_printf(my_putchar, NULL, "Hello, %s! Session ID: %u.", "Alex", 123);
    assert(strcmp(buffer, "Hello, Alex! Session ID: 123.") == 0);
    return 0;
}
