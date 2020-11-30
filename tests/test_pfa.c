#include <kernaux/pfa.h>

#include <assert.h>

int main()
{
    struct KernAux_PFA pfa;

    assert(KernAux_PFA_initialize_start(&pfa));

    assert(KernAux_PFA_initialize_add_zone(
        &pfa,
        "foo",
        0,
        16 * 1024 * 1024 - 1
    ));

    assert(KernAux_PFA_initialize_add_zone(
        &pfa,
        "bar",
        16 * 1024 * 1024,
        896 * 1024 * 1024 - 1
    ));

    assert(KernAux_PFA_initialize_add_zone(
        &pfa,
        "car",
        896 * 1024 * 1024,
        (unsigned long long)4 * 1024 * 1024 * 1024 - 1
    ));

    assert(KernAux_PFA_initialize_finish(&pfa));

    return 0;
}
