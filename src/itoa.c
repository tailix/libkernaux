#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/itoa.h>
#include <kernaux/libc.h>

void kernaux_itoa(const int d, char *buf, const int base)
{
    char *p = buf;
    char *p1, *p2;
    unsigned long ud = d;
    int divisor = 10;

    // If %d is specified and D is minus, put '-' in the head.
    if (base == 'd' && d < 0) {
        *p++ = '-';
        buf++;
        ud = -d;
    }
    else if (base == 'x') {
        divisor = 16;
    }

    // Divide UD by DIVISOR until UD == 0.
    do {
        int remainder = ud % divisor;
        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
    }
    while (ud /= divisor);

    // Terminate BUF.
    *p = '\0';

    // Reverse BUF.
    p1 = buf;
    p2 = p - 1;

    while (p1 < p2) {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }
}

void kernaux_utoa10(uint64_t value, char *buffer)
{
    char *pos = buffer;

    if (value == 0) *(pos++) = '0';

    while (value > 0) {
        *(pos++) = value % 10 + '0';
        value = value / 10;
    }

    *(pos--) = '\0';

    while (buffer < pos) {
        const char tmp = *buffer;
        *(buffer++) = *pos;
        *(pos--)    = tmp;
    }
}
