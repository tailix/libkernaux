#include <kernaux/stdlib.h>

#include <assert.h>

int main()
{
    // kernaux_memset

    {
        unsigned char buffer[10] =
            {32, 13, 254, 165, 98, 36, 169, 152, 233, 222};

        kernaux_memset(buffer, 0, sizeof(buffer));

        for (unsigned int i = 0; i < sizeof(buffer); ++i) {
            assert(buffer[i] == 0);
        }
    }

    {
        unsigned char buffer[10] =
            {32, 13, 254, 165, 98, 36, 169, 152, 233, 222};

        kernaux_memset(buffer, 143, sizeof(buffer));

        for (unsigned int i = 0; i < sizeof(buffer); ++i) {
            assert(buffer[i] == 143);
        }
    }

    // kernaux_strlen

    assert(kernaux_strlen("") == 0);
    assert(kernaux_strlen("\0abcde") == 0);
    assert(kernaux_strlen("12345") == 5);
    assert(kernaux_strlen("12345\0abcde") == 5);

    // kernaux_strncpy

    {
        const char src[] = "Hello, World!";
        char dest[sizeof(src)];
        kernaux_memset(dest, 0, sizeof(dest));

        kernaux_strncpy(dest, src, kernaux_strlen(src));

        assert(kernaux_strlen(dest) == kernaux_strlen(src));

        for (
            const char *src_p = src, *dest_p = dest;
            *src_p;
            ++src_p, ++dest_p
        ) {
            assert(*src_p == *dest_p);
        }
    }

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
