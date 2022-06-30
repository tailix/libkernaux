//===========
// my_file.c
//===========

// To not always use macro "KERNAUX_PROTECTED_FIELD" around the names of
// structure fields you may define "KERNAUX_ACCESS_PROTECTED" before including
// any other headers, but ONLY in the file where you implement a generic type.
//
#define KERNAUX_ACCESS_PROTECTED

//===========
// my_file.h
//===========

#include <kernaux/generic/file.h>
#include <stddef.h>

typedef struct MyFile {
    struct KernAux_File file;
    char *ptr;
    size_t size;
    size_t pos;
} *MyFile;

struct MyFile MyFile_create(char *ptr, size_t size);

//===========
// my_file.c
//===========

#include <kernaux/generic/file.h>
#include <kernaux/macro.h>
#include <stddef.h>

static int MyFile_getc(void *file);
static int MyFile_putc(void *file, unsigned char c);

struct MyFile MyFile_create(char *const ptr, const size_t size)
{
    struct MyFile my_file;
    my_file.file.getc = MyFile_getc;
    my_file.file.putc = MyFile_putc;
    my_file.file.puts = NULL; // "puts" has a default implementation
    my_file.file.write = NULL; // "write" has a default implementation
    my_file.ptr = ptr;
    my_file.size = size;
    my_file.pos = 0;
    return my_file;
}

int MyFile_getc(void *const file)
{
    const MyFile my_file = file;
    if (my_file->pos >= my_file->size) return KERNAUX_EOF;
    const unsigned char c = my_file->ptr[my_file->pos++];
    return c;
}

int MyFile_putc(void *const file, const unsigned char c)
{
    const MyFile my_file = file;
    if (my_file->pos >= my_file->size) return KERNAUX_EOF;
    my_file->ptr[my_file->pos++] = c;
    return c;
}

//========
// main.c
//========

#include <kernaux/macro.h>

#include <assert.h>
#include <string.h>

static const char *const hello = "Hello, World!";

void example_main()
{
    char buffer[20];

    {
        // Create file
        struct MyFile my_file = MyFile_create(buffer, sizeof(buffer));

        // Write "Hello, World!" to the file
        {
            const int result = KernAux_File_puts(&my_file.file, hello);
            assert(result != KERNAUX_EOF);
        }

        // Write null character to the file
        {
            const int result = KernAux_File_putc(&my_file.file, '\0');
            assert(result != KERNAUX_EOF);
        }

        char data[6];
        memset(data, 0xff, sizeof(data));

        // Write random data to the file
        {
            const int result =
                KernAux_File_write(&my_file.file, data, sizeof(data));
            assert(result != KERNAUX_EOF);
        }

        assert(strcmp(buffer, hello) == 0);
        assert(memcmp(&buffer[14], data, sizeof(data)) == 0);
    }

    {
        // Create file
        struct MyFile my_file = MyFile_create(buffer, sizeof(buffer));

        assert(KernAux_File_getc(&my_file.file) == 'H');
        assert(KernAux_File_getc(&my_file.file) == 'e');
        assert(KernAux_File_getc(&my_file.file) == 'l');
        assert(KernAux_File_getc(&my_file.file) == 'l');
        assert(KernAux_File_getc(&my_file.file) == 'o');
        assert(KernAux_File_getc(&my_file.file) == ',');
        assert(KernAux_File_getc(&my_file.file) == ' ');
        assert(KernAux_File_getc(&my_file.file) == 'W');
        assert(KernAux_File_getc(&my_file.file) == 'o');
        assert(KernAux_File_getc(&my_file.file) == 'r');
        assert(KernAux_File_getc(&my_file.file) == 'l');
        assert(KernAux_File_getc(&my_file.file) == 'd');
        assert(KernAux_File_getc(&my_file.file) == '!');
        assert(KernAux_File_getc(&my_file.file) == '\0');
        assert(KernAux_File_getc(&my_file.file) == 0xff);
        assert(KernAux_File_getc(&my_file.file) == 0xff);
        assert(KernAux_File_getc(&my_file.file) == 0xff);
        assert(KernAux_File_getc(&my_file.file) == 0xff);
        assert(KernAux_File_getc(&my_file.file) == 0xff);
        assert(KernAux_File_getc(&my_file.file) == 0xff);
        assert(KernAux_File_getc(&my_file.file) == KERNAUX_EOF);
    }
}
