#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/pfa.h>

#include <assert.h>
#include <stddef.h>

static unsigned int count = 0;

static void test();

#ifdef KERNAUX_ENABLE_ASSERT
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
#endif

int main()
{
    kernaux_assert_cb = NULL;
    test();

#if defined(KERNAUX_ENABLE_ASSERT) || defined(KERNAUX_ENABLE_NULL_GUARD)
#ifdef KERNAUX_ENABLE_ASSERT
    kernaux_assert_cb = assert_cb;
#endif
    test();
#endif

    return 0;
}

void test()
{
    unsigned int acc = 0;
    struct KernAux_PFA pfa;
    KernAux_PFA_initialize(&pfa);

#ifdef KERNAUX_ENABLE_NULL_GUARD
    KernAux_PFA_initialize(NULL);
    if (kernaux_assert_cb) assert(count == ++acc);
#endif

#ifdef KERNAUX_ENABLE_NULL_GUARD
    assert(!KernAux_PFA_is_available(NULL, KERNAUX_PFA_PAGE_SIZE));
    if (kernaux_assert_cb) assert(count == ++acc);
#endif

    assert(!KernAux_PFA_is_available(&pfa, 123));
    if (kernaux_assert_cb) assert(count == ++acc);

#ifdef KERNAUX_ENABLE_NULL_GUARD
    KernAux_PFA_mark_available(NULL, 0, KERNAUX_PFA_PAGE_SIZE);
    if (kernaux_assert_cb) assert(count == ++acc);
#endif

    KernAux_PFA_mark_available(&pfa, KERNAUX_PFA_PAGE_SIZE, 0);
    if (kernaux_assert_cb) assert(count == ++acc);

#ifdef KERNAUX_ENABLE_NULL_GUARD
    KernAux_PFA_mark_unavailable(NULL, 0, KERNAUX_PFA_PAGE_SIZE);
    if (kernaux_assert_cb) assert(count == ++acc);
#endif

    KernAux_PFA_mark_unavailable(&pfa, KERNAUX_PFA_PAGE_SIZE, 0);
    if (kernaux_assert_cb) assert(count == ++acc);

#ifdef KERNAUX_ENABLE_NULL_GUARD
    assert(KernAux_PFA_alloc_pages(NULL, KERNAUX_PFA_PAGE_SIZE) == 0);
    if (kernaux_assert_cb) assert(count == ++acc);
#endif

#ifdef KERNAUX_ENABLE_NULL_GUARD
    KernAux_PFA_free_pages(NULL, KERNAUX_PFA_PAGE_SIZE, KERNAUX_PFA_PAGE_SIZE);
    if (kernaux_assert_cb) assert(count == ++acc);
#endif

    KernAux_PFA_free_pages(&pfa, 123, KERNAUX_PFA_PAGE_SIZE);
    if (kernaux_assert_cb) assert(count == ++acc);
}
