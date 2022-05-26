/**
 * Copyright (c) 2014-2019 Marco Paland <info@paland.com>
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/libc.h>
#include <kernaux/printf_fmt.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static unsigned int _atoi(const char** str);

struct KernAux_PrintfFmt_Spec KernAux_PrintfFmt_Spec_create()
{
    struct KernAux_PrintfFmt_Spec spec;
    KernAux_PrintfFmt_Spec_init(&spec);
    return spec;
}

void KernAux_PrintfFmt_Spec_init(struct KernAux_PrintfFmt_Spec *const spec)
{
    KERNAUX_NOTNULL_RETURN(spec);

    spec->flags = 0u;
    spec->width = 0u;
    spec->precision = 0u;
    spec->type = KERNAUX_PRINTF_FMT_TYPE_NONE;

    spec->base = 0;
}

void KernAux_PrintfFmt_Spec_eval_flags(struct KernAux_PrintfFmt_Spec *const spec, const char **const format)
{
    KERNAUX_NOTNULL_RETURN(spec);
    KERNAUX_NOTNULL_RETURN(format);
    KERNAUX_NOTNULL_RETURN(*format);

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

bool KernAux_PrintfFmt_Spec_eval_width1(struct KernAux_PrintfFmt_Spec *const spec, const char **const format)
{
    KERNAUX_NOTNULL_RETVAL(spec, false);
    KERNAUX_NOTNULL_RETVAL(format, false);
    KERNAUX_NOTNULL_RETVAL(*format, false);

    if (isdigit(**format)) {
        spec->width = _atoi(format);
        return false;
    } else {
        return **format == '*';
    }
}

void KernAux_PrintfFmt_Spec_eval_width2(struct KernAux_PrintfFmt_Spec *const spec, const char **const format, const int width)
{
    KERNAUX_NOTNULL_RETURN(spec);
    KERNAUX_NOTNULL_RETURN(format);
    KERNAUX_NOTNULL_RETURN(*format);

    if (width < 0) {
        spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_LEFT; // reverse padding
        spec->width = (unsigned int)-width;
    } else {
        spec->width = (unsigned int)width;
    }

    ++(*format);
}

bool KernAux_PrintfFmt_Spec_eval_precision1(struct KernAux_PrintfFmt_Spec *const spec, const char **const format)
{
    KERNAUX_NOTNULL_RETVAL(spec, false);
    KERNAUX_NOTNULL_RETVAL(format, false);
    KERNAUX_NOTNULL_RETVAL(*format, false);

    if (**format == '.') {
        spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_PRECISION;
        ++(*format);
        if (isdigit(**format)) {
            spec->precision = _atoi(format);
            return false;
        } else {
            return **format == '*';
        }
    } else {
        return false;
    }
}

void KernAux_PrintfFmt_Spec_eval_precision2(struct KernAux_PrintfFmt_Spec *const spec, const char **const format, const int precision)
{
    KERNAUX_NOTNULL_RETURN(spec);
    KERNAUX_NOTNULL_RETURN(format);
    KERNAUX_NOTNULL_RETURN(*format);

    spec->precision = precision > 0 ? (unsigned int)precision : 0u;
    ++(*format);
}

void KernAux_PrintfFmt_Spec_eval_length(struct KernAux_PrintfFmt_Spec *const spec, const char **const format)
{
    KERNAUX_NOTNULL_RETURN(spec);
    KERNAUX_NOTNULL_RETURN(format);
    KERNAUX_NOTNULL_RETURN(*format);

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
#ifdef ENABLE_BLOAT
        case 'S':
            if (*(++(*format)) == 'U') {
                spec->flags |= KERNAUX_PRINTF_FMT_FLAGS_CUSTOM;
                ++(*format);
            } else {
                --(*format);
            }
            break;
#endif // ENABLE_BLOAT
        default:
            break;
    }
}

void KernAux_PrintfFmt_Spec_eval_type(struct KernAux_PrintfFmt_Spec *const spec, const char **const format)
{
    KERNAUX_NOTNULL_RETURN(spec);
    KERNAUX_NOTNULL_RETURN(format);
    KERNAUX_NOTNULL_RETURN(*format);

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

#ifdef ENABLE_BLOAT
        case 'S':
            if (spec->flags & KERNAUX_PRINTF_FMT_FLAGS_CUSTOM) {
                spec->type = KERNAUX_PRINTF_FMT_TYPE_CUSTOM;
                ++(*format);
            }
            break;
#endif // ENABLE_BLOAT

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

// internal ASCII string to unsigned int conversion
unsigned int _atoi(const char** str)
{
    const int result = atoi(*str);
    while (isdigit(**str)) (*str)++;
    return result;
}
