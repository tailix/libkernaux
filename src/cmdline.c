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

    if (cmdline[0] == '\0') {
        return KERNAUX_TRUE;
    }

    unsigned int start = 0;

    for (unsigned int index = 1; ; ++index) {
        const char prev = cmdline[index - 1];
        const char cur  = cmdline[index];

        if ((cur == ' ' || cur == '\0') && prev != ' ') {
            const unsigned size = index - start + 1;

            if (*argc >= argv_count_max) {
                kernaux_strncpy(error_msg, "too many args", 13);
                goto fail;
            }

            if (size > arg_size_max) {
                kernaux_strncpy(error_msg, "arg too long", 12);
                goto fail;
            }

            argv[(*argc)++] = buffer;
            kernaux_strncpy(buffer, &cmdline[start], size - 1);
            buffer += size;
        }

        if (prev == ' ' && cur != ' ' && cur != '\0') {
            start = index;
        }

        if (cur == '\0') {
            break;
        }
    }

    return KERNAUX_TRUE;

fail:
    *argc = 0;

    for (unsigned int index = 0; index < argv_count_max; ++index) {
        argv[index] = KERNAUX_NULL;
    }

    kernaux_memset(buffer, '\0', argv_count_max * arg_size_max);

    return KERNAUX_FALSE;
}
