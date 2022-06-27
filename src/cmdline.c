#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/cmdline.h>
#include <kernaux/generic/file.h>

#include "libc.h"

enum State {
    INITIAL,
    FINAL,
    WHITESPACE,
    TOKEN,
    BACKSLASH,
    QUOTE,
    QUOTE_BACKSLASH,
};

static bool kernaux_cmdline_common(
    const char *cmdline,
    char *error_msg,
    size_t *argc,
    char arg_terminator,
    char **argv,
    char *buffer,
    size_t argv_count_max,
    size_t buffer_size,
    KernAux_File file
);

/*****************************
 * Implementations: main API *
 *****************************/

bool kernaux_cmdline(
    const char *const cmdline,
    char *const error_msg,
    size_t *const argc,
    char **const argv,
    char *const buffer,
    const size_t argv_count_max,
    const size_t buffer_size
) {
    KERNAUX_ASSERT(cmdline);
    KERNAUX_ASSERT(error_msg);
    KERNAUX_ASSERT(argc);
    KERNAUX_ASSERT(argv);
    KERNAUX_ASSERT(argv_count_max > 0);
    KERNAUX_ASSERT(buffer_size > 0);

    return kernaux_cmdline_common(
        cmdline,
        error_msg,
        argc,
        '\0', // arg_terminator
        argv,
        buffer,
        argv_count_max,
        buffer_size,
        NULL
    );
}

bool kernaux_cmdline_file(
    const char *const cmdline,
    char *const error_msg,
    size_t *const argc,
    const KernAux_File file
) {
    KERNAUX_ASSERT(cmdline);
    KERNAUX_ASSERT(error_msg);
    KERNAUX_ASSERT(argc);
    KERNAUX_ASSERT(file);

    return kernaux_cmdline_common(
        cmdline,
        error_msg,
        argc,
        '\0', // arg_terminator
        NULL,
        NULL,
        0,
        0,
        file
    );
}

/******************************************
 * Implementation: main internal function *
 ******************************************/

#define FAIL(msg) do {      \
    strcpy(error_msg, msg); \
    goto fail;              \
} while (0)

#define PUT_CHAR(char) do {                                          \
    if (buffer_size && buffer_pos >= buffer_size) {                  \
        FAIL("buffer overflow");                                     \
    }                                                                \
    if (buffer) {                                                    \
        buffer[buffer_pos++] = char;                                 \
    }                                                                \
    if (file) {                                                      \
        if (KernAux_File_putc(file, char) == KERNAUX_EOF) goto fail; \
    }                                                                \
} while (0)

#define PUT_ARG do {                                 \
    if (argv_count_max && *argc >= argv_count_max) { \
        FAIL("too many args");                       \
    }                                                \
    if (argv && buffer) {                            \
        argv[*argc] = &buffer[buffer_pos];           \
    }                                                \
    ++(*argc);                                       \
} while (0)

#define PUT_ARG_AND_CHAR(char) do {                                  \
    if (argv_count_max && *argc >= argv_count_max) {                 \
        FAIL("too many args");                                       \
    }                                                                \
    if (buffer_size && buffer_pos >= buffer_size) {                  \
        FAIL("buffer overflow");                                     \
    }                                                                \
    if (argv && buffer) {                                            \
        argv[*argc] = &buffer[buffer_pos];                           \
        buffer[buffer_pos++] = char;                                 \
    }                                                                \
    if (file) {                                                      \
        if (KernAux_File_putc(file, char) == KERNAUX_EOF) goto fail; \
    }                                                                \
    ++(*argc);                                                       \
} while (0)

bool kernaux_cmdline_common(
    const char *const cmdline,
    char *const error_msg,
    size_t *const argc,
    char arg_terminator,
    char **const argv,
    char *const buffer,
    const size_t argv_count_max,
    const size_t buffer_size,
    const KernAux_File file
) {
    KERNAUX_ASSERT(cmdline);
    KERNAUX_ASSERT(error_msg);
    KERNAUX_ASSERT(argc);
    (void)file;

    memset(error_msg, '\0', KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX);
    *argc = 0;
    if (argv) memset(argv, 0, sizeof(char*) * argv_count_max);
    if (buffer) memset(buffer, '\0', buffer_size);

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
                state = BACKSLASH;
                PUT_ARG;
            } else if (cur == '"') {
                state = QUOTE;
                PUT_ARG;
            } else {
                state = TOKEN;
                PUT_ARG_AND_CHAR(cur);
            }
            break;

        case WHITESPACE:
            if (cur == '\0') {
                state = FINAL;
            } else if (cur == ' ') {
                // do nothing
            } else if (cur == '\\') {
                state = BACKSLASH;
                PUT_ARG;
            } else if (cur == '"') {
                state = QUOTE;
                PUT_ARG;
            } else {
                state = TOKEN;
                PUT_ARG_AND_CHAR(cur);
            }
            break;

        case TOKEN:
            if (cur == '\0') {
                state = FINAL;
                PUT_CHAR(arg_terminator);
            } else if (cur == ' ') {
                state = WHITESPACE;
                PUT_CHAR(arg_terminator);
            } else if (cur == '\\') {
                state = BACKSLASH;
            } else if (cur == '"') {
                FAIL("unescaped quotation mark");
            } else {
                PUT_CHAR(cur);
            }
            break;

        case BACKSLASH:
            if (cur == '\0') {
                FAIL("EOL after backslash");
            } else {
                state = TOKEN;
                PUT_CHAR(cur);
            }
            break;

        case QUOTE:
            if (cur == '\0') {
                FAIL("EOL inside quote");
            } else if (cur == '\\') {
                state = QUOTE_BACKSLASH;
            } else if (cur == '"') {
                state = WHITESPACE;
                PUT_CHAR(arg_terminator);
            } else {
                PUT_CHAR(cur);
            }
            break;

        case QUOTE_BACKSLASH:
            if (cur == '\0') {
                FAIL("EOL after backslash inside quote");
            } else {
                state = QUOTE;
                PUT_CHAR(cur);
            }
            break;
        }

        if (state == FINAL) break;
    }

    return true;

fail:
    *argc = 0;
    if (argv) memset(argv, 0, sizeof(char*) * argv_count_max);
    if (buffer) memset(buffer, '\0', buffer_size);
    return false;
}
