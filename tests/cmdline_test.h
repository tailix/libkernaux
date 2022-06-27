#ifndef KERNAUX_INCLUDED_TESTS_CMDLINE_TEST
#define KERNAUX_INCLUDED_TESTS_CMDLINE_TEST

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

void test(
    const char *cmdline,
    size_t arg_count_max,
    size_t buffer_size,

    bool expected_result,
    const char *expected_error_msg,
    size_t expected_argc,
    const char *const *const expected_argv
);

#ifdef __cplusplus
}
#endif

#endif
