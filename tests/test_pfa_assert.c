#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/macro.h>
#include <kernaux/pfa.h>
#include <kernaux/runtime.h>

#include <assert.h>
#include <setjmp.h>
#include <stddef.h>
#include <stdlib.h>

static unsigned int count = 0;
static jmp_buf jmpbuf;

static void assert_cb(
    const char *const file KERNAUX_UNUSED,
    const int line KERNAUX_UNUSED,
    const char *const str KERNAUX_UNUSED
) {
    ++count;
    longjmp(jmpbuf, 1);
}

void test_main()
{
    if (setjmp(jmpbuf) != 0) abort();

    kernaux_assert_cb = assert_cb;

    struct KernAux_PFA pfa;

    if (setjmp(jmpbuf) == 0) {
        KernAux_PFA_initialize(&pfa);
    } else {
        assert(count == 0);
    }

    if (setjmp(jmpbuf) == 0) {
        KernAux_PFA_initialize(NULL);
    } else {
        assert(count == 1);
    }

    if (setjmp(jmpbuf) == 0) {
        assert(!KernAux_PFA_is_available(NULL, KERNAUX_PFA_PAGE_SIZE));
    } else {
        assert(count == 2);
    }

    if (setjmp(jmpbuf) == 0) {
        assert(!KernAux_PFA_is_available(&pfa, 123));
    } else {
        assert(count == 3);
    }

    if (setjmp(jmpbuf) == 0) {
        KernAux_PFA_mark_available(NULL, 0, KERNAUX_PFA_PAGE_SIZE);
    } else {
        assert(count == 4);
    }

    if (setjmp(jmpbuf) == 0) {
        KernAux_PFA_mark_available(&pfa, KERNAUX_PFA_PAGE_SIZE, 0);
    } else {
        assert(count == 5);
    }

    if (setjmp(jmpbuf) == 0) {
        KernAux_PFA_mark_unavailable(NULL, 0, KERNAUX_PFA_PAGE_SIZE);
    } else {
        assert(count == 6);
    }

    if (setjmp(jmpbuf) == 0) {
        KernAux_PFA_mark_unavailable(&pfa, KERNAUX_PFA_PAGE_SIZE, 0);
    } else {
        assert(count == 7);
    }

    if (setjmp(jmpbuf) == 0) {
        assert(KernAux_PFA_alloc_pages(NULL, KERNAUX_PFA_PAGE_SIZE) == 0);
    } else {
        assert(count == 8);
    }

    if (setjmp(jmpbuf) == 0) {
        KernAux_PFA_free_pages(NULL, KERNAUX_PFA_PAGE_SIZE, KERNAUX_PFA_PAGE_SIZE);
    } else {
        assert(count == 9);
    }

    if (setjmp(jmpbuf) == 0) {
        KernAux_PFA_free_pages(&pfa, 123, KERNAUX_PFA_PAGE_SIZE);
    } else {
        assert(count == 10);
    }
}
