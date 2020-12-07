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

static void my_printf(const char *const format, ...)
{
    va_list va;
    va_start(va, format);
    kernaux_printf_va(my_putchar, format, va);
    va_end(va);
}

int main()
{
    my_printf("Hello, %s! Session ID: %u.", "Alex", 123);
    assert(strcmp(buffer, "Hello, Alex! Session ID: 123.") == 0);
    return 0;
}
