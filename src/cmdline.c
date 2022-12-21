#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "assert.h"

#include <kernaux/cmdline.h>
#include <kernaux/macro.h>

#include <stddef.h>
#include <string.h>

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
    size_t *arg_idxs,
    size_t arg_count_max,
    size_t buffer_size
);

static bool kernaux_cmdline_iter(
    char cur,
    enum State *state,
    size_t *buffer_or_file_pos,
    char *error_msg,
    size_t *argc,
    char arg_terminator,
    char **argv,
    char *buffer,
    size_t *arg_idxs,
    size_t arg_count_max,
    size_t buffer_size
);

/*******************************
 * Implementations: public API *
 *******************************/

bool kernaux_cmdline(
    const char *const cmdline,
    char *const error_msg,
    size_t *const argc,
    char **const argv,
    char *const buffer,
    const size_t arg_count_max,
    const size_t buffer_size
) {
    KERNAUX_NOTNULL(cmdline);
    KERNAUX_NOTNULL(error_msg);
    KERNAUX_ASSERT(argc);
    KERNAUX_NOTNULL(argv);
    KERNAUX_ASSERT(arg_count_max > 0);
    KERNAUX_ASSERT(buffer_size > 0);

    return kernaux_cmdline_common(
        cmdline,
        error_msg,
        argc,
        '\0', // arg_terminator
        argv,
        buffer,
        NULL,
        arg_count_max,
        buffer_size
    );
}

/*********************************
 * Implementation: main function *
 *********************************/

#define CLEAR do {                                                        \
    *argc = 0;                                                            \
    if (argv)     memset(argv,     0,    sizeof(char*) * arg_count_max);  \
    if (buffer)   memset(buffer,   '\0', buffer_size);                    \
    if (arg_idxs) memset(arg_idxs, 0,    sizeof(size_t) * arg_count_max); \
} while (0)

bool kernaux_cmdline_common(
    const char *const cmdline,
    char *const error_msg,
    size_t *const argc,
    char arg_terminator,
    char **const argv,
    char *const buffer,
    size_t *const arg_idxs,
    const size_t arg_count_max,
    const size_t buffer_size
) {
    KERNAUX_NOTNULL(cmdline);
    KERNAUX_NOTNULL(error_msg);
    KERNAUX_ASSERT(argc);
    (void)arg_idxs;

    memset(error_msg, '\0', KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX);
    CLEAR;

    if (cmdline[0] == '\0') return true;

    enum State state = INITIAL;
    size_t buffer_or_file_pos = 0;

    for (size_t index = 0; state != FINAL; ++index) {
        const bool result = kernaux_cmdline_iter(
            cmdline[index],
            &state,
            &buffer_or_file_pos,
            error_msg,
            argc,
            arg_terminator,
            argv,
            buffer,
            arg_idxs,
            arg_count_max,
            buffer_size
        );
        if (!result) goto fail;
    }

    return true;

fail:
    CLEAR;
    return false;
}

/**************************************
 * Implementation: iteration function *
 **************************************/

#define FAIL(msg) do {      \
    strcpy(error_msg, msg); \
    return false;           \
} while (0)

#define PUT_CHAR(char) do {                                  \
    if (buffer_size && *buffer_or_file_pos >= buffer_size) { \
        FAIL("EOF or buffer overflow");                      \
    }                                                        \
    if (buffer) {                                            \
        buffer[*buffer_or_file_pos] = char;                  \
    }                                                        \
    ++(*buffer_or_file_pos);                                 \
} while (0)

#define PUT_ARG do {                                \
    if (arg_count_max && *argc >= arg_count_max) {  \
        FAIL("too many args");                      \
    }                                               \
    if (argv && buffer) {                           \
        argv[*argc] = &buffer[*buffer_or_file_pos]; \
    }                                               \
    if (arg_idxs) {                                 \
        arg_idxs[*argc] = *buffer_or_file_pos;      \
    }                                               \
    ++(*argc);                                      \
} while (0)

#define PUT_ARG_AND_CHAR(char) do {                          \
    if (arg_count_max && *argc >= arg_count_max) {           \
        FAIL("too many args");                               \
    }                                                        \
    if (buffer_size && *buffer_or_file_pos >= buffer_size) { \
        FAIL("EOF or buffer overflow");                      \
    }                                                        \
    if (argv && buffer) {                                    \
        argv[*argc] = &buffer[*buffer_or_file_pos];          \
        buffer[*buffer_or_file_pos] = char;                  \
    }                                                        \
    if (arg_idxs) {                                          \
        arg_idxs[*argc] = *buffer_or_file_pos;               \
    }                                                        \
    ++(*argc);                                               \
    ++(*buffer_or_file_pos);                                 \
} while (0)

bool kernaux_cmdline_iter(
    const char cur,
    enum State *const state,
    size_t *const buffer_or_file_pos,
    char *const error_msg,
    size_t *const argc,
    char arg_terminator,
    char **const argv,
    char *const buffer,
    size_t *const arg_idxs,
    const size_t arg_count_max,
    const size_t buffer_size
) {
    switch (*state) {
    case FINAL:
        break;

    case INITIAL:
        if (cur == '\0') {
            *state = FINAL;
        } else if (cur == ' ') {
            *state = WHITESPACE;
        } else if (cur == '\\') {
            *state = BACKSLASH;
            PUT_ARG;
        } else if (cur == '"') {
            *state = QUOTE;
            PUT_ARG;
        } else {
            *state = TOKEN;
            PUT_ARG_AND_CHAR(cur);
        }
        break;

    case WHITESPACE:
        if (cur == '\0') {
            *state = FINAL;
        } else if (cur == ' ') {
            // do nothing
        } else if (cur == '\\') {
            *state = BACKSLASH;
            PUT_ARG;
        } else if (cur == '"') {
            *state = QUOTE;
            PUT_ARG;
        } else {
            *state = TOKEN;
            PUT_ARG_AND_CHAR(cur);
        }
        break;

    case TOKEN:
        if (cur == '\0') {
            *state = FINAL;
            PUT_CHAR(arg_terminator);
        } else if (cur == ' ') {
            *state = WHITESPACE;
            PUT_CHAR(arg_terminator);
        } else if (cur == '\\') {
            *state = BACKSLASH;
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
            *state = TOKEN;
            PUT_CHAR(cur);
        }
        break;

    case QUOTE:
        if (cur == '\0') {
            FAIL("EOL inside quote");
        } else if (cur == '\\') {
            *state = QUOTE_BACKSLASH;
        } else if (cur == '"') {
            *state = WHITESPACE;
            PUT_CHAR(arg_terminator);
        } else {
            PUT_CHAR(cur);
        }
        break;

    case QUOTE_BACKSLASH:
        if (cur == '\0') {
            FAIL("EOL after backslash inside quote");
        } else {
            *state = QUOTE;
            PUT_CHAR(cur);
        }
        break;
    }

    return true;
}
