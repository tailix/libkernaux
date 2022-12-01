#include <kernaux/macro.h>

#include <assert.h>
#include <string.h>

struct Foo {
    const char *hello;
};

struct Bar {
    unsigned char a;
    unsigned int b;
    struct Foo foo;
    unsigned short c;
};

static const struct Bar bar = {
    .a = 143,
    .b = 820794098,
    .foo = {
        .hello = "Hello, World!",
    },
    .c = 10981,
};

void example_main()
{
    const struct Bar *const bar_ptr =
        KERNAUX_CONTAINER_OF(&bar.foo, struct Bar, foo);

    assert(bar_ptr->a == 143);
    assert(bar_ptr->b == 820794098);
    assert(strcmp(bar_ptr->foo.hello, "Hello, World!") == 0);
    assert(bar_ptr->c == 10981);
}
