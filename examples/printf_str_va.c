#include <kernaux/printf.h>

#include <assert.h>
#include <string.h>

#define BUFFER_SIZE 1024

static char buffer[BUFFER_SIZE];

static int my_snprintf(const char *const format, ...)
{
    va_list va;
    va_start(va, format);
    const int result = kernaux_vsnprintf(buffer, sizeof(buffer), format, va);
    va_end(va);
    return result;
}

void example_main()
{
    const int result = my_snprintf("Hello, %s! Session ID: %u.", "Alex", 123);
    assert((size_t)result == strlen(buffer));
    assert(strcmp(buffer, "Hello, Alex! Session ID: 123.") == 0);
}
