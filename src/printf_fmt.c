/**
 * The code was taken from Marco Paland's printf.
 *
 * Copyright (c) 2014-2019 Marco Paland <info@paland.com>
 * Copyright (c) 2021-2022 Alex Kotov
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/printf_fmt.h>

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

static unsigned int _atoi(const char** str);

struct KernAux_PrintfFmt_Spec KernAux_PrintfFmt_Spec_create()
{
    struct KernAux_PrintfFmt_Spec spec;
    KernAux_PrintfFmt_Spec_init(&spec);
    return spec;
}

void KernAux_PrintfFmt_Spec_init(struct KernAux_PrintfFmt_Spec *const spec)
{
    KERNAUX_ASSERT(spec);

    spec->flags = 0u;
    spec->width = 0u;
    spec->precision = 0u;
    spec->type = KERNAUX_PRINTF_FMT_TYPE_NONE;
    spec->base = 0;

    spec->set_width = false;
    spec->set_precision = false;
}

const char *KernAux_PrintfFmt_Spec_parse(struct KernAux_PrintfFmt_Spec *spec, const char *format)
{
    KERNAUX_ASSERT(spec);
    KERNAUX_ASSERT(format);

    KernAux_PrintfFmt_Spec_parse_flags(spec, &format);
    KernAux_PrintfFmt_Spec_parse_width(spec, &format);
    KernAux_PrintfFmt_Spec_parse_precision(spec, &format);
    KernAux_PrintfFmt_Spec_parse_length(spec, &format);
    KernAux_PrintfFmt_Spec_parse_type(spec, &format);

    return format;
}

void KernAux_PrintfFmt_Spec_parse_flags(struct KernAux_PrintfFmt_Spec *const spec, const char **const format)
{
    KERNAUX_ASSERT(spec);
    KERNAUX_ASSERT(format);
    KERNAUX_ASSERT(*format);

    bool running = true;
    do {
        switch (**format) {
            case '0': spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_ZEROPAD; ++(*format); break;
            case '-': spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_LEFT;    ++(*format); break;
            case '+': spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_PLUS;    ++(*format); break;
            case ' ': spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_SPACE;   ++(*format); break;
            case '#': spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_HASH;    ++(*format); break;
            default: running = false; break;
        }
    } while (running);
}

void KernAux_PrintfFmt_Spec_parse_width(struct KernAux_PrintfFmt_Spec *const spec, const char **const format)
{
    KERNAUX_ASSERT(spec);
    KERNAUX_ASSERT(format);
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

void KernAux_PrintfFmt_Spec_parse_precision(struct KernAux_PrintfFmt_Spec *const spec, const char **const format)
{
    KERNAUX_ASSERT(spec);
    KERNAUX_ASSERT(format);
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

void KernAux_PrintfFmt_Spec_parse_length(struct KernAux_PrintfFmt_Spec *const spec, const char **const format)
{
    KERNAUX_ASSERT(spec);
    KERNAUX_ASSERT(format);
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
            spec->flags |= (sizeof(ptrdiff_t) == sizeof(long) ? KERNAUX_PRINTF_FMT_FLAGS_LONG : KERNAUX_PRINTF_FMT_FLAGS_LONG_LONG);
            ++(*format);
            break;
        case 'j':
            spec->flags |= (sizeof(intmax_t) == sizeof(long) ? KERNAUX_PRINTF_FMT_FLAGS_LONG : KERNAUX_PRINTF_FMT_FLAGS_LONG_LONG);
            ++(*format);
            break;
        case 'z':
            spec->flags |= (sizeof(size_t) == sizeof(long) ? KERNAUX_PRINTF_FMT_FLAGS_LONG : KERNAUX_PRINTF_FMT_FLAGS_LONG_LONG);
            ++(*format);
            break;
        default:
            break;
    }
}

void KernAux_PrintfFmt_Spec_parse_type(struct KernAux_PrintfFmt_Spec *const spec, const char **const format)
{
    KERNAUX_ASSERT(spec);
    KERNAUX_ASSERT(format);
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
                spec->flags &= ~KERNAUX_PRINTF_FMT_FLAGS_HASH; // no hash for dec format
            }
            // uppercase
            if (**format == 'X') {
                spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_UPPERCASE;
            }

            // no plus or space flag for u, x, X, o, b
            if ((**format != 'i') && (**format != 'd')) {
                spec->flags &= ~(KERNAUX_PRINTF_FMT_FLAGS_PLUS | KERNAUX_PRINTF_FMT_FLAGS_SPACE);
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
            if (**format == 'F') spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_UPPERCASE;
            spec->type = KERNAUX_PRINTF_FMT_TYPE_FLOAT;
            ++(*format);
            break;

        case 'e':
        case 'E':
        case 'g':
        case 'G':
            if ((**format == 'g')||(**format == 'G')) spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_ADAPT_EXP;
            if ((**format == 'E')||(**format == 'G')) spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_UPPERCASE;
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
            spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_ZEROPAD | KERNAUX_PRINTF_FMT_FLAGS_UPPERCASE;
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

void KernAux_PrintfFmt_Spec_set_width(struct KernAux_PrintfFmt_Spec *const spec, const int width)
{
    KERNAUX_ASSERT(spec);

    if (width < 0) {
        spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_LEFT; // reverse padding
        spec->width = (unsigned int)-width;
    } else {
        spec->width = (unsigned int)width;
    }
}

void KernAux_PrintfFmt_Spec_set_precision(struct KernAux_PrintfFmt_Spec *const spec, const int precision)
{
    KERNAUX_ASSERT(spec);

    spec->precision = precision > 0 ? (unsigned int)precision : 0u;
}

// internal ASCII string to unsigned int conversion
unsigned int _atoi(const char** str)
{
    const int result = atoi(*str);
    while (isdigit(**str)) (*str)++;
    return result;
}
