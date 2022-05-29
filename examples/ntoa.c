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
    // kernaux_utoa - common func, unsigned, with prefix.
    {
        char buffer[KERNAUX_UTOA_BUFFER_SIZE + 3]; // more space for prefix
        const char *end;

        // decimal: 10
        // no prefix (NULL)
        end = kernaux_utoa(123, buffer, 10, NULL);
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // decimal: 10
        // no prefix ("")
        end = kernaux_utoa(123, buffer, 10, "");
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

        // decimal, character alias: 'd'
        // no prefix ("")
        end = kernaux_utoa(123, buffer, 'd', "");
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // decimal, character alias: 'd'
        // with prefix ("foo")
        end = kernaux_utoa(123, buffer, 'd', "foo");
        assert(strcmp(buffer, "foo123") == 0);
        assert(end == str_end(buffer));

        // decimal, uppercase: -10
        // (uppercase has no effect because this base has no letters)
        // no prefix (NULL)
        end = kernaux_utoa(123, buffer, -10, NULL);
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // decimal, uppercase: -10
        // (uppercase has no effect because this base has no letters)
        // no prefix ("")
        end = kernaux_utoa(123, buffer, -10, "");
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // decimal, uppercase: -10
        // (uppercase has no effect because this base has no letters)
        // with prefix ("foo")
        end = kernaux_utoa(123, buffer, -10, "foo");
        assert(strcmp(buffer, "foo123") == 0);
        assert(end == str_end(buffer));

        // decimal, uppercase, character alias: 'D'
        // (uppercase has no effect because this base has no letters)
        // no prefix (NULL)
        end = kernaux_utoa(123, buffer, 'D', NULL);
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // decimal, uppercase, character alias: 'D'
        // (uppercase has no effect because this base has no letters)
        // no prefix ("")
        end = kernaux_utoa(123, buffer, 'D', "");
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // decimal, uppercase, character alias: 'D'
        // (uppercase has no effect because this base has no letters)
        // with prefix ("foo")
        end = kernaux_utoa(123, buffer, 'D', "foo");
        assert(strcmp(buffer, "foo123") == 0);
        assert(end == str_end(buffer));

        // binary: 2
        // no prefix (NULL)
        end = kernaux_utoa(123, buffer, 2, NULL);
        assert(strcmp(buffer, "1111011") == 0);
        assert(end == str_end(buffer));

        // binary: 2
        // no prefix ("")
        end = kernaux_utoa(123, buffer, 2, "");
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
        // no prefix ("")
        end = kernaux_utoa(123, buffer, 'b', "");
        assert(strcmp(buffer, "1111011") == 0);
        assert(end == str_end(buffer));

        // binary, character alias: 'b'
        // with prefix ("0b")
        end = kernaux_utoa(123, buffer, 'b', "0b");
        assert(strcmp(buffer, "0b1111011") == 0);
        assert(end == str_end(buffer));

        // binary, uppercase: -2
        // (uppercase has no effect because this base has no letters)
        // no prefix (NULL)
        end = kernaux_utoa(123, buffer, -2, NULL);
        assert(strcmp(buffer, "1111011") == 0);
        assert(end == str_end(buffer));

        // binary, uppercase: -2
        // (uppercase has no effect because this base has no letters)
        // no prefix ("")
        end = kernaux_utoa(123, buffer, -2, "");
        assert(strcmp(buffer, "1111011") == 0);
        assert(end == str_end(buffer));

        // binary, uppercase: -2
        // (uppercase has no effect because this base has no letters)
        // with prefix ("0b")
        end = kernaux_utoa(123, buffer, -2, "0b");
        assert(strcmp(buffer, "0b1111011") == 0);
        assert(end == str_end(buffer));

        // binary, uppercase, character alias: 'B'
        // (uppercase has no effect because this base has no letters)
        // no prefix (NULL)
        end = kernaux_utoa(123, buffer, 'B', NULL);
        assert(strcmp(buffer, "1111011") == 0);
        assert(end == str_end(buffer));

        // binary, uppercase, character alias: 'B'
        // (uppercase has no effect because this base has no letters)
        // no prefix ("")
        end = kernaux_utoa(123, buffer, 'B', "");
        assert(strcmp(buffer, "1111011") == 0);
        assert(end == str_end(buffer));

        // binary, uppercase, character alias: 'B'
        // (uppercase has no effect because this base has no letters)
        // with prefix ("0b")
        end = kernaux_utoa(123, buffer, 'B', "0b");
        assert(strcmp(buffer, "0b1111011") == 0);
        assert(end == str_end(buffer));

        // octal: 8
        // no prefix (NULL)
        end = kernaux_utoa(0123, buffer, 8, NULL);
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // octal: 8
        // no prefix ("")
        end = kernaux_utoa(0123, buffer, 8, "");
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
        // no prefix ("")
        end = kernaux_utoa(0123, buffer, 'o', "");
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // octal, character alias: 'o'
        // with prefix ("0o")
        end = kernaux_utoa(0123, buffer, 'o', "0o");
        assert(strcmp(buffer, "0o123") == 0);
        assert(end == str_end(buffer));

        // octal, uppercase: -8
        // (uppercase has no effect because this base has no letters)
        // no prefix (NULL)
        end = kernaux_utoa(0123, buffer, -8, NULL);
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // octal, uppercase: -8
        // (uppercase has no effect because this base has no letters)
        // no prefix ("")
        end = kernaux_utoa(0123, buffer, -8, "");
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // octal, uppercase: -8
        // (uppercase has no effect because this base has no letters)
        // with prefix ("0o")
        end = kernaux_utoa(0123, buffer, -8, "0o");
        assert(strcmp(buffer, "0o123") == 0);
        assert(end == str_end(buffer));

        // octal, uppercase, character alias: 'O'
        // (uppercase has no effect because this base has no letters)
        // no prefix (NULL)
        end = kernaux_utoa(0123, buffer, 'O', NULL);
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // octal, uppercase, character alias: 'O'
        // (uppercase has no effect because this base has no letters)
        // no prefix ("")
        end = kernaux_utoa(0123, buffer, 'O', "");
        assert(strcmp(buffer, "123") == 0);
        assert(end == str_end(buffer));

        // octal, uppercase, character alias: 'O'
        // (uppercase has no effect because this base has no letters)
        // with prefix ("0o")
        end = kernaux_utoa(0123, buffer, 'O', "0o");
        assert(strcmp(buffer, "0o123") == 0);
        assert(end == str_end(buffer));

        // hex: 16
        // no prefix (NULL)
        end = kernaux_utoa(0x123cafe, buffer, 16, NULL);
        assert(strcmp(buffer, "123cafe") == 0);
        assert(end == str_end(buffer));

        // hex: 16
        // no prefix ("")
        end = kernaux_utoa(0x123cafe, buffer, 16, "");
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
        // no prefix ("")
        end = kernaux_utoa(0x123cafe, buffer, 'x', "");
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

        // hex, character alias: 'h'
        // no prefix ("")
        end = kernaux_utoa(0x123cafe, buffer, 'h', "");
        assert(strcmp(buffer, "123cafe") == 0);
        assert(end == str_end(buffer));

        // hex, character alias: 'h'
        // with prefix ("0x")
        end = kernaux_utoa(0x123cafe, buffer, 'h', "0x");
        assert(strcmp(buffer, "0x123cafe") == 0);
        assert(end == str_end(buffer));

        // hex, uppercase: -16
        // no prefix (NULL)
        end = kernaux_utoa(0x123cafe, buffer, -16, NULL);
        assert(strcmp(buffer, "123CAFE") == 0);
        assert(end == str_end(buffer));

        // hex, uppercase: -16
        // no prefix ("")
        end = kernaux_utoa(0x123cafe, buffer, -16, "");
        assert(strcmp(buffer, "123CAFE") == 0);
        assert(end == str_end(buffer));

        // hex, uppercase: -16
        // with prefix ("0x")
        end = kernaux_utoa(0x123cafe, buffer, -16, "0x");
        assert(strcmp(buffer, "0x123CAFE") == 0);
        assert(end == str_end(buffer));

        // hex, uppercase, character alias: 'X'
        // no prefix (NULL)
        end = kernaux_utoa(0x123cafe, buffer, 'X', NULL);
        assert(strcmp(buffer, "123CAFE") == 0);
        assert(end == str_end(buffer));

        // hex, uppercase, character alias: 'X'
        // no prefix ("")
        end = kernaux_utoa(0x123cafe, buffer, 'X', "");
        assert(strcmp(buffer, "123CAFE") == 0);
        assert(end == str_end(buffer));

        // hex, uppercase, character alias: 'X'
        // with prefix ("0x")
        end = kernaux_utoa(0x123cafe, buffer, 'X', "0x");
        assert(strcmp(buffer, "0x123CAFE") == 0);
        assert(end == str_end(buffer));

        // hex, uppercase, character alias: 'H'
        // no prefix (NULL)
        end = kernaux_utoa(0x123cafe, buffer, 'H', NULL);
        assert(strcmp(buffer, "123CAFE") == 0);
        assert(end == str_end(buffer));

        // hex, uppercase, character alias: 'H'
        // no prefix ("")
        end = kernaux_utoa(0x123cafe, buffer, 'H', "");
        assert(strcmp(buffer, "123CAFE") == 0);
        assert(end == str_end(buffer));

        // hex, uppercase, character alias: 'H'
        // with prefix ("0x")
        end = kernaux_utoa(0x123cafe, buffer, 'H', "0x");
        assert(strcmp(buffer, "0x123CAFE") == 0);
        assert(end == str_end(buffer));

        // random base: 14
        // no prefix (NULL)
        end = kernaux_utoa(123456, buffer, 14, NULL);
        assert(strcmp(buffer, "32dc4") == 0);
        assert(end == str_end(buffer));

        // random base: 14
        // no prefix ("")
        end = kernaux_utoa(123456, buffer, 14, "");
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

        // random base, uppercase: -14
        // no prefix ("")
        end = kernaux_utoa(123456, buffer, -14, "");
        assert(strcmp(buffer, "32DC4") == 0);
        assert(end == str_end(buffer));

        // random base, uppercase: -14
        // with prefix ("foo")
        end = kernaux_utoa(123456, buffer, -14, "foo");
        assert(strcmp(buffer, "foo32DC4") == 0);
        assert(end == str_end(buffer));
    }

    return 0;
}
