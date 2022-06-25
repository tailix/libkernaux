#include <kernaux/printf.h>

#include <assert.h>
#include <string.h>

#define BUFFER_SIZE 1024

static char buffer[BUFFER_SIZE];

void example_main()
{
    const int result = kernaux_snprintf(
        buffer,
        sizeof(buffer),
        "Hello, %s! Session ID: %u.",
        "Alex",
        123
    );
    assert((size_t)result == strlen(buffer));
    assert(strcmp(buffer, "Hello, Alex! Session ID: 123.") == 0);
}
