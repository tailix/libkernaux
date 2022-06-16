#include <kernaux/io.h>

#include <assert.h>
#include <string.h>

#define BUFFER_SIZE 4096

static char buffer[BUFFER_SIZE];

void example_main()
{
    struct KernAux_MemStore mem_store =
        KernAux_MemStore_create(buffer, BUFFER_SIZE);

    assert(KernAux_Store_put_char(&mem_store.store, 'H' ) == 'H' );
    assert(KernAux_Store_put_char(&mem_store.store, 'e' ) == 'e' );
    assert(KernAux_Store_put_char(&mem_store.store, 'l' ) == 'l' );
    assert(KernAux_Store_put_char(&mem_store.store, 'l' ) == 'l' );
    assert(KernAux_Store_put_char(&mem_store.store, 'o' ) == 'o' );
    assert(KernAux_Store_put_char(&mem_store.store, '!' ) == '!' );
    assert(KernAux_Store_put_char(&mem_store.store, '\0') == '\0');

    assert(strncmp(buffer, "Hello!", BUFFER_SIZE) == 0);
}
