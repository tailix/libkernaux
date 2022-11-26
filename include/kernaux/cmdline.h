#ifndef KERNAUX_INCLUDED_CMDLINE
#define KERNAUX_INCLUDED_CMDLINE

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

#define KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX 256
#define KERNAUX_CMDLINE_ERROR_MSG_SLEN_MAX \
  (KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX - 1)

bool kernaux_cmdline(
    const char *cmdline,
    char *error_msg,
    size_t *argc,
    char **argv,
    char *buffer,
    size_t arg_count_max,
    size_t buffer_size
);

#ifdef __cplusplus
}
#endif

#endif
