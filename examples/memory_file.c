#include <kernaux/memory_file.h>

#include <assert.h>
#include <string.h>

static char buffer[4096];

void example_main()
{
    struct KernAux_MemoryFile memory_file =
        KernAux_MemoryFile_create(buffer, sizeof(buffer), NULL);

    KernAux_File_puts(&memory_file.file, "Hello, World!");

    assert(strcmp(buffer, "Hello, World!") == 0);
}
