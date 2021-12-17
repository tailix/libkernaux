#define KERNAUX_ENABLE_ASSERT
#include <kernaux/assert.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

static unsigned int count = 0;
static const char *last_file = NULL;
static int last_line = 0;
static const char *last_str = NULL;

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

int main()
{
    kernaux_assert_cb = assert_cb;

    KERNAUX_ASSERT(1 == 1);

    assert(count == 0);
    assert(last_file == NULL);
    assert(last_line == 0);
    assert(last_str == NULL);

    KERNAUX_ASSERT(1 != 1);

    assert(count == 1);
    assert(strcmp(last_file, __FILE__) == 0);
    assert(last_line == __LINE__ - 4);
    assert(strcmp(last_str, "1 != 1") == 0);

    KERNAUX_ASSERT(strcmp("qwe", "rty") == 0);

    assert(count == 2);
    assert(strcmp(last_file, __FILE__) == 0);
    assert(last_line == __LINE__ - 4);
    assert(strcmp(last_str, "strcmp(\"qwe\", \"rty\") == 0") == 0);

    return 0;
}
