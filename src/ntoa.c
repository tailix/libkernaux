#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/ntoa.h>

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

void kernaux_itoa10(int64_t value, char *buffer)
{
    if (value >= 0) {
        kernaux_utoa10(value, buffer);
    } else {
        *(buffer++) = '-';
        kernaux_utoa10(-value, buffer);
    }
}
