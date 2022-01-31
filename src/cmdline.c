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
    char *const error_msg,
    size_t *const argc,
    char **const argv,
    char *const buffer,
    const size_t argv_count_max,
    const size_t buffer_size
) {
    if (
        cmdline == NULL ||
        error_msg == NULL ||
        argc == NULL ||
        argv == NULL ||
        argv_count_max == 0 ||
        buffer_size == 0
    ) {
        return false;
    }

    memset(error_msg, '\0', KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX);
    *argc = 0;
    memset(argv, 0, sizeof(char*) * argv_count_max);
    memset(buffer, '\0', buffer_size);

    if (cmdline[0] == '\0') return true;

    enum State state = INITIAL;
    size_t buffer_pos = 0;

    for (size_t index = 0; ; ++index) {
        const char cur = cmdline[index];

        switch (state) {
        case FINAL:
            break; // Case break; loop break after switch.

        case INITIAL:
            if (cur == '\0') {
                state = FINAL;
            } else if (cur == ' ') {
                state = WHITESPACE;
            } else if (cur == '\\') {
                if (*argc >= argv_count_max) {
                    strcpy(error_msg, "too many args");
                    goto fail;
                }

                state = BACKSLASH;
                argv[(*argc)++] = &buffer[buffer_pos];
            } else if (cur == '"') {
                if (*argc >= argv_count_max) {
                    strcpy(error_msg, "too many args");
                    goto fail;
                }

                state = QUOTE;
                argv[(*argc)++] = &buffer[buffer_pos];
            } else {
                if (*argc >= argv_count_max) {
                    strcpy(error_msg, "too many args");
                    goto fail;
                }

                if (buffer_pos >= buffer_size) {
                    strcpy(error_msg, "buffer overflow");
                    goto fail;
                }

                state = TOKEN;
                argv[(*argc)++] = &buffer[buffer_pos];
                buffer[buffer_pos++] = cur;
            }
            break;

        case WHITESPACE:
            if (cur == '\0') {
                state = FINAL;
            } else if (cur == ' ') {
                // do nothing
            } else if (cur == '\\') {
                if (*argc >= argv_count_max) {
                    strcpy(error_msg, "too many args");
                    goto fail;
                }

                state = BACKSLASH;
                argv[(*argc)++] = &buffer[buffer_pos];
            } else if (cur == '"') {
                if (*argc >= argv_count_max) {
                    strcpy(error_msg, "too many args");
                    goto fail;
                }

                state = QUOTE;
                argv[(*argc)++] = &buffer[buffer_pos];
            } else {
                if (*argc >= argv_count_max) {
                    strcpy(error_msg, "too many args");
                    goto fail;
                }

                if (buffer_pos >= buffer_size) {
                    strcpy(error_msg, "buffer overflow");
                    goto fail;
                }

                state = TOKEN;
                argv[(*argc)++] = &buffer[buffer_pos];
                buffer[buffer_pos++] = cur;
            }
            break;

        case TOKEN:
            if (cur == '\0') {
                if (buffer_pos >= buffer_size) {
                    strcpy(error_msg, "buffer overflow");
                    goto fail;
                }

                state = FINAL;
                buffer[buffer_pos++] = '\0';
            } else if (cur == ' ') {
                if (buffer_pos >= buffer_size) {
                    strcpy(error_msg, "buffer overflow");
                    goto fail;
                }

                state = WHITESPACE;
                buffer[buffer_pos++] = '\0';
            } else if (cur == '\\') {
                state = BACKSLASH;
            } else if (cur == '"') {
                strcpy(error_msg, "unescaped quotation mark");
                goto fail;
            } else {
                if (buffer_pos >= buffer_size) {
                    strcpy(error_msg, "buffer overflow");
                    goto fail;
                }

                buffer[buffer_pos++] = cur;
            }
            break;

        case BACKSLASH:
            if (cur == '\0') {
                strcpy(error_msg, "EOL after backslash");
                goto fail;
            } else {
                if (buffer_pos >= buffer_size) {
                    strcpy(error_msg, "buffer overflow");
                    goto fail;
                }

                state = TOKEN;
                buffer[buffer_pos++] = cur;
            }
            break;

        case QUOTE:
            if (cur == '\0') {
                strcpy(error_msg, "EOL inside quote");
                goto fail;
            } else if (cur == '\\') {
                state = QUOTE_BACKSLASH;
            } else if (cur == '"') {
                if (buffer_pos >= buffer_size) {
                    strcpy(error_msg, "buffer overflow");
                    goto fail;
                }

                state = WHITESPACE;
                buffer[buffer_pos++] = '\0';
            } else {
                if (buffer_pos >= buffer_size) {
                    strcpy(error_msg, "buffer overflow");
                    goto fail;
                }

                buffer[buffer_pos++] = cur;
            }
            break;

        case QUOTE_BACKSLASH:
            if (cur == '\0') {
                strcpy(error_msg, "EOL after backslash inside quote");
                goto fail;
            } else {
                if (buffer_pos >= buffer_size) {
                    strcpy(error_msg, "buffer overflow");
                    goto fail;
                }

                state = QUOTE;
                buffer[buffer_pos++] = cur;
            }
            break;
        }

        if (state == FINAL) break;
    }

    return true;

fail:
    *argc = 0;
    memset(argv, 0, sizeof(char*) * argv_count_max);
    memset(buffer, '\0', buffer_size);
    return false;
}
