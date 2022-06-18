#include <kernaux/pfa.h>

#include <assert.h>

// Create PFA in some static memory area because typically you don't have memory
// management in kernel without PFA.
struct KernAux_PFA pfa;

void example_main()
{
    // In the earliest stage of kernel initialization mark all pages as
    // unavailable because you don't have memory map yet.
    KernAux_PFA_initialize(&pfa);

    // Let's assume that you have the following memory map now:
    // * [0 B; 64 KiB)
    // * [1 MiB; 4 MiB)
    // * [6 MiB; 128 MiB)
    // Mark these pages as available. Note that page is identified by any
    // address inside it. This is why you can subtract 1, not only
    // KERNAUX_PFA_PAGE_SIZE.
    KernAux_PFA_mark_available(&pfa, 0,               1024        * 64  - 1);
    KernAux_PFA_mark_available(&pfa, 1024 * 1024,     1024 * 1024 * 4   - 1);
    KernAux_PFA_mark_available(&pfa, 1024 * 1024 * 6, 1024 * 1024 * 128 - 1);

    // You can test page availability.
    assert(KernAux_PFA_is_available(&pfa,  1024 * 32));      // 32 KiB
    assert(!KernAux_PFA_is_available(&pfa, 1024 * 64));      // 64 KiB
    assert(KernAux_PFA_is_available(&pfa,  1024 * 1024));    // 1 MiB
    assert(!KernAux_PFA_is_available(&pfa, 1024 * 1024 * 6   // 6 MiB - 4 KiB
                                           - KERNAUX_PFA_PAGE_SIZE));
    assert(KernAux_PFA_is_available(&pfa,  1024 * 1024 * 128 // 128 MiB - 4 KiB
                                           - KERNAUX_PFA_PAGE_SIZE));
    assert(!KernAux_PFA_is_available(&pfa, 1024 * 1024 * 128)); // 128 MiB

    // When you have configured PFA, you can use it to allocate and free pages.
    {
        const size_t page_addr =
            KernAux_PFA_alloc_pages(&pfa, KERNAUX_PFA_PAGE_SIZE);
        assert(!KernAux_PFA_is_available(&pfa, page_addr));
        KernAux_PFA_free_pages(&pfa, page_addr, KERNAUX_PFA_PAGE_SIZE);
        assert(KernAux_PFA_is_available(&pfa, page_addr));
    }

    // You can also allocate multiple continuous pages.
    {
        const size_t page_addr =
            KernAux_PFA_alloc_pages(&pfa, 10 * KERNAUX_PFA_PAGE_SIZE);

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

    // You can also request amounts of memory which are not factors of page
    // size.
    {
        const size_t page_addr = KernAux_PFA_alloc_pages(&pfa, 123);
        assert(!KernAux_PFA_is_available(&pfa, page_addr));
        KernAux_PFA_free_pages(&pfa, page_addr, 123);
        assert(KernAux_PFA_is_available(&pfa, page_addr));
    }
}
