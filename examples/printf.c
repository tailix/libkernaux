#include <kernaux/printf.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

static char buffer[BUFFER_SIZE];
static unsigned int buffer_index = 0;

static void my_putchar(const char chr)
{
    if (buffer_index >= BUFFER_SIZE) abort();
    buffer[buffer_index++] = chr;
}

int main()
{
    kernaux_printf(my_putchar, "Hello, %s! Session ID: %u.", "Alex", 123);
    assert(strcmp(buffer, "Hello, Alex! Session ID: 123.") == 0);
    return 0;
}
