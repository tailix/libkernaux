#include <kernaux/pfa.h>

#include <assert.h>

int main()
{
    struct KernAux_PFA pfa;

    KernAux_PFA_initialize(&pfa);

    for (unsigned int index = 0; index < KERNAUX_PFA_PAGES_COUNT_MAX; ++index) {
        assert(pfa.pages[index] == KERNAUX_FALSE);
    }

    KernAux_PFA_mark_available(&pfa, 0, 654335);
    KernAux_PFA_mark_available(&pfa, 1048576, 134086655);

    for (unsigned int index = 0; index < 159; ++index) {
        assert(pfa.pages[index] == KERNAUX_TRUE);
    }

    for (unsigned int index = 159; index < 256; ++index) {
        assert(pfa.pages[index] == KERNAUX_FALSE);
    }

    for (unsigned int index = 256; index < 32736; ++index) {
        assert(pfa.pages[index] == KERNAUX_TRUE);
    }

    for (
        unsigned int index = 32736;
        index < KERNAUX_PFA_PAGES_COUNT_MAX;
        ++index
    ) {
        assert(pfa.pages[index] == KERNAUX_FALSE);
    }

    return 0;
}
