#include "config.h"

#include <kernaux/cmdline.h>
#include <kernaux/stdlib.h>

#include <stddef.h>

enum State {
    INITIAL,
    FINAL,
    WHITESPACE,
    TOKEN,
    BACKSLASHED,
};

bool kernaux_cmdline_parse(
    const char *const cmdline,
    char *error_msg,
    unsigned int *const argc,
    char **argv,
    char *buffer,
    const unsigned int argv_count_max,
    const unsigned int arg_size_max
) {
    if (
        cmdline == NULL ||
        error_msg == NULL ||
        argc == NULL ||
        argv == NULL ||
        argv_count_max == 0 ||
        arg_size_max == 0
    ) {
        return false;
    }

    kernaux_memset(error_msg, '\0', KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX);
    *argc = 0;

    for (unsigned int index = 0; index < argv_count_max; ++index) {
        argv[index] = NULL;
    }

    kernaux_memset(buffer, '\0', argv_count_max * arg_size_max);

    if (cmdline[0] == '\0') {
        return true;
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

    return true;

fail:
    *argc = 0;

    for (unsigned int index = 0; index < argv_count_max; ++index) {
        argv[index] = NULL;
    }

    kernaux_memset(buffer, '\0', argv_count_max * arg_size_max);

    return false;
}
