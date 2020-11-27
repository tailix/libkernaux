#include <assert.h>
#include <string.h>
#include <unistd.h>

#define __USE_POSIX2
#include <stdio.h>

int main()
{
    FILE *const fd = popen("tests/hang 2>&1", "r");
    assert(fd != NULL);

    char buffer[256];
    char *const result = fgets(buffer, 256, fd);
    assert(result == buffer);
    assert(0 == strncmp(result, "Segmentation fault (core dumped)\n", 256));

    const int status = pclose(fd);
    assert(status != 0);

    return 0;
}
