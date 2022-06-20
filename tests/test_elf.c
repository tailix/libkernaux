#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "helper.h"

#include <kernaux/elf.h>

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define BUFFER_SIZE (1024 * 1024)

int main(int argc, char **argv)
{
    setup_assert_abort();

    assert(argc >= 1);

    FILE *const fd = fopen(argv[0], "r");
    assert(fd);

    uint8_t buffer[BUFFER_SIZE];
    const size_t size = fread(buffer, sizeof(uint8_t), BUFFER_SIZE, fd);
    assert(size > 0);

    assert(KernAux_ELF_Header_is_valid((struct KernAux_ELF_Header*)buffer));

    fclose(fd);

    return 0;
}
