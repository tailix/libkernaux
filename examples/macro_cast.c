#include <kernaux/macro.h>

#include <assert.h>
#include <stdint.h>

void example_main()
{
    const uint32_t value = 123;

    // const unsigned long ul = (unsigned long)value;
    KERNAUX_CAST_CONST(unsigned long, ul, value);
    assert(ul == 123);

    // unsigned long long ull = (unsigned long long)value;
    KERNAUX_CAST_VAR(unsigned long long, ull, value);
    assert(ull == 123);

    // const [signed] long sl = ([signed] long)value;
    KERNAUX_CAST_CONST(long, sl, value);
    assert(sl == 123);

    // [signed] long long sll = ([signed] long long)value;
    KERNAUX_CAST_VAR(long long, sll, value);
    assert(sll == 123);
}
