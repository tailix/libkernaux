#undef KERNAUX_DISABLE_ASSERT
#include <kernaux/assert.h>

#include <assert.h>
#include <setjmp.h>
#include <stddef.h>
#include <string.h>

static jmp_buf jmpbuf;
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

    longjmp(jmpbuf, 1);
}

int main()
{
    assert(setjmp(jmpbuf) == 0);

    kernaux_assert_cb = assert_cb;

    if (setjmp(jmpbuf) == 0) {
        KERNAUX_PANIC("bar");
    }

    assert(count == 1);
    assert(strcmp(last_file, __FILE__) == 0);
    assert(last_line == __LINE__ - 5);
    assert(strcmp(last_str, "bar") == 0);

    if (setjmp(jmpbuf) == 0) {
        KERNAUX_PANIC("car");
    }

    assert(count == 2);
    assert(strcmp(last_file, __FILE__) == 0);
    assert(last_line == __LINE__ - 5);
    assert(strcmp(last_str, "car") == 0);
}
