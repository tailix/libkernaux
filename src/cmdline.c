#include "config.h"

#include <kernaux/cmdline.h>

kernaux_bool kernaux_cmdline_parse(
    const char *const cmdline,
    char *error_msg,
    unsigned int *const argc,
    char **argv,
    char *buffer,
    const unsigned int argv_count_max,
    const unsigned int arg_size_max
) {
    if (
        cmdline == KERNAUX_NULL ||
        error_msg == KERNAUX_NULL ||
        argc == KERNAUX_NULL ||
        argv == KERNAUX_NULL ||
        argv_count_max == 0 ||
        arg_size_max == 0
    ) {
        return KERNAUX_FALSE;
    }

    kernaux_memset(error_msg, '\0', KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX);
    *argc = 0;

    for (unsigned int index = 0; index < argv_count_max; ++index) {
        argv[index] = KERNAUX_NULL;
    }

    kernaux_memset(buffer, '\0', argv_count_max * arg_size_max);

    return KERNAUX_TRUE;
}
