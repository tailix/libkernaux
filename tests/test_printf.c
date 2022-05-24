/**
 * Copyright (c) 2014-2019 Marco Paland <info@paland.com>
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/printf.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

static const char *const data = "foobar";

static char buffer[BUFFER_SIZE];
static size_t buffer_index;

static void test_putchar(const char chr, void *const arg)
{
    assert(arg == data);

    if (buffer_index >= BUFFER_SIZE) {
        printf("Buffer overflow!\n");
        abort();
    }

    buffer[buffer_index++] = chr;
}

static void test(const char *const expected, const char *const format, ...)
{
    va_list va;
    int result;

    memset(buffer, '\0', sizeof(buffer));
    buffer_index = 0;
    va_start(va, format);
    result = kernaux_vprintf(test_putchar, (char*)data, format, va);
    va_end(va);
    assert((size_t)result == strlen(expected));
    assert(strcmp(expected, buffer) == 0);

    memset(buffer, '\0', sizeof(buffer));
    buffer_index = 0;
    va_start(va, format);
    result = kernaux_vsnprintf(buffer, sizeof(buffer), format, va);
    va_end(va);
    assert((size_t)result == strlen(expected));
    assert(strcmp(expected, buffer) == 0);
}

int main()
{
    memset(buffer, '\0', sizeof(buffer));
    buffer_index = 0;
    kernaux_printf(test_putchar, (char*)data, "Hello, World!");
    assert(strcmp("Hello, World!", buffer) == 0);

    // - flag
    // ...
    test("42",              "%0-d",      42);
    test("-42",             "%0-d",     -42);
    test("42   ",           "%0-5d",     42);
    test("-42  ",           "%0-5d",    -42);
    test("42             ", "%0-15d",    42);
    test("-42            ", "%0-15d",   -42);
#ifdef ENABLE_FLOAT
    test("-4.200e+01     ", "%0-15.3e", -42.0);
    test("-42.0          ", "%0-15.3g", -42.0);
#else
    test("e",               "%0-15.3e", -42.0);
    test("g",               "%0-15.3g", -42.0);
#endif

    // width *20
    test("               Hello", "%*s", 20, "Hello");
    test("                1024", "%*d", 20, 1024);
    test("               -1024", "%*d", 20, -1024);
    test("                1024", "%*i", 20, 1024);
    test("               -1024", "%*i", 20, -1024);
    test("                1024", "%*u", 20, 1024);
    test("          4294966272", "%*u", 20, 4294966272);
    test("                 777", "%*o", 20, 511);
    test("         37777777001", "%*o", 20, 4294966785);
    test("            1234abcd", "%*x", 20, 305441741);
    test("            edcb5433", "%*x", 20, 3989525555);
    test("            1234ABCD", "%*X", 20, 305441741);
    test("            EDCB5433", "%*X", 20, 3989525555);
    test("                   x", "%*c", 20, 'x');

    return 0;
}
