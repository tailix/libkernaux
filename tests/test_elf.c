#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/elf.h>

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#define BUFFER_SIZE (1024 * 1024)

int main(int argc, char **argv)
{
    assert(argc >= 1);

    FILE *const fd = fopen(argv[0], "r");
    assert(fd);

    unsigned char buffer[BUFFER_SIZE];
    const size_t size = fread(buffer, sizeof(unsigned char), BUFFER_SIZE, fd);
    assert(size > 0);

    assert(KernAux_ELF_Header_is_valid(buffer));

    fclose(fd);

    return 0;
}
