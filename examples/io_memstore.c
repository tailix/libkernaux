#include <kernaux/io.h>

#include <assert.h>
#include <string.h>

#define BUFFER_SIZE 4096
#define SMALL_BUFFER_SIZE 5

static const char *const hello = "Hello, World!";

static char buffer[BUFFER_SIZE];

void example_main()
{
    {
        struct KernAux_MemStore mem_store =
            KernAux_MemStore_create(buffer, BUFFER_SIZE);

        assert(KernAux_Store_puts(&mem_store.store, hello));
        assert(strncmp(buffer, hello, strlen(hello)) == 0);
    }

    memset(buffer, 0, sizeof(buffer));

    {
        struct KernAux_MemStore mem_store;
        KernAux_MemStore_init(&mem_store, buffer, SMALL_BUFFER_SIZE);

        assert(!KernAux_Store_puts(&mem_store.store, hello));
        assert(strncmp(buffer, hello, SMALL_BUFFER_SIZE) == 0);
        assert(strncmp(buffer, hello, strlen(hello)) != 0);
    }
}
