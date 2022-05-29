#include <kernaux/ntoa.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

static const char *str_end(const char *str)
{
    for (;; ++str) if (*str == '\0') return str;
}

int main()
{
    // kernaux_utoa - common func, unsigned, without prefix.
    {
        char buffer[KERNAUX_UTOA_BUFFER_SIZE];
        const char *end;

        // decimal: 10
        end = kernaux_utoa(123, buffer, 10);
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // decimal, character alias: 'd'
        end = kernaux_utoa(123, buffer, 'd');
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // decimal, uppercase: -10
        // (uppercase has no effect because this base has no letters)
        end = kernaux_utoa(123, buffer, -10);
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // decimal, uppercase, character alias: 'D'
        // (uppercase has no effect because this base has no letters)
        end = kernaux_utoa(123, buffer, 'D');
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // binary: 2
        end = kernaux_utoa(123, buffer, 2);
        assert(strcmp(buffer, "1111011") == 0);
        assert(end == str_end(buffer));

        // binary, character alias: 'b'
        end = kernaux_utoa(123, buffer, 'b');
        assert(strcmp(buffer, "1111011") == 0);
        assert(end == str_end(buffer));

        // binary, uppercase: -2
        // (uppercase has no effect because this base has no letters)
        end = kernaux_utoa(123, buffer, -2);
        assert(strcmp(buffer, "1111011") == 0);
        assert(end == str_end(buffer));

        // binary, uppercase, character alias: 'B'
        // (uppercase has no effect because this base has no letters)
        end = kernaux_utoa(123, buffer, 'B');
        assert(strcmp(buffer, "1111011") == 0);
        assert(end == str_end(buffer));

        // octal: 8
        end = kernaux_utoa(0123, buffer, 8);
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // octal, character alias: 'o'
        end = kernaux_utoa(0123, buffer, 'o');
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // octal, uppercase: -8
        // (uppercase has no effect because this base has no letters)
        end = kernaux_utoa(0123, buffer, -8);
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // octal, uppercase, character alias: 'O'
        // (uppercase has no effect because this base has no letters)
        end = kernaux_utoa(0123, buffer, 'O');
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // hex: 16
        end = kernaux_utoa(0x123cafe, buffer, 16);
        assert(strcmp(buffer, "123cafe") == 0);
        assert(end == str_end(buffer));

        // hex, character alias: 'x'
        end = kernaux_utoa(0x123cafe, buffer, 'x');
        assert(strcmp(buffer, "123cafe") == 0);
        assert(end == str_end(buffer));

        // hex, character alias: 'h'
        end = kernaux_utoa(0x123cafe, buffer, 'h');
        assert(strcmp(buffer, "123cafe") == 0);
        assert(end == str_end(buffer));

        // hex, uppercase: -16
        end = kernaux_utoa(0x123cafe, buffer, -16);
        assert(strcmp(buffer, "123CAFE") == 0);
        assert(end == str_end(buffer));

        // hex, uppercase, character alias: 'X'
        end = kernaux_utoa(0x123cafe, buffer, 'X');
        assert(strcmp(buffer, "123CAFE") == 0);
        assert(end == str_end(buffer));

        // hex, uppercase, character alias: 'H'
        end = kernaux_utoa(0x123cafe, buffer, 'H');
        assert(strcmp(buffer, "123CAFE") == 0);
        assert(end == str_end(buffer));

        // random base: 14
        end = kernaux_utoa(123456, buffer, 14);
        assert(strcmp(buffer, "32dc4") == 0);
        assert(end == str_end(buffer));

        // random base, uppercase: -14
        end = kernaux_utoa(123456, buffer, -14);
        assert(strcmp(buffer, "32DC4") == 0);
        assert(end == str_end(buffer));
    }

    return 0;
}
