//==============
// my_display.c
//==============

// To not always use macro "KERNAUX_PROTECTED_FIELD" around the names of
// structure fields you may define "KERNAUX_ACCESS_PROTECTED" before including
// any other headers, but ONLY in the file where you implement a generic type.
//
#define KERNAUX_ACCESS_PROTECTED

//==============
// my_display.h
//==============

#include <kernaux/generic/display.h>
#include <stddef.h>

typedef struct MyDisplay {
    struct KernAux_Display display;
    char *buffer, *cursor;
    size_t capacity;
} *MyDisplay;

struct MyDisplay MyDisplay_create();

//==============
// my_display.c
//==============

#include <assert.h>
#include <kernaux/generic/display.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAP_FREE (1024)
#define CAP_INCR (2 * (CAP_FREE))

static void MyDisplay_putc(void *display, char c);
void MyDisplay_vprintf(void *display, const char *format, va_list va);

static void MyDisplay_realloc(MyDisplay my_display);

struct MyDisplay MyDisplay_create()
{
    char *const buffer = malloc(CAP_INCR);
    if (!buffer) abort();

    return (struct MyDisplay){
        .display = {
            .putc = MyDisplay_putc,
            .vprintf = MyDisplay_vprintf,
        },
        .buffer = buffer,
        .cursor = buffer,
        .capacity = CAP_INCR,
    };
}

void MyDisplay_putc(void *display, char c)
{
    const MyDisplay my_display = display;
    MyDisplay_realloc(my_display);
    *(my_display->cursor++) = c;
}

void MyDisplay_vprintf(void *display, const char *format, va_list va)
{
    const MyDisplay my_display = display;
    MyDisplay_realloc(my_display);
    size_t left =
        my_display->buffer + my_display->capacity - my_display->cursor;
    const int delta = vsnprintf(my_display->cursor, left, format, va);
    if (delta < 0) abort();
    my_display->cursor += delta;
}

void MyDisplay_realloc(const MyDisplay my_display)
{
    size_t left =
        my_display->buffer + my_display->capacity - my_display->cursor;

    if (left < CAP_FREE) {
        my_display->buffer =
            realloc(my_display->buffer, my_display->capacity + CAP_INCR);
        if (!my_display->buffer) abort();
        my_display->capacity += CAP_INCR;
    }
}

//========
// main.c
//========

void example_main()
{
    struct MyDisplay my_display = MyDisplay_create();

    KernAux_Display_putc(&my_display.display, '@');
    KernAux_Display_print(&my_display.display, "print");
    KernAux_Display_println(&my_display.display, "println");
    KernAux_Display_write(&my_display.display, "write!!!", 5);
    KernAux_Display_writeln(&my_display.display, "writeln!!!", 7);
    KernAux_Display_printf(&my_display.display, "printf(%d)", 123);
    KernAux_Display_printlnf(&my_display.display, "printfln(%d)", 123);

    assert(
        strcmp(
            my_display.buffer,
            "@printprintln\nwritewriteln\nprintf(123)printfln(123)\n"
        ) == 0
    );
}
