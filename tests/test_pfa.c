#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/pfa.h>

#include <assert.h>

void test_main()
{
    struct KernAux_PFA pfa;

    KernAux_PFA_initialize(&pfa);

    for (size_t index = 0; index < KERNAUX_PFA_PAGES_COUNT_MAX; ++index) {
        assert(!KernAux_PFA_is_available(&pfa, index * KERNAUX_PFA_PAGE_SIZE));
    }

    KernAux_PFA_mark_available(&pfa, 0, 654335);
    KernAux_PFA_mark_available(&pfa, 1048576, 134086655);
    KernAux_PFA_mark_unavailable(&pfa, 4194304, 6291455); // [4 MB, 6 MB)

    for (size_t index = 0; index < 159; ++index) {
        assert(KernAux_PFA_is_available(&pfa, index * KERNAUX_PFA_PAGE_SIZE));
    }

    for (size_t index = 159; index < 256; ++index) {
        assert(!KernAux_PFA_is_available(&pfa, index * KERNAUX_PFA_PAGE_SIZE));
    }

    for (size_t index = 256; index < 1024; ++index) { // [1 MB, 4 MB)
        assert(KernAux_PFA_is_available(&pfa, index * KERNAUX_PFA_PAGE_SIZE));
    }

    for (size_t index = 1024; index < 1536; ++index) { // [4 MB, 6 MB)
        assert(!KernAux_PFA_is_available(&pfa, index * KERNAUX_PFA_PAGE_SIZE));
    }

    for (size_t index = 1536; index < 32736; ++index) { // [6 MB, ~127 MB)
        assert(KernAux_PFA_is_available(&pfa, index * KERNAUX_PFA_PAGE_SIZE));
    }

    for (size_t index = 32736; index < KERNAUX_PFA_PAGES_COUNT_MAX; ++index) {
        assert(!KernAux_PFA_is_available(&pfa, index * KERNAUX_PFA_PAGE_SIZE));
    }

    {
        const size_t page_addr = KernAux_PFA_alloc_pages(&pfa, 1);

        assert(page_addr != 0);
        assert(page_addr % KERNAUX_PFA_PAGE_SIZE == 0);
        assert(!KernAux_PFA_is_available(&pfa, page_addr));

        KernAux_PFA_free_pages(&pfa, page_addr, 1);

        assert(KernAux_PFA_is_available(&pfa, page_addr));
    }

    {
        const size_t page_addr =
            KernAux_PFA_alloc_pages(&pfa, 10 * KERNAUX_PFA_PAGE_SIZE);

        assert(page_addr != 0);
        assert(page_addr % KERNAUX_PFA_PAGE_SIZE == 0);

        for (size_t index = 0, addr = page_addr; index < 10; ++index) {
            assert(!KernAux_PFA_is_available(&pfa, addr));
            addr += KERNAUX_PFA_PAGE_SIZE;
        }

        KernAux_PFA_free_pages(&pfa, page_addr, 10 * KERNAUX_PFA_PAGE_SIZE);

        for (size_t index = 0, addr = page_addr; index < 10; ++index) {
            assert(KernAux_PFA_is_available(&pfa, addr));
            addr += KERNAUX_PFA_PAGE_SIZE;
        }
    }

    for (size_t index = 0; index < KERNAUX_PFA_PAGES_COUNT_MAX; ++index) {
        if (KernAux_PFA_is_available(&pfa, index * KERNAUX_PFA_PAGE_SIZE)) {
            assert(KernAux_PFA_alloc_pages(&pfa, 1) != 0);
        }
    }

    assert(KernAux_PFA_alloc_pages(&pfa, 1) == 0);
}
