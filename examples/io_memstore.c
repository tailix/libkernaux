#include <kernaux/io.h>

#include <assert.h>
#include <string.h>

#define BUFFER_SIZE 4096
#define SMALL_BUFFER_SIZE 5

static const char *const hello = "Hello, World!";

static unsigned char files_void[1000];
static char buffer[BUFFER_SIZE];

void example_main()
{
    struct KernAux_SizedVoid files_sized_void =
        KernAux_SizedVoid_create(sizeof(files_void), files_void);

    {
        struct KernAux_MemStore mem_store =
            KernAux_MemStore_create(&files_sized_void, buffer, BUFFER_SIZE);

        KernAux_File file = KernAux_Store_open(&mem_store.store);
        assert(file);

        assert(KernAux_File_puts(file, hello));
        assert(strncmp(buffer, hello, strlen(hello)) == 0);
    }

    memset(buffer, 0, sizeof(buffer));

    {
        struct KernAux_MemStore mem_store;
        KernAux_MemStore_init(
            &mem_store,
            &files_sized_void,
            buffer,
            SMALL_BUFFER_SIZE
        );

        KernAux_File file = KernAux_Store_open(&mem_store.store);
        assert(file);

        assert(!KernAux_File_puts(file, hello));
        assert(strncmp(buffer, hello, SMALL_BUFFER_SIZE) == 0);
        assert(strncmp(buffer, hello, strlen(hello)) != 0);
    }
}
