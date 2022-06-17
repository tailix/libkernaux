#include <kernaux/io.h>

#include <assert.h>
#include <string.h>

#define BUFFER_SIZE 4096
#define SMALL_BUFFER_SIZE 5

static const char *const hello = "Hello, World!";

static char                     buffer[BUFFER_SIZE];
static struct KernAux_MemStore  buffer_mem_store;
static struct KernAux_SizedVoid buffer_mem_store_files_sized_void;
static unsigned char            buffer_mem_store_files_void[1000];

void example_main()
{
    KernAux_SizedVoid_init(
        &buffer_mem_store_files_sized_void,
        buffer_mem_store_files_void,
        sizeof(buffer_mem_store_files_void)
    );

    {
        KernAux_MemStore_init(
            &buffer_mem_store,
            &buffer_mem_store_files_sized_void,
            buffer,
            BUFFER_SIZE
        );

        KernAux_File file = KernAux_Store_open(&buffer_mem_store.store);
        assert(file);

        assert(KernAux_File_puts(file, hello));
        assert(strncmp(buffer, hello, strlen(hello)) == 0);
    }

    memset(buffer, 0, sizeof(buffer));

    {
        KernAux_MemStore_init(
            &buffer_mem_store,
            &buffer_mem_store_files_sized_void,
            buffer,
            SMALL_BUFFER_SIZE
        );

        KernAux_File file = KernAux_Store_open(&buffer_mem_store.store);
        assert(file);

        assert(!KernAux_File_puts(file, hello));
        assert(strncmp(buffer, hello, SMALL_BUFFER_SIZE) == 0);
        assert(strncmp(buffer, hello, strlen(hello)) != 0);
    }
}
