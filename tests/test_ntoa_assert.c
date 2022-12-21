#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/ntoa.h>
#include <kernaux/runtime.h>

#include <assert.h>
#include <setjmp.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define VALID_LONG_PREFIX "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
#define TOO_LONG_PREFIX   "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"

static jmp_buf jmpbuf;

static unsigned int assert_count_exp = 0;
static unsigned int assert_count_ctr = 0;

static const char *assert_last_file = NULL;
static int assert_last_line = 0;
static const char *assert_last_msg = NULL;

static void assert_cb(
    const char *const file,
    const int line,
    const char *const msg
) {
    ++assert_count_ctr;

    assert_last_file = file;
    assert_last_line = line;
    assert_last_msg = msg;

    longjmp(jmpbuf, 1);
}

static void test_utoa_assert(char *const buffer, const int base)
{
    if (setjmp(jmpbuf) == 0) {
        kernaux_utoa(0, buffer, base, NULL);
    } else {
        // cppcheck-suppress assignmentInAssert
        assert(assert_count_ctr == ++assert_count_exp);
        assert(strstr(assert_last_file, "src/ntoa.c") != NULL);
        assert(assert_last_line != 0);
        assert(assert_last_msg != NULL);

        assert_last_file = NULL;
        assert_last_line = 0;
        assert_last_msg = NULL;
    }
}

static void test_itoa_assert(char *const buffer, const int base)
{
    if (setjmp(jmpbuf) == 0) {
        kernaux_itoa(0, buffer, base, NULL);
    } else {
        // cppcheck-suppress assignmentInAssert
        assert(assert_count_ctr == ++assert_count_exp);
        assert(strstr(assert_last_file, "src/ntoa.c") != NULL);
        assert(assert_last_line != 0);
        assert(assert_last_msg != NULL);

        assert_last_file = NULL;
        assert_last_line = 0;
        assert_last_msg = NULL;
    }
}

static const char *str_end(const char *str)
{
    for (;; ++str) if (*str == '\0') return str;
}

void test_main()
{
    kernaux_assert_cb = assert_cb;

    if (setjmp(jmpbuf) != 0) abort();

    {
        char buffer[KERNAUX_UTOA_MIN_BUFFER_SIZE + KERNAUX_NTOA_MAX_PREFIX_LEN];

        const char *const end1 =
            kernaux_utoa(123, buffer, 'd', VALID_LONG_PREFIX);
        assert(strcmp(buffer, VALID_LONG_PREFIX"123") == 0);
        assert(end1 == str_end(buffer));
        assert(assert_count_ctr == assert_count_exp);
        assert(assert_last_file == NULL);
        assert(assert_last_line == 0);
        assert(assert_last_msg == NULL);

        if (setjmp(jmpbuf) == 0) {
            kernaux_utoa(123, buffer, 'd', TOO_LONG_PREFIX);
        } else {
            assert(strcmp(buffer, VALID_LONG_PREFIX) == 0);
            // cppcheck-suppress assignmentInAssert
            assert(assert_count_ctr == ++assert_count_exp);
            assert(strstr(assert_last_file, "src/ntoa.c") != NULL);
            assert(assert_last_line != 0);
            assert(strcmp(assert_last_msg, "prefix is too long") == 0);
            assert_last_file = NULL;
            assert_last_line = 0;
            assert_last_msg = NULL;
        }

        test_utoa_assert(NULL, 'd');
        test_utoa_assert(buffer, 0);
        test_utoa_assert(buffer, 1);
        test_utoa_assert(buffer, -1);
        test_utoa_assert(buffer, 37);
        test_utoa_assert(buffer, -37);
    }

    if (setjmp(jmpbuf) != 0) abort();

    {
        char buffer[KERNAUX_ITOA_MIN_BUFFER_SIZE + KERNAUX_NTOA_MAX_PREFIX_LEN];

        const char *const end1 =
            kernaux_itoa(123, buffer, 'd', VALID_LONG_PREFIX);
        assert(strcmp(buffer, VALID_LONG_PREFIX"123") == 0);
        assert(end1 == str_end(buffer));
        assert(assert_count_ctr == assert_count_exp);
        assert(assert_last_file == NULL);
        assert(assert_last_line == 0);
        assert(assert_last_msg == NULL);

        if (setjmp(jmpbuf) == 0) {
            kernaux_itoa(123, buffer, 'd', TOO_LONG_PREFIX);
        } else {
            assert(strcmp(buffer, VALID_LONG_PREFIX) == 0);
            // cppcheck-suppress assignmentInAssert
            assert(assert_count_ctr == ++assert_count_exp);
            assert(strstr(assert_last_file, "src/ntoa.c") != NULL);
            assert(assert_last_line != 0);
            assert(strcmp(assert_last_msg, "prefix is too long") == 0);
            assert_last_file = NULL;
            assert_last_line = 0;
            assert_last_msg = NULL;
        }

        test_itoa_assert(NULL, 'd');
        test_itoa_assert(buffer, 0);
        test_itoa_assert(buffer, 1);
        test_itoa_assert(buffer, -1);
        test_itoa_assert(buffer, 37);
        test_itoa_assert(buffer, -37);
    }
}
