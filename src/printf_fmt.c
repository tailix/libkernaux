/**
 * The code was taken from Marco Paland's printf.
 *
 * Copyright (c) 2014-2019 Marco Paland <info@paland.com>
 * Copyright (c) 2021-2022 Alex Kotov
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "assert.h"

#include <kernaux/printf_fmt.h>

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct KernAux_PrintfFmt_Spec *Spec;

static void parse_flags    (Spec spec, const char **format);
static void parse_width    (Spec spec, const char **format);
static void parse_precision(Spec spec, const char **format);
static void parse_length   (Spec spec, const char **format);
static void parse_type     (Spec spec, const char **format);

static unsigned int _atoi(const char** str);

/***********************************
 * Public function implementations *
 ***********************************/

struct KernAux_PrintfFmt_Spec KernAux_PrintfFmt_Spec_create_out(
    const char **const format
) {
    KERNAUX_NOTNULL(format);

    const struct KernAux_PrintfFmt_Spec spec =
        KernAux_PrintfFmt_Spec_create(*format);
    *format = spec.format_limit;
    return spec;
}

struct KernAux_PrintfFmt_Spec KernAux_PrintfFmt_Spec_create_out_new(
    const char *const format,
    const char **const new_format
) {
    KERNAUX_NOTNULL(format);
    KERNAUX_NOTNULL(new_format);

    *new_format = NULL;
    const struct KernAux_PrintfFmt_Spec spec =
        KernAux_PrintfFmt_Spec_create(format);
    *new_format = spec.format_limit;
    return spec;
}

struct KernAux_PrintfFmt_Spec KernAux_PrintfFmt_Spec_create(const char *format)
{
    KERNAUX_NOTNULL(format);

    struct KernAux_PrintfFmt_Spec spec;

    spec.format_start = format;

    spec.flags = 0u;
    spec.width = 0u;
    spec.precision = 0u;
    spec.type = KERNAUX_PRINTF_FMT_TYPE_NONE;
    spec.base = 0;

    spec.set_width = false;
    spec.set_precision = false;

    parse_flags(&spec, &format);
    parse_width(&spec, &format);
    parse_precision(&spec, &format);
    parse_length(&spec, &format);
    parse_type(&spec, &format);

    spec.format_limit = format;

    return spec;
}

void KernAux_PrintfFmt_Spec_set_width(const Spec spec, const int width)
{
    KERNAUX_NOTNULL(spec);

    if (width < 0) {
        spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_LEFT; // reverse padding
        spec->width = (unsigned int)-width;
    } else {
        spec->width = (unsigned int)width;
    }
}

void KernAux_PrintfFmt_Spec_set_precision(const Spec spec, const int precision)
{
    KERNAUX_NOTNULL(spec);

    spec->precision = precision > 0 ? (unsigned int)precision : 0u;
}

/************************************
 * Private function implementations *
 ************************************/

void parse_flags(const Spec spec, const char **const format)
{
    KERNAUX_NOTNULL(spec);
    KERNAUX_NOTNULL(format);
    KERNAUX_ASSERT(*format);

    bool running = true;
    do {
        switch (**format) {
            case '0':
                spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_ZEROPAD;
                ++(*format);
                break;
            case '-':
                spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_LEFT;
                ++(*format);
                break;
            case '+':
                spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_PLUS;
                ++(*format);
                break;
            case ' ':
                spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_SPACE;
                ++(*format);
                break;
            case '#':
                spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_HASH;
                ++(*format);
                break;
            default: running = false; break;
        }
    } while (running);
}

void parse_width(const Spec spec, const char **const format)
{
    KERNAUX_NOTNULL(spec);
    KERNAUX_NOTNULL(format);
    KERNAUX_ASSERT(*format);

    if (isdigit(**format)) {
        spec->width = _atoi(format);
        spec->set_width = false;
    } else if (**format == '*') {
        ++(*format);
        spec->set_width = true;
    } else {
        spec->set_width = false;
    }
}

void parse_precision(const Spec spec, const char **const format)
{
    KERNAUX_NOTNULL(spec);
    KERNAUX_NOTNULL(format);
    KERNAUX_ASSERT(*format);

    if (**format == '.') {
        spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_PRECISION;
        ++(*format);
        if (isdigit(**format)) {
            spec->precision = _atoi(format);
            spec->set_precision = false;
        } else if (**format == '*') {
            ++(*format);
            spec->set_precision = true;
        } else {
            spec->set_precision = false;
        }
    } else {
        spec->set_precision = false;
    }
}

void parse_length(const Spec spec, const char **const format)
{
    KERNAUX_NOTNULL(spec);
    KERNAUX_NOTNULL(format);
    KERNAUX_ASSERT(*format);

    switch (**format) {
        case 'l':
            spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_LONG;
            ++(*format);
            if (**format == 'l') {
                spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_LONG_LONG;
                ++(*format);
            }
            break;
        case 'h':
            spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_SHORT;
            ++(*format);
            if (**format == 'h') {
                spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_CHAR;
                ++(*format);
            }
            break;
        case 't':
            if (sizeof(ptrdiff_t) == sizeof(long)) {
                spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_LONG;
            } else {
                spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_LONG_LONG;
            }
            ++(*format);
            break;
        case 'j':
            if (sizeof(ptrdiff_t) == sizeof(long)) {
                spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_LONG;
            } else {
                spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_LONG_LONG;
            }
            ++(*format);
            break;
        case 'z':
            if (sizeof(ptrdiff_t) == sizeof(long)) {
                spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_LONG;
            } else {
                spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_LONG_LONG;
            }
            ++(*format);
            break;
        default:
            break;
    }
}

void parse_type(const Spec spec, const char **const format)
{
    KERNAUX_NOTNULL(spec);
    KERNAUX_NOTNULL(format);
    KERNAUX_ASSERT(*format);

    switch (**format) {
        case 'd':
        case 'i':
        case 'u':
        case 'x':
        case 'X':
        case 'o':
        case 'b':
            // set the base
            if (**format == 'x' || **format == 'X') {
                spec->base = 16u;
            } else if (**format == 'o') {
                spec->base = 8u;
            } else if (**format == 'b') {
                spec->base = 2u;
            } else {
                spec->base = 10u;
                // no hash for dec format
                spec->flags &= ~KERNAUX_PRINTF_FMT_FLAGS_HASH;
            }
            // uppercase
            if (**format == 'X') {
                spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_UPPERCASE;
            }

            // no plus or space flag for u, x, X, o, b
            if ((**format != 'i') && (**format != 'd')) {
                spec->flags &= ~(KERNAUX_PRINTF_FMT_FLAGS_PLUS |
                                 KERNAUX_PRINTF_FMT_FLAGS_SPACE);
            }

            // ignore '0' flag when precision is given
            if (spec->flags & KERNAUX_PRINTF_FMT_FLAGS_PRECISION) {
                spec->flags &= ~KERNAUX_PRINTF_FMT_FLAGS_ZEROPAD;
            }

            // convert the integer
            if ((**format == 'i') || (**format == 'd')) {
                spec->type = KERNAUX_PRINTF_FMT_TYPE_INT;
            } else {
                spec->type = KERNAUX_PRINTF_FMT_TYPE_UINT;
            }
            ++(*format);
            break;

#ifdef ENABLE_FLOAT
        case 'f':
        case 'F':
            if (**format == 'F') {
                spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_UPPERCASE;
            }
            spec->type = KERNAUX_PRINTF_FMT_TYPE_FLOAT;
            ++(*format);
            break;

        case 'e':
        case 'E':
        case 'g':
        case 'G':
            if ((**format == 'g') || (**format == 'G')) {
                spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_ADAPT_EXP;
            }
            if ((**format == 'E') || (**format == 'G')) {
                spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_UPPERCASE;
            }
            spec->type = KERNAUX_PRINTF_FMT_TYPE_EXP;
            ++(*format);
            break;
#endif // ENABLE_FLOAT

        case 'c':
            spec->type = KERNAUX_PRINTF_FMT_TYPE_CHAR;
            ++(*format);
            break;

        case 's':
            spec->type = KERNAUX_PRINTF_FMT_TYPE_STR;
            ++(*format);
            break;

        case 'p':
            spec->width = sizeof(void*) * 2u;
            spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_ZEROPAD |
                           KERNAUX_PRINTF_FMT_FLAGS_UPPERCASE;
            spec->type = KERNAUX_PRINTF_FMT_TYPE_PTR;
            ++(*format);
            break;

        case '%':
            spec->type = KERNAUX_PRINTF_FMT_TYPE_PERCENT;
            ++(*format);
            break;

        default:
            spec->type = KERNAUX_PRINTF_FMT_TYPE_NONE;
            break;
    }
}

// internal ASCII string to unsigned int conversion
unsigned int _atoi(const char** str)
{
    const int result = atoi(*str);
    while (isdigit(**str)) (*str)++;
    return result;
}
