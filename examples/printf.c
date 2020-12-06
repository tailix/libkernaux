#include <kernaux/printf.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

static char buffer[BUFFER_SIZE];
static unsigned int buffer_index;

static void my_putchar(const char chr)
{
    if (buffer_index >= BUFFER_SIZE) abort();
    buffer[buffer_index++] = chr;
}

int main()
{
    memset(buffer, '\0', sizeof(buffer));
    buffer_index = 0;
    kernaux_printf(my_putchar, "Hello, %s!", "Alex");
    assert(strcmp(buffer, "Hello, Alex!") == 0);

    printf("OK!\n");

    return 0;
}
