#include <kernaux/printf.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

static char buffer[BUFFER_SIZE];
static unsigned int buffer_index;

static void test_putchar(const char chr)
{
    if (buffer_index >= BUFFER_SIZE) {
        printf("Buffer overflow!\n");
        abort();
    }

    buffer[buffer_index++] = chr;
}

static void test(const char *const expected, const char *const format, ...)
{
    memset(buffer, '\0', sizeof(buffer));
    buffer_index = 0;
    va_list va;
    va_start(va, format);
    kernaux_printf_va(test_putchar, format, va);
    va_end(va);
    assert(strcmp(expected, buffer) == 0);
}

int main()
{
    memset(buffer, '\0', sizeof(buffer));
    buffer_index = 0;
    kernaux_printf(test_putchar, "Hello, World!");
    assert(strcmp("Hello, World!", buffer) == 0);

    test("", "");
    test("Hello, World!", "Hello, World!");
    test("Hello, Alex!", "Hello, %s!", "Alex");
    test("Hello, Alex!", "Hello, %c%c%c%c!", 'A', 'l', 'e', 'x');
    test("%", "%%");
    test("123", "%u", 123);

    return 0;
}
