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

static int  MyFile_getc  (void *file);
static int  MyFile_putc  (void *file, unsigned char c);
static void MyFile_rewind(void *file);

struct MyFile MyFile_create(char *const ptr, const size_t size)
{
    struct MyFile my_file;
    my_file.file.getc = MyFile_getc;
    my_file.file.putc = MyFile_putc;
    my_file.file.gets  = NULL; // "gets"  has a default implementation
    my_file.file.puts  = NULL; // "puts"  has a default implementation
    my_file.file.read  = NULL; // "read"  has a default implementation
    my_file.file.write = NULL; // "write" has a default implementation
    my_file.file.rewind = MyFile_rewind;
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

void MyFile_rewind(void *const file)
{
    const MyFile my_file = file;
    my_file->pos = 0;
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
    char tmp_buffer[20];
    size_t count;

    char data[6];
    memset(&data[0], 0xf0, 3);
    memset(&data[3], 0xff, 3);


    // Create file
    struct MyFile my_file = MyFile_create(buffer, sizeof(buffer));

    // Write "Hello, World!" to the file
    assert(KernAux_File_puts(&my_file.file, hello) == true);

    // Write null character to the file
    assert(KernAux_File_putc(&my_file.file, '\0') != KERNAUX_EOF);

    // Write random data to the file
    count = sizeof(data);
    assert(KernAux_File_write(&my_file.file, data, &count) == true);
    assert(count == sizeof(data));

    // Seek to the beginning of the file
    KernAux_File_rewind(&my_file.file);

    // Read a line from the file
    count = 14;
    assert(KernAux_File_gets(&my_file.file, tmp_buffer, &count) == true);
    assert(count == 14);

    // Read random data from the file
    count = 6;
    assert(KernAux_File_read(&my_file.file, &tmp_buffer[14], &count) == true);
    assert(count == 6);

    // Read a single character from the file
    assert(KernAux_File_getc(&my_file.file) == KERNAUX_EOF);


    assert(strcmp(&buffer[0], hello) == 0);
    assert(memcmp(&buffer[14], data, sizeof(data)) == 0);
    assert(strcmp(&tmp_buffer[0], hello) == 0);
    assert(memcmp(&tmp_buffer[14], data, sizeof(data)) == 0);
}
