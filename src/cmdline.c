#include "config.h"

#include <kernaux/cmdline.h>

enum State {
    INITIAL,
    FINAL,
    WHITESPACE,
    TOKEN,
    BACKSLASHED,
};

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

    enum State state = INITIAL;

    unsigned int buffer_size = 0;

    for (unsigned int index = 0; ; ++index) {
        const char cur = cmdline[index];

        switch (state) {
        case FINAL:
            break; // Case break; loop break after switch.

        case INITIAL:
            if (cur == '\0') {
                state = FINAL;
            }
            else if (cur == ' ') {
                state = WHITESPACE;
            }
            else if (cur == '\\') {
                if (*argc >= argv_count_max) {
                    kernaux_strncpy(error_msg, "too many args", 13);
                    goto fail;
                }

                state = BACKSLASHED;
                argv[(*argc)++] = buffer;
            }
            else {
                if (*argc >= argv_count_max) {
                    kernaux_strncpy(error_msg, "too many args", 13);
                    goto fail;
                }

                if (buffer_size >= arg_size_max) {
                    kernaux_strncpy(error_msg, "arg too long", 12);
                    goto fail;
                }

                state = TOKEN;
                argv[(*argc)++] = buffer;
                *(buffer++) = cur;
                ++buffer_size;
            }
            break;

        case WHITESPACE:
            if (cur == '\0') {
                state = FINAL;
            }
            else if (cur == ' ') {
            }
            else if (cur == '\\') {
                if (*argc >= argv_count_max) {
                    kernaux_strncpy(error_msg, "too many args", 13);
                    goto fail;
                }

                state = BACKSLASHED;
                argv[(*argc)++] = buffer;
            }
            else {
                if (*argc >= argv_count_max) {
                    kernaux_strncpy(error_msg, "too many args", 13);
                    goto fail;
                }

                if (buffer_size >= arg_size_max) {
                    kernaux_strncpy(error_msg, "arg too long", 12);
                    goto fail;
                }

                state = TOKEN;
                argv[(*argc)++] = buffer;
                *(buffer++) = cur;
                ++buffer_size;
            }
            break;

        case TOKEN:
            if (cur == '\0') {
                if (buffer_size >= arg_size_max) {
                    kernaux_strncpy(error_msg, "arg too long", 12);
                    goto fail;
                }

                state = FINAL;
                *(buffer++) = '\0';
                buffer_size = 0;
            }
            else if (cur == ' ') {
                if (buffer_size >= arg_size_max) {
                    kernaux_strncpy(error_msg, "arg too long", 12);
                    goto fail;
                }

                state = WHITESPACE;
                *(buffer++) = '\0';
                buffer_size = 0;
            }
            else if (cur == '\\') {
                state = BACKSLASHED;
            }
            else {
                if (buffer_size >= arg_size_max) {
                    kernaux_strncpy(error_msg, "arg too long", 12);
                    goto fail;
                }

                *(buffer++) = cur;
                ++buffer_size;
            }
            break;

        case BACKSLASHED:
            if (cur == '\0') {
                kernaux_strncpy(error_msg, "EOL after backslash", 19);
                goto fail;
            }
            else {
                if (buffer_size >= arg_size_max) {
                    kernaux_strncpy(error_msg, "arg too long", 12);
                    goto fail;
                }

                state = TOKEN;
                *(buffer++) = cur;
                ++buffer_size;
            }
            break;
        }

        if (state == FINAL) {
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
