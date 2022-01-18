#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/itoa.h>

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
