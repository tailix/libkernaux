#include <kernaux/macro.h>

#include <assert.h>
#include <stdint.h>

struct Foo {
    uint8_t a;
    uint32_t b;
};

#include <kernaux/macro/packing_start.run>

struct Bar {
    uint8_t a;
    uint32_t b;
}
KERNAUX_PACKED;

#include <kernaux/macro/packing_end.run>

void example_main()
{
    assert(sizeof(struct Foo) > 5);
    assert(sizeof(struct Bar) == 5);
}
