#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/stdlib.h>

void kernaux_memset(
    void *const buffer,
    const unsigned char value,
    const unsigned long size
) {
    unsigned char *const s = buffer;

    for (unsigned long i = 0; i < size; ++i) {
        s[i] = value;
    }
}

unsigned int kernaux_strlen(const char *const s)
{
    unsigned int result = 0;

    while (s[result]) {
        ++result;
    }

    return result;
}

char *kernaux_strncpy(
    char *const dest,
    const char *const src,
    const unsigned long slen
) {
    for (unsigned long i = 0; i < slen; ++i) {
        dest[i] = src[i];
    }

    dest[slen] = '\0';

    return dest;
}

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
