#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/ntoa.h>

#include <stddef.h>

// TODO: example common func, maybe it may become public
static char *kernaux_utoa(uint64_t value, char *buffer, int base)
{
    switch (base) {
    case 'b': base = 2;  break;
    case 'o': base = 8;  break;
    case 'd': base = 10; break;
    case 'h':
    case 'x':
        base = 16;
        break;
    case 'H':
    case 'X':
        base = -16;
        break;
    }

    char alpha = 'a';
    if (base < 0) {
        alpha = 'A';
        base = -base;
    }

    if (base < 2 || base > 36) return NULL;

    char *pos = buffer;

    if (value == 0) *(pos++) = '0';

    while (value > 0) {
        const char mod = value % base;
        *(pos++) = mod < 10 ? mod + '0' : mod - 10 + alpha;
        value = value / base;
    }

    char *const result = pos;
    *(pos--) = '\0';

    while (buffer < pos) {
        const char tmp = *buffer;
        *(buffer++) = *pos;
        *(pos--)    = tmp;
    }

    return result;
}

// TODO: example common func, maybe it may become public
static char *kernaux_itoa(int64_t value, char *buffer, int base)
{
    if (value >= 0) {
        return kernaux_utoa(value, buffer, base);
    } else {
        *(buffer++) = '-';
        return kernaux_utoa(-value, buffer, base);
    }
}

void kernaux_utoa10(uint64_t value, char *buffer)
{
    kernaux_utoa(value, buffer, 'd');
}

void kernaux_itoa10(int64_t value, char *buffer)
{
    kernaux_itoa(value, buffer, 'd');
}

void kernaux_utoa16(uint64_t value, char *buffer)
{
    kernaux_utoa(value, buffer, 'x');
}

void kernaux_itoa16(int64_t value, char *buffer)
{
    kernaux_itoa(value, buffer, 'x');
}
