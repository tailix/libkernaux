#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "assert.h"

#include <kernaux/macro.h>
#include <kernaux/pfa.h>

#include <string.h>

#define PAGE_INDEX(page_addr) ((page_addr) / KERNAUX_PFA_PAGE_SIZE)

#define FLAG_INDEX_FROM_INDEX(page_index) ((page_index) / 8)
#define FLAG_MASK_FROM_INDEX(page_index) KERNAUX_BITS((page_index) % 8)

#define FLAG_INDEX_FROM_ADDR(page_addr) \
    (FLAG_INDEX_FROM_INDEX(PAGE_INDEX(page_addr)))
#define FLAG_MASK_FROM_ADDR(page_addr) \
    (FLAG_MASK_FROM_INDEX(PAGE_INDEX(page_addr)))

#define GET_FLAG_FROM_INDEX(pfa, page_index) \
    (!!((pfa)->flags[FLAG_INDEX_FROM_INDEX(page_index)] & \
        FLAG_MASK_FROM_INDEX(page_index)))
#define GET_FLAG_FROM_ADDR(pfa, page_addr) \
    (!!((pfa)->flags[FLAG_INDEX_FROM_ADDR(page_addr)] & \
        FLAG_MASK_FROM_ADDR(page_addr)))

#define FLAG_TRUE_FROM_INDEX(pfa, page_index) \
    ((pfa)->flags[FLAG_INDEX_FROM_INDEX(page_index)] |= \
     FLAG_MASK_FROM_INDEX(page_index))
#define FLAG_FALSE_FROM_INDEX(pfa, page_index) \
    ((pfa)->flags[FLAG_INDEX_FROM_INDEX(page_index)] &= \
     ~FLAG_MASK_FROM_INDEX(page_index))

static void KernAux_PFA_mark(
    KernAux_PFA pfa,
    bool status,
    size_t start,
    size_t end
);

void KernAux_PFA_initialize(const KernAux_PFA pfa)
{
    KERNAUX_NOTNULL(pfa);
    // cppcheck-suppress ctunullpointer
    memset(pfa->flags, 0, sizeof(pfa->flags));
}

bool KernAux_PFA_is_available(const KernAux_PFA pfa, const size_t page_addr)
{
    KERNAUX_NOTNULL(pfa);
    KERNAUX_ASSERT(page_addr % KERNAUX_PFA_PAGE_SIZE == 0);

    // cppcheck-suppress ctunullpointer
    return GET_FLAG_FROM_ADDR(pfa, page_addr);
}

void KernAux_PFA_mark_available(
    const KernAux_PFA pfa,
    const size_t start,
    const size_t end
) {
    KernAux_PFA_mark(pfa, true, start, end);
}

void KernAux_PFA_mark_unavailable(
    const KernAux_PFA pfa,
    const size_t start,
    const size_t end
) {
    KernAux_PFA_mark(pfa, false, start, end);
}

void KernAux_PFA_mark(
    const KernAux_PFA pfa,
    const bool status,
    size_t start,
    size_t end
) {
    KERNAUX_NOTNULL(pfa);
    KERNAUX_ASSERT(start < end);

    const size_t start_rem = start % KERNAUX_PFA_PAGE_SIZE;
    const size_t end_rem = (end + 1) % KERNAUX_PFA_PAGE_SIZE;

    if (start_rem != 0) {
        start = start - start_rem + KERNAUX_PFA_PAGE_SIZE;
    }

    if (end_rem != 0) {
        end = end - end_rem;
    }

    const size_t start_index = start / KERNAUX_PFA_PAGE_SIZE;
    const size_t end_index   = end   / KERNAUX_PFA_PAGE_SIZE;

    for (size_t index = start_index; index <= end_index; ++index) {
        if (status) {
            FLAG_TRUE_FROM_INDEX(pfa, index);
        } else {
            FLAG_FALSE_FROM_INDEX(pfa, index);
        }
    }
}

size_t KernAux_PFA_alloc_pages(const KernAux_PFA pfa, size_t mem_size)
{
    KERNAUX_NOTNULL(pfa);

    const size_t mem_rem = mem_size % KERNAUX_PFA_PAGE_SIZE;

    if (mem_rem != 0) {
        mem_size = mem_size - mem_rem + KERNAUX_PFA_PAGE_SIZE;
    }

    const size_t pages_count = mem_size / KERNAUX_PFA_PAGE_SIZE;

    // We start from 1 because 0 indicates failure.
    // It is not very useful to alloc page at address 0;
    for (size_t index = 1, start = 0;
            index < KERNAUX_PFA_PAGES_COUNT_MAX;
            ++index)
    {
        if (!GET_FLAG_FROM_INDEX(pfa, index)) {
            start = 0;
            continue;
        }

        if (start == 0) start = index;

        if (index - start + 1 == pages_count) {
            for (; index >= start; --index) {
                FLAG_FALSE_FROM_INDEX(pfa, index);
            }
            return start * KERNAUX_PFA_PAGE_SIZE;
        }
    }

    return 0;
}

void KernAux_PFA_free_pages(
    const KernAux_PFA pfa,
    const size_t page_addr,
    size_t mem_size
) {
    KERNAUX_NOTNULL(pfa);
    KERNAUX_ASSERT(page_addr % KERNAUX_PFA_PAGE_SIZE == 0);

    const size_t mem_rem = mem_size % KERNAUX_PFA_PAGE_SIZE;

    if (mem_rem != 0) {
        mem_size = mem_size - mem_rem + KERNAUX_PFA_PAGE_SIZE;
    }

    const size_t start_index = page_addr / KERNAUX_PFA_PAGE_SIZE;
    const size_t pages_count = mem_size  / KERNAUX_PFA_PAGE_SIZE;

    for (size_t index = 0; index < pages_count; ++index) {
        FLAG_TRUE_FROM_INDEX(pfa, start_index + index);
    }
}
