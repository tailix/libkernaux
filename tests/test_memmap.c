#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define KERNAUX_ACCESS_PRIVATE

#include <kernaux/macro.h>
#include <kernaux/memmap.h>
#include <kernaux/runtime.h>

#include <assert.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

static KernAux_MemMap memmap;

static jmp_buf jmpbuf;
static unsigned int assert_count_exp = 0;
static unsigned int assert_count_ctr = 0;
static const char *assert_last_file = NULL;

static void assert_cb(
    const char *const file,
    const int line KERNAUX_UNUSED,
    const char *const msg KERNAUX_UNUSED
) {
    ++assert_count_ctr;
    assert_last_file = file;

    longjmp(jmpbuf, 1);
}

static void before_assert()
{
    assert(assert_count_ctr == assert_count_exp);
}

static void expect_assert()
{
#ifdef ENABLE_ASSERT
    // cppcheck-suppress assignmentInAssert
    assert(assert_count_ctr == ++assert_count_exp);
    assert(strstr(assert_last_file, "src/memmap.c") != NULL);
    assert_last_file = NULL;
#else
    assert(assert_count_ctr == 0);
    assert(assert_last_file == NULL);
#endif
}

#define MEMSET memset(memmap, 0xff, sizeof(memmap))
#define MEMMAP (*memmap)

void test_main()
{
    assert(setjmp(jmpbuf) == 0);

    kernaux_assert_cb = assert_cb;

    {
        MEMSET;
        KernAux_MemMap_init(memmap, 0);

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 0);
        assert(MEMMAP.entries_count == 0);

        assert(KernAux_MemMap_finish(memmap));

        assert(MEMMAP.is_finished);
        assert(MEMMAP.memory_size == 0);
        assert(MEMMAP.entries_count == 0);

        assert(KernAux_MemMap_entry_by_index(memmap, 0) == NULL);

        before_assert();
        if (setjmp(jmpbuf) == 0) {
            assert(!KernAux_MemMap_finish(memmap));
        }
        expect_assert();
    }

    {
        MEMSET;
        KernAux_MemMap_init(memmap, 0);

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 0);
        assert(MEMMAP.entries_count == 0);

        assert(!KernAux_MemMap_add_entry(memmap, false, NULL, 0, 0));

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 0);
        assert(MEMMAP.entries_count == 0);

        assert(KernAux_MemMap_finish(memmap));

        assert(MEMMAP.is_finished);
        assert(MEMMAP.memory_size == 0);
        assert(MEMMAP.entries_count == 0);

        assert(KernAux_MemMap_entry_by_index(memmap, 0) == NULL);
    }

    {
        MEMSET;
        KernAux_MemMap_init(memmap, 1);

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 1);
        assert(MEMMAP.entries_count == 0);

        assert(KernAux_MemMap_add_entry(memmap, false, NULL, 0, 1));

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 1);
        assert(MEMMAP.entries_count == 1);

        assert(KernAux_MemMap_finish(memmap));

        assert(MEMMAP.is_finished);
        assert(MEMMAP.memory_size == 1);
        assert(MEMMAP.entries_count == 1);
        assert(MEMMAP.entries[0].is_available == false);
        assert(MEMMAP.entries[0].tag[0] == '\0');
        assert(MEMMAP.entries[0].start == 0);
        assert(MEMMAP.entries[0].size == 1);
        assert(MEMMAP.entries[0].end == 0);
        assert(MEMMAP.entries[0].limit == 1);

        assert(KernAux_MemMap_entry_by_index(memmap, 0) == &MEMMAP.entries[0]);
    }

    {
        MEMSET;
        KernAux_MemMap_init(memmap, 2);

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 2);
        assert(MEMMAP.entries_count == 0);

        assert(KernAux_MemMap_add_entry(memmap, false, NULL, 0, 2));

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 2);
        assert(MEMMAP.entries_count == 1);

        assert(KernAux_MemMap_finish(memmap));

        assert(MEMMAP.is_finished);
        assert(MEMMAP.memory_size == 2);
        assert(MEMMAP.entries_count == 1);
        assert(MEMMAP.entries[0].is_available == false);
        assert(MEMMAP.entries[0].tag[0] == '\0');
        assert(MEMMAP.entries[0].start == 0);
        assert(MEMMAP.entries[0].size == 2);
        assert(MEMMAP.entries[0].end == 1);
        assert(MEMMAP.entries[0].limit == 2);

        assert(KernAux_MemMap_entry_by_index(memmap, 0) == &MEMMAP.entries[0]);
    }

    {
        MEMSET;
        KernAux_MemMap_init(memmap, 1);

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 1);
        assert(MEMMAP.entries_count == 0);

        assert(KernAux_MemMap_add_entry(memmap, false, NULL, 0, 2));

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 1);
        assert(MEMMAP.entries_count == 1);

        assert(!KernAux_MemMap_finish(memmap));

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 1);
        assert(MEMMAP.entries_count == 1);
        assert(MEMMAP.entries[0].is_available == false);
        assert(MEMMAP.entries[0].tag[0] == '\0');
        assert(MEMMAP.entries[0].start == 0);
        assert(MEMMAP.entries[0].size == 2);
        assert(MEMMAP.entries[0].end == 1);
        assert(MEMMAP.entries[0].limit == 2);

        before_assert();
        if (setjmp(jmpbuf) == 0) {
            assert(KernAux_MemMap_entry_by_index(memmap, 0) == NULL);
        }
        expect_assert();
    }

    {
        MEMSET;
        KernAux_MemMap_init(memmap, 2);

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 2);
        assert(MEMMAP.entries_count == 0);

        assert(KernAux_MemMap_add_entry(memmap, false, NULL, 0, 1));

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 2);
        assert(MEMMAP.entries_count == 1);

        assert(KernAux_MemMap_add_entry(memmap, false, NULL, 1, 1));

        assert(MEMMAP.is_finished == false);
        assert(MEMMAP.memory_size == 2);
        assert(MEMMAP.entries_count == 2);

        assert(KernAux_MemMap_finish(memmap));

        assert(MEMMAP.is_finished);
        assert(MEMMAP.memory_size == 2);
        assert(MEMMAP.entries_count == 2);
        assert(MEMMAP.entries[0].is_available == false);
        assert(MEMMAP.entries[0].tag[0] == '\0');
        assert(MEMMAP.entries[0].start == 0);
        assert(MEMMAP.entries[0].size == 1);
        assert(MEMMAP.entries[0].end == 0);
        assert(MEMMAP.entries[0].limit == 1);
        assert(MEMMAP.entries[1].is_available == false);
        assert(MEMMAP.entries[1].tag[0] == '\0');
        assert(MEMMAP.entries[1].start == 1);
        assert(MEMMAP.entries[1].size == 1);
        assert(MEMMAP.entries[1].end == 1);
        assert(MEMMAP.entries[1].limit == 2);

        assert(KernAux_MemMap_entry_by_index(memmap, 0) == &MEMMAP.entries[0]);
        assert(KernAux_MemMap_entry_by_index(memmap, 1) == &MEMMAP.entries[1]);
    }

    assert(assert_count_ctr == assert_count_exp);
}
