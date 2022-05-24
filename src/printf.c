/**
 * Copyright (c) 2014-2019 Marco Paland <info@paland.com>
 *
 * Tiny printf, sprintf and (v)snprintf implementation, optimized for speed on
 * embedded systems with a very limited resources. These routines are thread
 * safe and reentrant!
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/libc.h>
#include <kernaux/printf.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// import float.h for DBL_MAX
#ifdef ENABLE_FLOAT
#include <float.h>
#endif

// 'ntoa' conversion buffer size, this must be big enough to hold one converted
// numeric number including padded zeros (dynamically created on stack)
#define PRINTF_NTOA_BUFFER_SIZE 32u

// 'ftoa' conversion buffer size, this must be big enough to hold one converted
// float number including padded zeros (dynamically created on stack)
#define PRINTF_FTOA_BUFFER_SIZE 32u

// define the default floating point precision
#define PRINTF_DEFAULT_FLOAT_PRECISION 6u

// define the largest float suitable to print with %f
#define PRINTF_MAX_FLOAT 1e9

// internal flag definitions
#define FLAGS_ZEROPAD   (1u <<  0u)
#define FLAGS_LEFT      (1u <<  1u)
#define FLAGS_PLUS      (1u <<  2u)
#define FLAGS_SPACE     (1u <<  3u)
#define FLAGS_HASH      (1u <<  4u)
#define FLAGS_UPPERCASE (1u <<  5u)
#define FLAGS_CHAR      (1u <<  6u)
#define FLAGS_SHORT     (1u <<  7u)
#define FLAGS_LONG      (1u <<  8u)
#define FLAGS_LONG_LONG (1u <<  9u)
#define FLAGS_PRECISION (1u << 10u)
#define FLAGS_ADAPT_EXP (1u << 11u)
#define FLAGS_CUSTOM    (1u << 12u)

// output function type
typedef void (*out_fct_type)(char character, void* buffer, size_t idx, size_t maxlen);

// wrapper (used as buffer) for output function type
typedef struct {
    void (*fct)(char character, void* arg);
    void* arg;
} out_fct_wrap_type;

static int _vsnprintf(out_fct_type out, char* buffer, const size_t maxlen, const char* format, va_list va);

static inline void _out_buffer(char character, void* buffer, size_t idx, size_t maxlen);
static inline void _out_null(char character, void* buffer, size_t idx, size_t maxlen);
static inline void _out_fct(char character, void* buffer, size_t idx, size_t maxlen);
static unsigned int _atoi(const char** str);
static size_t _out_rev(out_fct_type out, char* buffer, size_t idx, size_t maxlen, const char* buf, size_t len, unsigned int width, unsigned int flags);
static size_t _ntoa_format(out_fct_type out, char* buffer, size_t idx, size_t maxlen, char* buf, size_t len, bool negative, unsigned int base, unsigned int prec, unsigned int width, unsigned int flags);
static size_t _ntoa_long(out_fct_type out, char* buffer, size_t idx, size_t maxlen, unsigned long value, bool negative, unsigned long base, unsigned int prec, unsigned int width, unsigned int flags);
static size_t _ntoa_long_long(out_fct_type out, char* buffer, size_t idx, size_t maxlen, unsigned long long value, bool negative, unsigned long long base, unsigned int prec, unsigned int width, unsigned int flags);

#ifdef ENABLE_BLOAT
static char _custom(unsigned int flags, size_t *index);
#endif // ENABLE_BLOAT

#ifdef ENABLE_FLOAT
static size_t _ftoa(out_fct_type out, char* buffer, size_t idx, size_t maxlen, double value, unsigned int prec, unsigned int width, unsigned int flags);
static size_t _etoa(out_fct_type out, char* buffer, size_t idx, size_t maxlen, double value, unsigned int prec, unsigned int width, unsigned int flags);
#endif // ENABLE_FLOAT

/*******************************
 * Implementations: public API *
 *******************************/

int kernaux_printf(void (*out)(char character, void* arg), void* arg, const char* format, ...)
{
    KERNAUX_NOTNULL_RETVAL(out, 0);
    KERNAUX_NOTNULL_RETVAL(format, 0);

    va_list va;
    va_start(va, format);
    const out_fct_wrap_type out_fct_wrap = { out, arg };
    const int ret = _vsnprintf(_out_fct, (char*)(uintptr_t)&out_fct_wrap, (size_t)-1, format, va);
    va_end(va);
    return ret;
}

int kernaux_vprintf(void (*out)(char character, void* arg), void* arg, const char* format, va_list va)
{
    KERNAUX_NOTNULL_RETVAL(out, 0);
    KERNAUX_NOTNULL_RETVAL(format, 0);

    const out_fct_wrap_type out_fct_wrap = { out, arg };
    return _vsnprintf(_out_fct, (char*)(uintptr_t)&out_fct_wrap, (size_t)-1, format, va);
}

int kernaux_snprintf(char* buffer, size_t count, const char* format, ...)
{
    KERNAUX_NOTNULL_RETVAL(buffer, 0);
    KERNAUX_NOTNULL_RETVAL(format, 0);

    va_list va;
    va_start(va, format);
    const int ret = _vsnprintf(_out_buffer, buffer, count, format, va);
    va_end(va);
    return ret;
}

int kernaux_vsnprintf(char* buffer, size_t count, const char* format, va_list va)
{
    KERNAUX_NOTNULL_RETVAL(buffer, 0);
    KERNAUX_NOTNULL_RETVAL(format, 0);

    return _vsnprintf(_out_buffer, buffer, count, format, va);
}

int kernaux_sprintf(char* buffer, const char* format, ...)
{
    KERNAUX_NOTNULL_RETVAL(buffer, 0);
    KERNAUX_NOTNULL_RETVAL(format, 0);

    va_list va;
    va_start(va, format);
    const int ret = _vsnprintf(_out_buffer, buffer, (size_t)-1, format, va);
    va_end(va);
    return ret;
}

/******************************************
 * Implementation: main internal function *
 ******************************************/

int _vsnprintf(out_fct_type out, char* buffer, const size_t maxlen, const char* format, va_list va)
{
    KERNAUX_NOTNULL_RETVAL(format, 0);

    unsigned int flags, width, precision, n;
    size_t idx = 0u;

    if (!buffer) {
        // use null output function
        out = _out_null;
    }

    while (*format)
    {
        // format specifier? %[flags][width][.precision][length]
        if (*format != '%') {
            // no
            out(*format, buffer, idx++, maxlen);
            format++;
            continue;
        } else {
            // yes, evaluate it
            format++;
        }

        // evaluate flags
        flags = 0u;
        do {
            switch (*format) {
                case '0': flags |= FLAGS_ZEROPAD; format++; n = 1u; break;
                case '-': flags |= FLAGS_LEFT;    format++; n = 1u; break;
                case '+': flags |= FLAGS_PLUS;    format++; n = 1u; break;
                case ' ': flags |= FLAGS_SPACE;   format++; n = 1u; break;
                case '#': flags |= FLAGS_HASH;    format++; n = 1u; break;
                default:                                    n = 0u; break;
            }
        } while (n);

        // evaluate width field
        width = 0u;
        if (isdigit(*format)) {
            width = _atoi(&format);
        } else if (*format == '*') {
            const int w = va_arg(va, int);
            if (w < 0) {
                flags |= FLAGS_LEFT; // reverse padding
                width = (unsigned int)-w;
            } else {
                width = (unsigned int)w;
            }
            format++;
        }

        // evaluate precision field
        precision = 0u;
        if (*format == '.') {
            flags |= FLAGS_PRECISION;
            format++;
            if (isdigit(*format)) {
                precision = _atoi(&format);
            } else if (*format == '*') {
                const int prec = (int)va_arg(va, int);
                precision = prec > 0 ? (unsigned int)prec : 0u;
                format++;
            }
        }

        // evaluate length field
        switch (*format) {
            case 'l':
                flags |= FLAGS_LONG;
                format++;
                if (*format == 'l') {
                    flags |= FLAGS_LONG_LONG;
                    format++;
                }
                break;
            case 'h':
                flags |= FLAGS_SHORT;
                format++;
                if (*format == 'h') {
                    flags |= FLAGS_CHAR;
                    format++;
                }
                break;
            case 't':
                flags |= (sizeof(ptrdiff_t) == sizeof(long) ? FLAGS_LONG : FLAGS_LONG_LONG);
                format++;
                break;
            case 'j':
                flags |= (sizeof(intmax_t) == sizeof(long) ? FLAGS_LONG : FLAGS_LONG_LONG);
                format++;
                break;
            case 'z':
                flags |= (sizeof(size_t) == sizeof(long) ? FLAGS_LONG : FLAGS_LONG_LONG);
                format++;
                break;
#ifdef ENABLE_BLOAT
            case 'S':
                if (*(++format) == 'U') {
                    flags |= FLAGS_CUSTOM;
                    ++format;
                } else {
                    --format;
                }
                break;
#endif // ENABLE_BLOAT
            default:
                break;
        }

        // evaluate specifier
        switch (*format) {
            case 'd':
            case 'i':
            case 'u':
            case 'x':
            case 'X':
            case 'o':
            case 'b':
            {
                // set the base
                unsigned int base;
                if (*format == 'x' || *format == 'X') {
                    base = 16u;
                } else if (*format == 'o') {
                    base = 8u;
                } else if (*format == 'b') {
                    base = 2u;
                } else {
                    base = 10u;
                    flags &= ~FLAGS_HASH; // no hash for dec format
                }
                // uppercase
                if (*format == 'X') {
                    flags |= FLAGS_UPPERCASE;
                }

                // no plus or space flag for u, x, X, o, b
                if ((*format != 'i') && (*format != 'd')) {
                    flags &= ~(FLAGS_PLUS | FLAGS_SPACE);
                }

                // ignore '0' flag when precision is given
                if (flags & FLAGS_PRECISION) {
                    flags &= ~FLAGS_ZEROPAD;
                }

                // convert the integer
                if ((*format == 'i') || (*format == 'd')) {
                    // signed
                    if (flags & FLAGS_LONG_LONG) {
                        const long long value = va_arg(va, long long);
                        idx = _ntoa_long_long(out, buffer, idx, maxlen, (unsigned long long)(value > 0 ? value : 0 - value), value < 0, base, precision, width, flags);
                    } else if (flags & FLAGS_LONG) {
                        const long value = va_arg(va, long);
                        idx = _ntoa_long(out, buffer, idx, maxlen, (unsigned long)(value > 0 ? value : 0 - value), value < 0, base, precision, width, flags);
                    } else {
                        const int value = (flags & FLAGS_CHAR) ? (char)va_arg(va, int) : (flags & FLAGS_SHORT) ? (short int)va_arg(va, int) : va_arg(va, int);
                        idx = _ntoa_long(out, buffer, idx, maxlen, (unsigned int)(value > 0 ? value : 0 - value), value < 0, base, precision, width, flags);
                    }
                } else {
                    // unsigned
                    if (flags & FLAGS_LONG_LONG) {
                        idx = _ntoa_long_long(out, buffer, idx, maxlen, va_arg(va, unsigned long long), false, base, precision, width, flags);
                    } else if (flags & FLAGS_LONG) {
                        idx = _ntoa_long(out, buffer, idx, maxlen, va_arg(va, unsigned long), false, base, precision, width, flags);
                    } else {
                        const unsigned int value = (flags & FLAGS_CHAR) ? (unsigned char)va_arg(va, unsigned int) : (flags & FLAGS_SHORT) ? (unsigned short int)va_arg(va, unsigned int) : va_arg(va, unsigned int);
                        idx = _ntoa_long(out, buffer, idx, maxlen, value, false, base, precision, width, flags);
                    }
                }
                format++;
                break;
            }
#ifdef ENABLE_FLOAT
            case 'f':
            case 'F':
                if (*format == 'F') flags |= FLAGS_UPPERCASE;
                idx = _ftoa(out, buffer, idx, maxlen, va_arg(va, double), precision, width, flags);
                format++;
                break;
            case 'e':
            case 'E':
            case 'g':
            case 'G':
                if ((*format == 'g')||(*format == 'G')) flags |= FLAGS_ADAPT_EXP;
                if ((*format == 'E')||(*format == 'G')) flags |= FLAGS_UPPERCASE;
                idx = _etoa(out, buffer, idx, maxlen, va_arg(va, double), precision, width, flags);
                format++;
                break;
#endif // ENABLE_FLOAT
            case 'c':
            {
                unsigned int l = 1u;
                // pre padding
                if (!(flags & FLAGS_LEFT)) {
                    while (l++ < width) {
                        out(' ', buffer, idx++, maxlen);
                    }
                }
                // char output
                out((char)va_arg(va, int), buffer, idx++, maxlen);
                // post padding
                if (flags & FLAGS_LEFT) {
                    while (l++ < width) {
                        out(' ', buffer, idx++, maxlen);
                    }
                }
                format++;
                break;
            }

            case 's':
            {
                const char* p = va_arg(va, char*);
                unsigned int l = strnlen(p, precision ? precision : (size_t)-1);
                // pre padding
                if (flags & FLAGS_PRECISION) {
                    l = (l < precision ? l : precision);
                }
                if (!(flags & FLAGS_LEFT)) {
                    while (l++ < width) {
                        out(' ', buffer, idx++, maxlen);
                    }
                }
                // string output
                while ((*p != 0) && (!(flags & FLAGS_PRECISION) || precision--)) {
                    out(*(p++), buffer, idx++, maxlen);
                }
                // post padding
                if (flags & FLAGS_LEFT) {
                    while (l++ < width) {
                        out(' ', buffer, idx++, maxlen);
                    }
                }
                format++;
                break;
            }

#ifdef ENABLE_BLOAT
            case 'S':
                if (flags & FLAGS_CUSTOM) {
                    format++;
                    size_t index = 0;
                    char c;
                    while ((c = _custom(flags, &index))) {
                        out(c, buffer, idx++, maxlen);
                    }
                }
                break;
#endif // ENABLE_BLOAT

            case 'p':
            {
                width = sizeof(void*) * 2u;
                flags |= FLAGS_ZEROPAD | FLAGS_UPPERCASE;
                const bool is_ll = sizeof(uintptr_t) == sizeof(long long);
                if (is_ll) {
                    idx = _ntoa_long_long(out, buffer, idx, maxlen, (uintptr_t)va_arg(va, void*), false, 16u, precision, width, flags);
                } else {
                    idx = _ntoa_long(out, buffer, idx, maxlen, (unsigned long)((uintptr_t)va_arg(va, void*)), false, 16u, precision, width, flags);
                }
                format++;
                break;
            }

            case '%':
                out('%', buffer, idx++, maxlen);
                format++;
                break;

            default:
                out(*format, buffer, idx++, maxlen);
                format++;
                break;
        }
    }

    // termination
    out((char)0, buffer, idx < maxlen ? idx : maxlen - 1u, maxlen);

    // return written chars without terminating \0
    return (int)idx;
}

/*************************************
 * Implementations: helper functions *
 *************************************/

// internal buffer output
void _out_buffer(char character, void* buffer, size_t idx, size_t maxlen)
{
    if (idx < maxlen) {
        ((char*)buffer)[idx] = character;
    }
}

// internal null output
void _out_null(char character, void* buffer, size_t idx, size_t maxlen)
{
    (void)character; (void)buffer; (void)idx; (void)maxlen;
}

// internal output function wrapper
void _out_fct(char character, void* buffer, size_t idx, size_t maxlen)
{
    (void)idx; (void)maxlen;
    if (character) {
        // buffer is the output fct pointer
        ((out_fct_wrap_type*)buffer)->fct(character, ((out_fct_wrap_type*)buffer)->arg);
    }
}

// internal ASCII string to unsigned int conversion
unsigned int _atoi(const char** str)
{
    const int result = atoi(*str);
    while (isdigit(**str)) (*str)++;
    return result;
}

// output the specified string in reverse, taking care of any zero-padding
size_t _out_rev(out_fct_type out, char* buffer, size_t idx, size_t maxlen, const char* buf, size_t len, unsigned int width, unsigned int flags)
{
    const size_t start_idx = idx;

    // pad spaces up to given width
    if (!(flags & FLAGS_LEFT) && !(flags & FLAGS_ZEROPAD)) {
        for (size_t i = len; i < width; i++) {
            out(' ', buffer, idx++, maxlen);
        }
    }

    // reverse string
    while (len) {
        out(buf[--len], buffer, idx++, maxlen);
    }

    // append pad spaces up to given width
    if (flags & FLAGS_LEFT) {
        while (idx - start_idx < width) {
            out(' ', buffer, idx++, maxlen);
        }
    }

    return idx;
}

// internal itoa format
size_t _ntoa_format(out_fct_type out, char* buffer, size_t idx, size_t maxlen, char* buf, size_t len, bool negative, unsigned int base, unsigned int prec, unsigned int width, unsigned int flags)
{
    // pad leading zeros
    if (!(flags & FLAGS_LEFT)) {
        if (width && (flags & FLAGS_ZEROPAD) && (negative || (flags & (FLAGS_PLUS | FLAGS_SPACE)))) {
            width--;
        }
        while ((len < prec) && (len < PRINTF_NTOA_BUFFER_SIZE)) {
            buf[len++] = '0';
        }
        while ((flags & FLAGS_ZEROPAD) && (len < width) && (len < PRINTF_NTOA_BUFFER_SIZE)) {
            buf[len++] = '0';
        }
    }

    // handle hash
    if (flags & FLAGS_HASH) {
        if (!(flags & FLAGS_PRECISION) && len && ((len == prec) || (len == width))) {
            len--;
            if (len && (base == 16u)) {
                len--;
            }
        }
        if ((base == 16u) && !(flags & FLAGS_UPPERCASE) && (len < PRINTF_NTOA_BUFFER_SIZE)) {
            buf[len++] = 'x';
        } else if ((base == 16u) && (flags & FLAGS_UPPERCASE) && (len < PRINTF_NTOA_BUFFER_SIZE)) {
            buf[len++] = 'X';
        } else if ((base == 2u) && (len < PRINTF_NTOA_BUFFER_SIZE)) {
            buf[len++] = 'b';
        }
        if (len < PRINTF_NTOA_BUFFER_SIZE) {
            buf[len++] = '0';
        }
    }

    if (len < PRINTF_NTOA_BUFFER_SIZE) {
        if (negative) {
            buf[len++] = '-';
        } else if (flags & FLAGS_PLUS) {
            buf[len++] = '+'; // ignore the space if the '+' exists
        } else if (flags & FLAGS_SPACE) {
            buf[len++] = ' ';
        }
    }

    return _out_rev(out, buffer, idx, maxlen, buf, len, width, flags);
}

// internal itoa for 'long' type
size_t _ntoa_long(out_fct_type out, char* buffer, size_t idx, size_t maxlen, unsigned long value, bool negative, unsigned long base, unsigned int prec, unsigned int width, unsigned int flags)
{
    char buf[PRINTF_NTOA_BUFFER_SIZE];
    size_t len = 0u;

    // no hash for 0 values
    if (!value) {
        flags &= ~FLAGS_HASH;
    }

    // write if precision != 0 and value is != 0
    if (!(flags & FLAGS_PRECISION) || value) {
        do {
            const char digit = (char)(value % base);
            buf[len++] = digit < 10 ? '0' + digit : (flags & FLAGS_UPPERCASE ? 'A' : 'a') + digit - 10;
            value /= base;
        } while (value && (len < PRINTF_NTOA_BUFFER_SIZE));
    }

    return _ntoa_format(out, buffer, idx, maxlen, buf, len, negative, (unsigned int)base, prec, width, flags);
}

// internal itoa for 'long long' type
size_t _ntoa_long_long(out_fct_type out, char* buffer, size_t idx, size_t maxlen, unsigned long long value, bool negative, unsigned long long base, unsigned int prec, unsigned int width, unsigned int flags)
{
    char buf[PRINTF_NTOA_BUFFER_SIZE];
    size_t len = 0u;

    // no hash for 0 values
    if (!value) {
        flags &= ~FLAGS_HASH;
    }

    // write if precision != 0 and value is != 0
    if (!(flags & FLAGS_PRECISION) || value) {
        do {
            const char digit = (char)(value % base);
            buf[len++] = digit < 10 ? '0' + digit : (flags & FLAGS_UPPERCASE ? 'A' : 'a') + digit - 10;
            value /= base;
        } while (value && (len < PRINTF_NTOA_BUFFER_SIZE));
    }

    return _ntoa_format(out, buffer, idx, maxlen, buf, len, negative, (unsigned int)base, prec, width, flags);
}

#ifdef ENABLE_BLOAT
/**
 * Idea: superleaf1995
 * Implementation: smwmaster
 */
static const size_t map_size = 630;
static const char *const map =
    "\xD3\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9"
    "\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xD3\xF9\xF9"
    "\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF7\xFE\xF7\xF7\xF9\xF7"
    "\xFE\xF5\xF5\xF9\xF7\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xD3\xF9\xF9\xF9\xF9\xF9"
    "\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF7\xE2\xA1\x96\x96\x96\x96\x96\xB2\xBD"
    "\xB6\xE3\xF5\xFE\xF9\xF9\xF9\xF9\xF9\xD3\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9"
    "\xF9\xF9\xF9\xF9\xF7\xE2\x81\x81\x92\xE9\x96\x96\xE9\xE9\x92\x97\x97\x96"
    "\xFE\xFE\xF7\xF9\xF9\xF9\xD3\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9"
    "\xF7\xF7\xE9\xB5\xF7\xE2\xB5\xB6\xA1\xA1\xA1\xB5\xE2\xE3\x81\x92\xF5\xF7"
    "\xF9\xF9\xF9\xD3\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF7\xB2\x97"
    "\xB2\xF7\xF7\xE2\xBA\xBA\xE3\xE2\xF5\xFE\xE2\x81\x97\xE9\xF7\xF7\xF9\xF9"
    "\xD3\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xBA\x81\x97\x97\x97\x96"
    "\xA1\xBD\xBD\xA1\xB2\xE9\x97\x97\x97\x97\x97\xB5\xF7\xF9\xF9\xD3\xF9\xF9"
    "\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF7\x92\x97\x97\x97\x97\x97\x97\x97\x97"
    "\x97\x97\x97\x97\x97\x97\x97\x97\xA1\xF7\xF9\xF9\xD3\xF9\xF9\xF9\xF9\xF9"
    "\xF9\xF9\xF9\xF9\xF9\xBA\x97\x97\x97\x97\x97\x97\x97\x97\x97\x97\x97\x97"
    "\x97\x97\x97\x97\x97\xE9\xF7\xF9\xF9\xD3\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9"
    "\xF9\xF9\x96\x97\x97\x97\x97\x97\x97\x97\x97\x97\x97\x97\x97\x97\x97\x97"
    "\x97\x97\x92\xF7\xF9\xF9\xD3\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xFE\x81"
    "\x97\x97\x97\x97\x97\x97\x97\x97\x97\x97\x97\x97\x97\x97\x97\x97\x97\x81"
    "\xFE\xF9\xF9\xD3\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xB5\x97\x97\x97\x97"
    "\x97\x97\x97\x97\x97\x97\x97\x97\x97\x97\x97\x97\x97\x97\x97\xF5\xF9\xF9"
    "\xD3\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF7\x96\x97\x97\x97\xA1\xF5\xF9\xF9"
    "\xF9\xF9\xF9\xF9\xFE\x96\x97\x97\x97\x97\x97\x97\xE3\xF9\xF9\xD3\xF9\xF9"
    "\xF9\xF9\xF9\xF9\xF9\xF7\xF5\x81\x97\x97\x92\xF7\xF9\xF9\xF9\xF9\xF9\xF9"
    "\xF9\xF9\xFE\x81\x97\x97\x97\x97\x97\xBA\xF9\xF9\xD3\xF9\xF9\xF7\xE2\xBA"
    "\xBA\xBA\xF5\xB2\x97\x97\x97\x97\xE3\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF5"
    "\x81\x97\x97\x97\x97\x97\xE3\xF9\xF9\xD3\xF9\xF9\xFE\xE9\x81\x97\x97\x97"
    "\x97\x97\x81\x92\xB2\xF7\xF9\xF9\xF9\xF9\xF9\xF7\xF7\xF7\xB6\x97\x97\x97"
    "\x97\x97\x97\xE2\xF9\xF9\xD3\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9"
    "\xF9\xF9\xF9\xF9\xF9\xF7\xFE\xB2\x92\x81\x81\x97\x97\x97\x97\x97\x97\xE9"
    "\xF7\xF9\xF9\xD3\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9"
    "\xF9\xF9\xF9\xF9\xF5\xB2\x96\xE9\xE9\x96\xA1\xBD\xF5\xF9\xF9\xF9\xF9\xF9"
    "\xD3\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9"
    "\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xF9\xD3\xD3\xD9";

char _custom(const unsigned int flags, size_t *const index)
{
    if (*index >= map_size) return '\0';
    return map[(*index)++] ^ (73 + ((flags >> 8) | 128));
}
#endif // ENABLE_BLOAT

#ifdef ENABLE_FLOAT
// internal ftoa for fixed decimal floating point
size_t _ftoa(out_fct_type out, char* buffer, size_t idx, size_t maxlen, double value, unsigned int prec, unsigned int width, unsigned int flags)
{
    char buf[PRINTF_FTOA_BUFFER_SIZE];
    size_t len = 0u;
    double diff = 0.0;

    // powers of 10
    static const double pow10[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };

    // test for special values
    if (value != value)
        return _out_rev(out, buffer, idx, maxlen, "nan", 3, width, flags);
    if (value < -DBL_MAX)
        return _out_rev(out, buffer, idx, maxlen, "fni-", 4, width, flags);
    if (value > DBL_MAX)
        return _out_rev(out, buffer, idx, maxlen, (flags & FLAGS_PLUS) ? "fni+" : "fni", (flags & FLAGS_PLUS) ? 4u : 3u, width, flags);

    // test for very large values
    // standard printf behavior is to print EVERY whole number digit -- which could be 100s of characters overflowing your buffers == bad
    if ((value > PRINTF_MAX_FLOAT) || (value < -PRINTF_MAX_FLOAT)) {
        return _etoa(out, buffer, idx, maxlen, value, prec, width, flags);
    }

    // test for negative
    bool negative = false;
    if (value < 0) {
        negative = true;
        value = 0 - value;
    }

    // set default precision, if not set explicitly
    if (!(flags & FLAGS_PRECISION)) {
        prec = PRINTF_DEFAULT_FLOAT_PRECISION;
    }
    // limit precision to 9, cause a prec >= 10 can lead to overflow errors
    while ((len < PRINTF_FTOA_BUFFER_SIZE) && (prec > 9u)) {
        buf[len++] = '0';
        prec--;
    }

    int whole = (int)value;
    double tmp = (value - whole) * pow10[prec];
    unsigned long frac = (unsigned long)tmp;
    diff = tmp - frac;

    if (diff > 0.5) {
        ++frac;
        // handle rollover, e.g. case 0.99 with prec 1 is 1.0
        if (frac >= pow10[prec]) {
            frac = 0;
            ++whole;
        }
    } else if (diff < 0.5) {
        // TODO: do nothing?
    } else if ((frac == 0u) || (frac & 1u)) {
        // if halfway, round up if odd OR if last digit is 0
        ++frac;
    }

    if (prec == 0u) {
        diff = value - (double)whole;
        if ((!(diff < 0.5) || (diff > 0.5)) && (whole & 1)) {
            // exactly 0.5 and ODD, then round up
            // 1.5 -> 2, but 2.5 -> 2
            ++whole;
        }
    } else {
        unsigned int count = prec;
        // now do fractional part, as an unsigned number
        while (len < PRINTF_FTOA_BUFFER_SIZE) {
            --count;
            buf[len++] = (char)(48u + (frac % 10u));
            if (!(frac /= 10u)) {
                break;
            }
        }
        // add extra 0s
        while ((len < PRINTF_FTOA_BUFFER_SIZE) && (count-- > 0u)) {
            buf[len++] = '0';
        }
        if (len < PRINTF_FTOA_BUFFER_SIZE) {
            // add decimal
            buf[len++] = '.';
        }
    }

    // do whole part, number is reversed
    while (len < PRINTF_FTOA_BUFFER_SIZE) {
        buf[len++] = (char)(48 + (whole % 10));
        if (!(whole /= 10)) {
            break;
        }
    }

    // pad leading zeros
    if (!(flags & FLAGS_LEFT) && (flags & FLAGS_ZEROPAD)) {
        if (width && (negative || (flags & (FLAGS_PLUS | FLAGS_SPACE)))) {
            width--;
        }
        while ((len < width) && (len < PRINTF_FTOA_BUFFER_SIZE)) {
            buf[len++] = '0';
        }
    }

    if (len < PRINTF_FTOA_BUFFER_SIZE) {
        if (negative) {
            buf[len++] = '-';
        } else if (flags & FLAGS_PLUS) {
            buf[len++] = '+'; // ignore the space if the '+' exists
        } else if (flags & FLAGS_SPACE) {
            buf[len++] = ' ';
        }
    }

    return _out_rev(out, buffer, idx, maxlen, buf, len, width, flags);
}

// internal ftoa variant for exponential floating-point type, contributed by Martijn Jasperse <m.jasperse@gmail.com>
size_t _etoa(out_fct_type out, char* buffer, size_t idx, size_t maxlen, double value, unsigned int prec, unsigned int width, unsigned int flags)
{
    // check for NaN and special values
    if ((value != value) || (value > DBL_MAX) || (value < -DBL_MAX)) {
        return _ftoa(out, buffer, idx, maxlen, value, prec, width, flags);
    }

    // determine the sign
    const bool negative = value < 0;
    if (negative) {
        value = -value;
    }

    // default precision
    if (!(flags & FLAGS_PRECISION)) {
        prec = PRINTF_DEFAULT_FLOAT_PRECISION;
    }

    // determine the decimal exponent
    // based on the algorithm by David Gay (https://www.ampl.com/netlib/fp/dtoa.c)
    union {
        uint64_t U;
        double  F;
    } conv;

    conv.F = value;
    int exp2 = (int)((conv.U >> 52u) & 0x07ffu) - 1023; // effectively log2
    conv.U = (conv.U & ((1ull << 52u) - 1u)) | (102ull << 52u); // drop the exponent so conv.F is now in [1,2)
    // now approximate log10 from the log2 integer part and an expansion of ln around 1.5
    int expval = (int)(0.1760912590558 + exp2 * 0.301029995663981 + (conv.F - 1.5) * 0.289529654602168);
    // now we want to compute 10^expval but we want to be sure it won't overflow
    exp2 = (int)(expval * 3.321928094887362 + 0.5);
    const double z = expval * 2.302585092994046 - exp2 * 0.6931471805599453;
    const double z2 = z * z;
    conv.U = (uint64_t)(exp2 + 1023) << 52u;
    // compute exp(z) using continued fractions, see https://en.wikipedia.org/wiki/Exponential_function#Continued_fractions_for_ex
    conv.F *= 1 + 2 * z / (2 - z + (z2 / (6 + (z2 / (10 + z2 / 14)))));
    // correct for rounding errors
    if (value < conv.F) {
        expval--;
        conv.F /= 10;
    }

    // the exponent format is "%+03d" and largest value is "307", so set aside 4-5 characters
    unsigned int minwidth = ((expval < 100) && (expval > -100)) ? 4u : 5u;

    // in "%g" mode, "prec" is the number of *significant figures* not decimals
    if (flags & FLAGS_ADAPT_EXP) {
        // do we want to fall-back to "%f" mode?
        if ((value >= 1e-4) && (value < 1e6)) {
            if ((int)prec > expval) {
                prec = (unsigned)((int)prec - expval - 1);
            } else {
                prec = 0;
            }
            flags |= FLAGS_PRECISION; // make sure _ftoa respects precision
            // no characters in exponent
            minwidth = 0u;
            expval = 0;
        } else {
            // we use one sigfig for the whole part
            if ((prec > 0) && (flags & FLAGS_PRECISION)) {
                --prec;
            }
        }
    }

    // will everything fit?
    unsigned int fwidth = width;
    if (width > minwidth) {
        // we didn't fall-back so subtract the characters required for the exponent
        fwidth -= minwidth;
    } else {
        // not enough characters, so go back to default sizing
        fwidth = 0u;
    }
    if ((flags & FLAGS_LEFT) && minwidth) {
        // if we're padding on the right, DON'T pad the floating part
        fwidth = 0u;
    }

    // rescale the float value
    if (expval) {
        value /= conv.F;
    }

    // output the floating part
    const size_t start_idx = idx;
    idx = _ftoa(out, buffer, idx, maxlen, negative ? -value : value, prec, fwidth, flags & ~FLAGS_ADAPT_EXP);

    // output the exponent part
    if (minwidth) {
        // output the exponential symbol
        out((flags & FLAGS_UPPERCASE) ? 'E' : 'e', buffer, idx++, maxlen);
        // output the exponent value
        idx = _ntoa_long(out, buffer, idx, maxlen, (expval < 0) ? -expval : expval, expval < 0, 10, 0, minwidth-1, FLAGS_ZEROPAD | FLAGS_PLUS);
        // might need to right-pad spaces
        if (flags & FLAGS_LEFT) {
            while (idx - start_idx < width) out(' ', buffer, idx++, maxlen);
        }
    }
    return idx;
}
#endif // ENABLE_FLOAT
