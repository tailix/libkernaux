#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/cmdline.h>
#include <kernaux/libc.h>

enum State {
    INITIAL,
    FINAL,
    WHITESPACE,
    TOKEN,
    BACKSLASH,
    QUOTE,
    QUOTE_BACKSLASH,
};

bool kernaux_cmdline(
    const char *const cmdline,
    char *error_msg,
    size_t *const argc,
    char **argv,
    char *buffer,
    const size_t argv_count_max,
    const size_t arg_size_max
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

    memset(error_msg, '\0', KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX);
    *argc = 0;

    for (size_t index = 0; index < argv_count_max; ++index) {
        argv[index] = NULL;
    }

    memset(buffer, '\0', argv_count_max * arg_size_max);

    if (cmdline[0] == '\0') {
        return true;
    }

    enum State state = INITIAL;

    size_t buffer_size = 0;

    for (size_t index = 0; ; ++index) {
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
                    strcpy(error_msg, "too many args");
                    goto fail;
                }

                state = BACKSLASH;
                argv[(*argc)++] = buffer;
            }
            else if (cur == '"') {
                if (*argc >= argv_count_max) {
                    strcpy(error_msg, "too many args");
                    goto fail;
                }

                state = QUOTE;
                argv[(*argc)++] = buffer;
            }
            else {
                if (*argc >= argv_count_max) {
                    strcpy(error_msg, "too many args");
                    goto fail;
                }

                if (buffer_size >= arg_size_max) {
                    strcpy(error_msg, "arg too long");
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
                    strcpy(error_msg, "too many args");
                    goto fail;
                }

                state = BACKSLASH;
                argv[(*argc)++] = buffer;
            }
            else if (cur == '"') {
                if (*argc >= argv_count_max) {
                    strcpy(error_msg, "too many args");
                    goto fail;
                }

                state = QUOTE;
                argv[(*argc)++] = buffer;
            }
            else {
                if (*argc >= argv_count_max) {
                    strcpy(error_msg, "too many args");
                    goto fail;
                }

                if (buffer_size >= arg_size_max) {
                    strcpy(error_msg, "arg too long");
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
                    strcpy(error_msg, "arg too long");
                    goto fail;
                }

                state = FINAL;
                *(buffer++) = '\0';
                buffer_size = 0;
            }
            else if (cur == ' ') {
                if (buffer_size >= arg_size_max) {
                    strcpy(error_msg, "arg too long");
                    goto fail;
                }

                state = WHITESPACE;
                *(buffer++) = '\0';
                buffer_size = 0;
            }
            else if (cur == '\\') {
                state = BACKSLASH;
            }
            else if (cur == '"') {
                strcpy(error_msg, "unescaped quotation mark");
                goto fail;
            }
            else {
                if (buffer_size >= arg_size_max) {
                    strcpy(error_msg, "arg too long");
                    goto fail;
                }

                *(buffer++) = cur;
                ++buffer_size;
            }
            break;

        case BACKSLASH:
            if (cur == '\0') {
                strcpy(error_msg, "EOL after backslash");
                goto fail;
            }
            else {
                if (buffer_size >= arg_size_max) {
                    strcpy(error_msg, "arg too long");
                    goto fail;
                }

                state = TOKEN;
                *(buffer++) = cur;
                ++buffer_size;
            }
            break;

        case QUOTE:
            if (cur == '\0') {
                strcpy(error_msg, "EOL inside quote");
                goto fail;
            }
            else if (cur == '\\') {
                state = QUOTE_BACKSLASH;
            }
            else if (cur == '"') {
                if (buffer_size >= arg_size_max) {
                    strcpy(error_msg, "arg too long");
                    goto fail;
                }

                state = WHITESPACE;
                *(buffer++) = '\0';
                buffer_size = 0;
            }
            else {
                if (buffer_size >= arg_size_max) {
                    strcpy(error_msg, "arg too long");
                    goto fail;
                }

                *(buffer++) = cur;
                ++buffer_size;
            }
            break;

        case QUOTE_BACKSLASH:
            if (cur == '\0') {
                strcpy(error_msg, "EOL after backslash inside quote");
                goto fail;
            }
            else {
                if (buffer_size >= arg_size_max) {
                    strcpy(error_msg, "arg too long");
                    goto fail;
                }

                state = QUOTE;
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

    for (size_t index = 0; index < argv_count_max; ++index) {
        argv[index] = NULL;
    }

    memset(buffer, '\0', argv_count_max * arg_size_max);

    return false;
}
