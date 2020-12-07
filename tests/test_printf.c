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
    test("%%", "%%%%");
    test("%%%", "%%%%%%");
    test("123", "%u", 123);
    test("123456", "%u%u", 123, 456);
    test("foo", "%s", "foo");
    test("foobar", "%s%s", "foo", "bar");
    test("a", "%c", 'a');
    test("ab", "%c%c", 'a', 'b');
    test("abc", "%c%c%c", 'a', 'b', 'c');
    test("%123fooa", "%%%u%s%c", 123, "foo", 'a');
    test("%123afoo", "%%%u%c%s", 123, 'a', "foo");
    test("%a123foo", "%%%c%u%s", 'a', 123, "foo");
    test("%afoo123", "%%%c%s%u", 'a', "foo", 123);
    test("%foo123a", "%%%s%u%c", "foo", 123, 'a');
    test("%fooa123", "%%%s%c%u", "foo", 'a', 123);
    test("123%fooa", "%u%%%s%c", 123, "foo", 'a');
    test("123%afoo", "%u%%%c%s", 123, 'a', "foo");
    test("a%123foo", "%c%%%u%s", 'a', 123, "foo");
    test("a%foo123", "%c%%%s%u", 'a', "foo", 123);
    test("foo%123a", "%s%%%u%c", "foo", 123, 'a');
    test("foo%a123", "%s%%%c%u", "foo", 'a', 123);
    test("123foo%a", "%u%s%%%c", 123, "foo", 'a');
    test("123a%foo", "%u%c%%%s", 123, 'a', "foo");
    test("a123%foo", "%c%u%%%s", 'a', 123, "foo");
    test("afoo%123", "%c%s%%%u", 'a', "foo", 123);
    test("foo123%a", "%s%u%%%c", "foo", 123, 'a');
    test("fooa%123", "%s%c%%%u", "foo", 'a', 123);
    test("123fooa%", "%u%s%c%%", 123, "foo", 'a');
    test("123afoo%", "%u%c%s%%", 123, 'a', "foo");
    test("a123foo%", "%c%u%s%%", 'a', 123, "foo");
    test("afoo123%", "%c%s%u%%", 'a', "foo", 123);
    test("foo123a%", "%s%u%c%%", "foo", 123, 'a');
    test("fooa123%", "%s%c%u%%", "foo", 'a', 123);

    return 0;
}
