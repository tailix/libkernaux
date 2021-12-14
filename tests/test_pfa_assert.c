#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/pfa.h>

#include <assert.h>
#include <stddef.h>

static unsigned int count = 0;

static void test();

static void assert_cb(
    __attribute__((unused))
    const char *const file,
    __attribute__((unused))
    const int line,
    __attribute__((unused))
    const char *const str
) {
    ++count;
}

int main()
{
    kernaux_assert_cb = NULL;
    test();

#ifdef ENABLE_ASSERT
    kernaux_assert_cb = assert_cb;
    test();
#endif

    return 0;
}

void test()
{
    struct KernAux_PFA pfa;
    KernAux_PFA_initialize(&pfa);

    KernAux_PFA_initialize(NULL);
    if (kernaux_assert_cb) assert(count == 1);

    assert(!KernAux_PFA_is_available(NULL, KERNAUX_PFA_PAGE_SIZE));
    if (kernaux_assert_cb) assert(count == 2);

    assert(!KernAux_PFA_is_available(&pfa, 123));
    if (kernaux_assert_cb) assert(count == 3);

    KernAux_PFA_mark_available(NULL, 0, KERNAUX_PFA_PAGE_SIZE);
    if (kernaux_assert_cb) assert(count == 4);

    KernAux_PFA_mark_available(&pfa, KERNAUX_PFA_PAGE_SIZE, 0);
    if (kernaux_assert_cb) assert(count == 5);

    KernAux_PFA_mark_unavailable(NULL, 0, KERNAUX_PFA_PAGE_SIZE);
    if (kernaux_assert_cb) assert(count == 6);

    KernAux_PFA_mark_unavailable(&pfa, KERNAUX_PFA_PAGE_SIZE, 0);
    if (kernaux_assert_cb) assert(count == 7);

    assert(KernAux_PFA_alloc_pages(NULL, KERNAUX_PFA_PAGE_SIZE) == 0);
    if (kernaux_assert_cb) assert(count == 8);

    KernAux_PFA_free_pages(NULL, KERNAUX_PFA_PAGE_SIZE, KERNAUX_PFA_PAGE_SIZE);
    if (kernaux_assert_cb) assert(count == 9);

    KernAux_PFA_free_pages(&pfa, 123, KERNAUX_PFA_PAGE_SIZE);
    if (kernaux_assert_cb) assert(count == 10);
}
