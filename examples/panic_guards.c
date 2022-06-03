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

static void test_panic_return(const bool do_panic)
{
    if (do_panic) KERNAUX_PANIC_RETURN("foo");
    ++noreturn_count;
}

static bool test_panic_retval(const bool do_panic)
{
    if (do_panic) KERNAUX_PANIC_RETVAL("bar", false);
    ++noreturn_count;
    return true;
}

int main()
{
    kernaux_assert_cb = assert_cb;

    test_panic_return(false);

    assert(count == 0);
    assert(last_file == NULL);
    assert(last_line == 0);
    assert(last_str == NULL);
    assert(noreturn_count == 1);

    assert(test_panic_retval(false));

    assert(count == 0);
    assert(last_file == NULL);
    assert(last_line == 0);
    assert(last_str == NULL);
    assert(noreturn_count == 2);

    test_panic_return(true);

    assert(count == 1);
    assert(strcmp(last_file, __FILE__) == 0);
    assert(last_line == 28);
    assert(strcmp(last_str, "foo") == 0);
    assert(noreturn_count == 2);

    assert(!test_panic_retval(true));

    assert(count == 2);
    assert(strcmp(last_file, __FILE__) == 0);
    assert(last_line == 34);
    assert(strcmp(last_str, "bar") == 0);
    assert(noreturn_count == 2);
}
