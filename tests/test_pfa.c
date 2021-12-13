#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/pfa.h>

#include <assert.h>

int main()
{
    struct KernAux_PFA pfa;

    KernAux_PFA_initialize(&pfa);

    for (size_t index = 0; index < KERNAUX_PFA_PAGES_COUNT_MAX; ++index) {
        assert(pfa.pages[index] == false);
    }

    KernAux_PFA_mark_available(&pfa, 0, 654335);
    KernAux_PFA_mark_available(&pfa, 1048576, 134086655);
    KernAux_PFA_mark_unavailable(&pfa, 4194304, 6291455); // [4 MB, 6 MB)

    for (size_t index = 0; index < 159; ++index) {
        assert(pfa.pages[index] == true);
    }

    for (size_t index = 159; index < 256; ++index) {
        assert(pfa.pages[index] == false);
    }

    for (size_t index = 256; index < 1024; ++index) { // [1 MB, 4 MB)
        assert(pfa.pages[index] == true);
    }

    for (size_t index = 1024; index < 1536; ++index) { // [4 MB, 6 MB)
        assert(pfa.pages[index] == false);
    }

    for (size_t index = 1536; index < 32736; ++index) { // [6 MB, ~127 MB)
        assert(pfa.pages[index] == true);
    }

    for (size_t index = 32736; index < KERNAUX_PFA_PAGES_COUNT_MAX; ++index) {
        assert(pfa.pages[index] == false);
    }

    const size_t page_addr = KernAux_PFA_alloc_page(&pfa);

    assert(page_addr != 0);
    assert(page_addr % KERNAUX_PFA_PAGE_SIZE == 0);
    assert(!pfa.pages[page_addr / KERNAUX_PFA_PAGE_SIZE]);

    KernAux_PFA_free_page(&pfa, page_addr);

    assert(pfa.pages[page_addr / KERNAUX_PFA_PAGE_SIZE]);

    for (size_t index = 0; index < KERNAUX_PFA_PAGES_COUNT_MAX; ++index) {
        if (pfa.pages[index]) {
            assert(KernAux_PFA_alloc_page(&pfa) != 0);
        }
    }

    assert(KernAux_PFA_alloc_page(&pfa) == 0);

    return 0;
}
