#include <kernaux/macro.h>

#include <stdint.h>

KERNAUX_STATIC_TEST(uint8_t_size,  sizeof(uint8_t)  == 1);
KERNAUX_STATIC_TEST(uint16_t_size, sizeof(uint16_t) == 2);
KERNAUX_STATIC_TEST(uint32_t_size, sizeof(uint32_t) == 4);
KERNAUX_STATIC_TEST(uint64_t_size, sizeof(uint64_t) == 8);

#include <kernaux/macro/packing_start.run>

struct Foo {
    uint8_t a;
    uint32_t b;
} KERNAUX_PACKED;

KERNAUX_STATIC_TEST_STRUCT_SIZE(Foo, 5);

union Bar {
    uint8_t a;
    uint16_t b;
} KERNAUX_PACKED;

KERNAUX_STATIC_TEST_UNION_SIZE(Bar, 2);

#include <kernaux/macro/packing_end.run>

void example_main() {}
