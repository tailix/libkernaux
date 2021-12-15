#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/stdlib.h>

#include <assert.h>
#include <string.h>

int main()
{
    // kernaux_itoa

    {
        char buffer[10];

        kernaux_itoa(495, buffer, 'd');

        assert(buffer[0] == '4');
        assert(buffer[1] == '9');
        assert(buffer[2] == '5');
        assert(buffer[3] == '\0');
    }

    {
        char buffer[10];

        kernaux_itoa(-7012, buffer, 'd');

        assert(buffer[0] == '-');
        assert(buffer[1] == '7');
        assert(buffer[2] == '0');
        assert(buffer[3] == '1');
        assert(buffer[4] == '2');
        assert(buffer[5] == '\0');
    }

    return 0;
}
