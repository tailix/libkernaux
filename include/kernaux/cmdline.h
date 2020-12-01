#ifndef KERNAUX_INCLUDED_CMDLINE
#define KERNAUX_INCLUDED_CMDLINE 1

#include <kernaux/stdlib.h>

#define KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX 256
#define KERNAUX_CMDLINE_ERROR_MSG_SLEN_MAX \
  (KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX - 1)

#ifdef __cplusplus
extern "C" {
#endif

kernaux_bool kernaux_cmdline_parse(
    const char *cmdline,
    char *error_msg,
    unsigned int *argc,
    char **argv,
    char *buffer,
    unsigned int argv_count_max,
    unsigned int arg_size_max
);

#ifdef __cplusplus
}
#endif

#endif
