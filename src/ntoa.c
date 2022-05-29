#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/ntoa.h>

#include <stddef.h>

char *kernaux_utoa(uint64_t value, char *buffer, int base, const char *prefix)
{
    KERNAUX_NOTNULL_RETVAL(buffer, NULL);

    switch (base) {
    case 'b': case 'B': base = 2;   break;
    case 'o': case 'O': base = 8;   break;
    case 'd': case 'D': base = 10;  break;
    case 'h': case 'x': base = 16;  break;
    case 'H': case 'X': base = -16; break;
    }

    // Uppercase
    char alpha = 'a';
    if (base < 0) {
        alpha = 'A';
        base = -base;
    }

    KERNAUX_ASSERT_RETVAL(base >= 2 && base <= 36, NULL);

    // Write prefix
    if (prefix) while (*prefix) *(buffer++) = *(prefix++);

    // Write number
    char *pos = buffer;
    if (value == 0) *(pos++) = '0';
    while (value > 0) {
        const char mod = value % base;
        *(pos++) = mod < 10 ? mod + '0' : mod - 10 + alpha;
        value /=  base;
    }
    char *const result = pos;
    *(pos--) = '\0';

    // Reverse buffer
    while (buffer < pos) {
        const char tmp = *buffer;
        *(buffer++) = *pos;
        *(pos--)    = tmp;
    }

    return result;
}

char *kernaux_itoa(int64_t value, char *buffer, int base, const char *prefix)
{
    if (value >= 0) {
        return kernaux_utoa(value, buffer, base, prefix);
    } else {
        *(buffer++) = '-';
        return kernaux_utoa(-value, buffer, base, prefix);
    }
}

char *kernaux_utoa2(uint64_t value, char *buffer)
{
    return kernaux_utoa(value, buffer, 'b', NULL);
}

char *kernaux_utoa2x(uint64_t value, char *buffer, const char *prefix)
{
    return kernaux_utoa(value, buffer, 'b', prefix);
}

char *kernaux_itoa2(int64_t value, char *buffer)
{
    return kernaux_itoa(value, buffer, 'b', NULL);
}

char *kernaux_itoa2x(int64_t value, char *buffer, const char *prefix)
{
    return kernaux_itoa(value, buffer, 'b', prefix);
}

char *kernaux_utoa8(uint64_t value, char *buffer)
{
    return kernaux_utoa(value, buffer, 'o', NULL);
}

char *kernaux_utoa8x(uint64_t value, char *buffer, const char *prefix)
{
    return kernaux_utoa(value, buffer, 'o', prefix);
}

char *kernaux_itoa8(int64_t value, char *buffer)
{
    return kernaux_itoa(value, buffer, 'o', NULL);
}

char *kernaux_itoa8x(int64_t value, char *buffer, const char *prefix)
{
    return kernaux_itoa(value, buffer, 'o', prefix);
}

char *kernaux_utoa10(uint64_t value, char *buffer)
{
    return kernaux_utoa(value, buffer, 'd', NULL);
}

char *kernaux_utoa10x(uint64_t value, char *buffer, const char *prefix)
{
    return kernaux_utoa(value, buffer, 'd', prefix);
}

char *kernaux_itoa10(int64_t value, char *buffer)
{
    return kernaux_itoa(value, buffer, 'd', NULL);
}

char *kernaux_itoa10x(int64_t value, char *buffer, const char *prefix)
{
    return kernaux_itoa(value, buffer, 'd', prefix);
}

char *kernaux_utoa16(uint64_t value, char *buffer)
{
    return kernaux_utoa(value, buffer, 'x', NULL);
}

char *kernaux_utoa16x(uint64_t value, char *buffer, const char *prefix)
{
    return kernaux_utoa(value, buffer, 'x', prefix);
}

char *kernaux_itoa16(int64_t value, char *buffer)
{
    return kernaux_itoa(value, buffer, 'x', NULL);
}

char *kernaux_itoa16x(int64_t value, char *buffer, const char *prefix)
{
    return kernaux_itoa(value, buffer, 'x', prefix);
}
