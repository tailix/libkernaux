#define KERNAUX_ENABLE_ASSERT
#define KERNAUX_ENABLE_GUARD
#include <kernaux/assert.h>

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

static unsigned int count = 0;
static const char *last_file = NULL;
static int last_line = 0;
static const char *last_str = NULL;

static unsigned int noreturn_count = 0;

static void assert_cb(
    const char *const file,
    const int line,
    const char *const str
) {
    ++count;
    last_file = file;
    last_line = line;
    last_str = str;
}

static void test_assert_return(const int value)
{
    KERNAUX_ASSERT_RETURN(value > 100);
    ++noreturn_count;
}

static bool test_assert_retval(const int value)
{
    KERNAUX_ASSERT_RETVAL(value > 100, false);
    ++noreturn_count;
    return true;
}

static void test_notnull_return(const int *const value)
{
    KERNAUX_NOTNULL_RETURN(value);
    ++noreturn_count;
}

static bool test_notnull_retval(const int *const value)
{
    KERNAUX_NOTNULL_RETVAL(value, false);
    ++noreturn_count;
    return true;
}

int main()
{
    kernaux_assert_cb = assert_cb;

    int value;

    test_assert_return(123);

    assert(count == 0);
    assert(last_file == NULL);
    assert(last_line == 0);
    assert(last_str == NULL);
    assert(noreturn_count == 1);

    assert(test_assert_retval(123));

    assert(count == 0);
    assert(last_file == NULL);
    assert(last_line == 0);
    assert(last_str == NULL);
    assert(noreturn_count == 2);

    test_notnull_return(&value);

    assert(count == 0);
    assert(last_file == NULL);
    assert(last_line == 0);
    assert(last_str == NULL);
    assert(noreturn_count == 3);

    assert(test_notnull_retval(&value));

    assert(count == 0);
    assert(last_file == NULL);
    assert(last_line == 0);
    assert(last_str == NULL);
    assert(noreturn_count == 4);

    test_assert_return(0);

    assert(count == 1);
    assert(strcmp(last_file, __FILE__) == 0);
    assert(last_line == 30);
    assert(strcmp(last_str, "value > 100") == 0);
    assert(noreturn_count == 4);

    assert(!test_assert_retval(0));

    assert(count == 2);
    assert(strcmp(last_file, __FILE__) == 0);
    assert(last_line == 36);
    assert(strcmp(last_str, "value > 100") == 0);
    assert(noreturn_count == 4);

    test_notnull_return(NULL);

    assert(count == 3);
    assert(strcmp(last_file, __FILE__) == 0);
    assert(last_line == 43);
    assert(strcmp(last_str, "value") == 0);
    assert(noreturn_count == 4);

    assert(!test_notnull_retval(NULL));

    assert(count == 4);
    assert(strcmp(last_file, __FILE__) == 0);
    assert(last_line == 49);
    assert(strcmp(last_str, "value") == 0);
    assert(noreturn_count == 4);

    return 0;
}
