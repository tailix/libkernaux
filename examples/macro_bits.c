#include <kernaux/macro.h>

#include <assert.h>

void example_main()
{
    assert(KERNAUX_BITS(0)    == 0x1);
    assert(KERNAUX_BITS(31)   == 0x80000000);

    assert(KERNAUX_BITS8(0)   == 0x1);
    assert(KERNAUX_BITS8(7)   == 0x80);

    assert(KERNAUX_BITS16(0)  == 0x1);
    assert(KERNAUX_BITS16(15) == 0x8000);

    assert(KERNAUX_BITS32(0)  == 0x1);
    assert(KERNAUX_BITS32(31) == 0x80000000);

    assert(KERNAUX_BITS64(0)  == 0x1);
    assert(KERNAUX_BITS64(63) == 0x8000000000000000);
}
