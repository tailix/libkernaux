#include "cmdline_test.h"

#include <kernaux/cmdline.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define ARG_COUNT_MAX 100
#define BUFFER_SIZE 4096

void test(
    const char *const cmdline,
    size_t arg_count_max,
    size_t buffer_size,

    const bool expected_result,
    const char *const expected_error_msg,
    size_t expected_argc,
    const char *const *const expected_argv
) {
    if (arg_count_max == 0) arg_count_max = ARG_COUNT_MAX;
    if (buffer_size   == 0) buffer_size   = BUFFER_SIZE;

    char *error_msg = malloc(KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX);
    size_t argc = 1234;
    char **const argv = malloc(sizeof(char*) * arg_count_max);
    size_t *arg_idxs = malloc(sizeof(size_t) * arg_count_max);
    char *const buffer = malloc(buffer_size);

    assert(error_msg);
    assert(argv);
    assert(buffer);

    {
        memset(error_msg, 'x', KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX);
        memset(argv,      0,   sizeof(char*) * arg_count_max);
        memset(arg_idxs,  0,   sizeof(size_t) * arg_count_max);
        memset(buffer,    'x', buffer_size);

        assert(
            kernaux_cmdline(
                cmdline,
                error_msg,
                &argc,
                argv,
                buffer,
                arg_count_max,
                buffer_size
            ) == !!expected_result
        );

        assert(strcmp(error_msg, expected_error_msg) == 0);
        assert(argc == expected_argc);

        if (expected_argv) {
            for (size_t index = 0; index < argc; ++index) {
                assert(strcmp(argv[index], expected_argv[index]) == 0);
            }
        }

        for (size_t index = argc; index < arg_count_max; ++index) {
            assert(argv[index] == NULL);
        }
    }

    free(error_msg);
    free(argv);
    free(arg_idxs);
    free(buffer);
}
