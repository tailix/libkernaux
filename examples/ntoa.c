#include <kernaux/ntoa.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

static const char *str_end(const char *str)
{
    for (;; ++str) if (*str == '\0') return str;
}

void example_main()
{
    // kernaux_utoa
    {
        char buffer[KERNAUX_UTOA_MIN_BUFFER_SIZE + 3]; // more space for prefix
        const char *end;

        // decimal: 10
        // no prefix (NULL)
        end = kernaux_utoa(123, buffer, 10, NULL);
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // decimal: 10
        // with prefix ("foo")
        end = kernaux_utoa(123, buffer, 10, "foo");
        assert(strcmp(buffer, "foo123") == 0);
        assert(end == str_end(buffer));

        // decimal, character alias: 'd'
        // no prefix (NULL)
        end = kernaux_utoa(123, buffer, 'd', NULL);
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // binary: 2
        // no prefix (NULL)
        end = kernaux_utoa(123, buffer, 2, NULL);
        assert(strcmp(buffer, "1111011") == 0);
        assert(end == str_end(buffer));

        // binary: 2
        // with prefix ("0b")
        end = kernaux_utoa(123, buffer, 2, "0b");
        assert(strcmp(buffer, "0b1111011") == 0);
        assert(end == str_end(buffer));

        // binary, character alias: 'b'
        // no prefix (NULL)
        end = kernaux_utoa(123, buffer, 'b', NULL);
        assert(strcmp(buffer, "1111011") == 0);
        assert(end == str_end(buffer));

        // binary, character alias: 'b'
        // with prefix ("0b")
        end = kernaux_utoa(123, buffer, 'b', "0b");
        assert(strcmp(buffer, "0b1111011") == 0);
        assert(end == str_end(buffer));

        // octal: 8
        // no prefix (NULL)
        end = kernaux_utoa(0123, buffer, 8, NULL);
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // octal: 8
        // with prefix ("0o")
        end = kernaux_utoa(0123, buffer, 8, "0o");
        assert(strcmp(buffer, "0o123") == 0);
        assert(end == str_end(buffer));

        // octal, character alias: 'o'
        // no prefix (NULL)
        end = kernaux_utoa(0123, buffer, 'o', NULL);
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // octal, character alias: 'o'
        // with prefix ("0o")
        end = kernaux_utoa(0123, buffer, 'o', "0o");
        assert(strcmp(buffer, "0o123") == 0);
        assert(end == str_end(buffer));

        // hex: 16
        // no prefix (NULL)
        end = kernaux_utoa(0x123cafe, buffer, 16, NULL);
        assert(strcmp(buffer, "123cafe") == 0);
        assert(end == str_end(buffer));

        // hex: 16
        // with prefix ("0x")
        end = kernaux_utoa(0x123cafe, buffer, 16, "0x");
        assert(strcmp(buffer, "0x123cafe") == 0);
        assert(end == str_end(buffer));

        // hex, character alias: 'x'
        // no prefix (NULL)
        end = kernaux_utoa(0x123cafe, buffer, 'x', NULL);
        assert(strcmp(buffer, "123cafe") == 0);
        assert(end == str_end(buffer));

        // hex, character alias: 'x'
        // with prefix ("0x")
        end = kernaux_utoa(0x123cafe, buffer, 'x', "0x");
        assert(strcmp(buffer, "0x123cafe") == 0);
        assert(end == str_end(buffer));

        // hex, character alias: 'h'
        // no prefix (NULL)
        end = kernaux_utoa(0x123cafe, buffer, 'h', NULL);
        assert(strcmp(buffer, "123cafe") == 0);
        assert(end == str_end(buffer));

        // hex, uppercase: -16
        // no prefix (NULL)
        end = kernaux_utoa(0x123cafe, buffer, -16, NULL);
        assert(strcmp(buffer, "123CAFE") == 0);
        assert(end == str_end(buffer));

        // hex, uppercase, character alias: 'X'
        // no prefix (NULL)
        end = kernaux_utoa(0x123cafe, buffer, 'X', NULL);
        assert(strcmp(buffer, "123CAFE") == 0);
        assert(end == str_end(buffer));

        // hex, uppercase, character alias: 'H'
        // no prefix (NULL)
        end = kernaux_utoa(0x123cafe, buffer, 'H', NULL);
        assert(strcmp(buffer, "123CAFE") == 0);
        assert(end == str_end(buffer));

        // random base: 14
        // no prefix (NULL)
        end = kernaux_utoa(123456, buffer, 14, NULL);
        assert(strcmp(buffer, "32dc4") == 0);
        assert(end == str_end(buffer));

        // random base: 14
        // with prefix ("foo")
        end = kernaux_utoa(123456, buffer, 14, "foo");
        assert(strcmp(buffer, "foo32dc4") == 0);
        assert(end == str_end(buffer));

        // random base, uppercase: -14
        // no prefix (NULL)
        end = kernaux_utoa(123456, buffer, -14, NULL);
        assert(strcmp(buffer, "32DC4") == 0);
        assert(end == str_end(buffer));
    }

    // kernaux_itoa - similar to kernaux_utoa
    {
        char buffer[KERNAUX_ITOA_MIN_BUFFER_SIZE + 3]; // more space for prefix
        const char *end;

        // sign: +
        // decimal: 10
        // no prefix (NULL)
        end = kernaux_itoa(123, buffer, 10, NULL);
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // sign: -
        // decimal: 10
        // no prefix (NULL)
        end = kernaux_itoa(-123, buffer, 10, NULL);
        assert(strcmp(buffer, "-123") == 0);
        assert(end == str_end(buffer));

        // sign: +
        // decimal: 10
        // with prefix ("foo")
        end = kernaux_itoa(123, buffer, 10, "foo");
        assert(strcmp(buffer, "foo123") == 0);
        assert(end == str_end(buffer));

        // sign: -
        // decimal: 10
        // with prefix ("foo")
        end = kernaux_itoa(-123, buffer, 10, "foo");
        assert(strcmp(buffer, "-foo123") == 0);
        assert(end == str_end(buffer));
    }

    // kernaux_utoa2
    {
        char buffer[KERNAUX_UTOA2_BUFFER_SIZE];
        const char *end;

        end = kernaux_utoa2(123, buffer);
        assert(strcmp(buffer, "0b1111011") == 0);
        assert(end == str_end(buffer));
    }

    // kernaux_itoa2
    {
        char buffer[KERNAUX_ITOA2_BUFFER_SIZE];
        const char *end;

        end = kernaux_itoa2(123, buffer);
        assert(strcmp(buffer, "0b1111011") == 0);
        assert(end == str_end(buffer));

        end = kernaux_itoa2(-123, buffer);
        assert(strcmp(buffer, "-0b1111011") == 0);
        assert(end == str_end(buffer));
    }

    // kernaux_utoa8
    {
        char buffer[KERNAUX_UTOA8_BUFFER_SIZE];
        const char *end;

        end = kernaux_utoa8(0123, buffer);
        assert(strcmp(buffer, "0o123") == 0);
        assert(end == str_end(buffer));
    }

    // kernaux_itoa8
    {
        char buffer[KERNAUX_ITOA8_BUFFER_SIZE];
        const char *end;

        end = kernaux_itoa8(0123, buffer);
        assert(strcmp(buffer, "0o123") == 0);
        assert(end == str_end(buffer));

        end = kernaux_itoa8(-0123, buffer);
        assert(strcmp(buffer, "-0o123") == 0);
        assert(end == str_end(buffer));
    }

    // kernaux_utoa10
    {
        char buffer[KERNAUX_UTOA10_BUFFER_SIZE];
        const char *end;

        end = kernaux_utoa10(123, buffer);
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));
    }

    // kernaux_itoa10
    {
        char buffer[KERNAUX_ITOA10_BUFFER_SIZE];
        const char *end;

        end = kernaux_itoa10(123, buffer);
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        end = kernaux_itoa10(-123, buffer);
        assert(strcmp(buffer, "-123") == 0);
        assert(end == str_end(buffer));
    }

    // kernaux_utoa16
    {
        char buffer[KERNAUX_UTOA16_BUFFER_SIZE];
        const char *end;

        end = kernaux_utoa16(0x123, buffer);
        assert(strcmp(buffer, "0x123") == 0);
        assert(end == str_end(buffer));
    }

    // kernaux_itoa16
    {
        char buffer[KERNAUX_ITOA16_BUFFER_SIZE];
        const char *end;

        end = kernaux_itoa16(0x123, buffer);
        assert(strcmp(buffer, "0x123") == 0);
        assert(end == str_end(buffer));

        end = kernaux_itoa16(-0x123, buffer);
        assert(strcmp(buffer, "-0x123") == 0);
        assert(end == str_end(buffer));
    }
}
