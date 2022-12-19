#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <assert.h>

#ifndef __USE_POSIX2
#define __USE_POSIX2
#endif
#include <stdio.h>

void test_main()
{
    {
        FILE *const print_file = popen("./multiboot2_header_print0", "r");
        FILE *const text_file =
            fopen("../fixtures/multiboot2_header_example0.txt", "r");
        assert(print_file != NULL);
        assert(text_file != NULL);

        while (!feof(text_file)) {
            assert(fgetc(print_file) == fgetc(text_file));
        }

        assert(pclose(print_file) == 0);
        assert(fclose(text_file) == 0);
    }

    {
        FILE *const print_file = popen("./multiboot2_header_print1", "r");
        FILE *const text_file =
            fopen("../fixtures/multiboot2_header_example1.txt", "r");
        assert(print_file != NULL);
        assert(text_file != NULL);

        while (!feof(text_file)) {
            assert(fgetc(print_file) == fgetc(text_file));
        }

        assert(pclose(print_file) == 0);
        assert(fclose(text_file) == 0);
    }

    {
        FILE *const print_file = popen("./multiboot2_header_print2", "r");
        FILE *const text_file =
            fopen("../fixtures/multiboot2_header_example2.txt", "r");
        assert(print_file != NULL);
        assert(text_file != NULL);

        while (!feof(text_file)) {
            assert(fgetc(print_file) == fgetc(text_file));
        }

        assert(pclose(print_file) == 0);
        assert(fclose(text_file) == 0);
    }
}
