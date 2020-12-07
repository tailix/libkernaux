#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/printf.h>
#include <kernaux/stdlib.h>

#include <stdbool.h>

enum NoneNumberDynamic { NONE, NUMBER, DYNAMIC };

enum Length { LEN0, LEN_hh, LEN_h, LEN_l, LEN_ll, LEN_L, LEN_z, LEN_j, LEN_t };

enum Type {
    TYPE0,
    TYPE_PERCENT,
    TYPE_di,
    TYPE_u,
    TYPE_fF,
    TYPE_eE,
    TYPE_gG,
    TYPE_xX,
    TYPE_o,
    TYPE_s,
    TYPE_c,
    TYPE_p,
    TYPE_aA,
    TYPE_n,
};

struct Formatter {
    bool flag_minus;      // -
    bool flag_plus;       // +
    bool flag_space;      // space
    bool flag_zero;       // 0
    bool flag_apostrophe; // '
    bool flag_hash;       // #

    enum NoneNumberDynamic width;
    unsigned int width_number;

    enum NoneNumberDynamic precision;
    unsigned int precision_number;

    enum Length length;
    enum Type type;
};

inline static struct Formatter Formatter_new();

void kernaux_printf(void (*putchar)(char), const char *const format, ...)
{
    va_list va;
    va_start(va, format);
    kernaux_printf_va(putchar, format, va);
    va_end(va);
}

void kernaux_printf_va(
    void (*const putchar)(char),
    const char *const format,
    va_list va
) {
    struct Formatter formatter = Formatter_new();

    for (const char *current = format; *current;) {
        if (*current != '%') {
            putchar(*current);
            ++current;
            continue;
        }

        ++current; // skip %
        formatter = Formatter_new();

        for (bool loop = true; loop;) {
            switch (*current) {
            case '-':  formatter.flag_minus      = true; break;
            case '+':  formatter.flag_plus       = true; break;
            case ' ':  formatter.flag_space      = true; break;
            case '0':  formatter.flag_zero       = true; break;
            case '\'': formatter.flag_apostrophe = true; break;
            case '#':  formatter.flag_hash       = true; break;
            default: loop = false;
            }
            if (loop) ++current;
        }

        for (; *current >= '1' && *current <= '9'; ++current) {
            // TODO: implement width parsing
        }

        if (*current == '.') {
            for (++current; *current >= '1' && *current <= '9'; ++current) {
                // TODO: implement precision parsing
            }
        }

        switch (*current) {
        case 'h':
            if (*(++current) == 'h') {
                formatter.length = LEN_hh;
                ++current;
            }
            else {
                formatter.length = LEN_h;
            }
            break;
        case 'l':
            if (*(++current) == 'l') {
                formatter.length = LEN_ll;
                ++current;
            }
            else {
                formatter.length = LEN_l;
            }
            break;
        case 'L':
            formatter.length = LEN_L;
            ++current;
            break;
        case 'z':
            formatter.length = LEN_z;
            ++current;
            break;
        case 'j':
            formatter.length = LEN_j;
            ++current;
            break;
        case 't':
            formatter.length = LEN_t;
            ++current;
            break;
        }

        switch (*current) {
        case '%':
            formatter.type = TYPE_PERCENT;
            ++current;
            break;
        case 'd':
        case 'i':
            formatter.type = TYPE_di;
            ++current;
            break;
        case 'u':
            formatter.type = TYPE_u;
            ++current;
            break;
        case 'f':
        case 'F':
            formatter.type = TYPE_fF;
            ++current;
            break;
        case 'e':
        case 'E':
            formatter.type = TYPE_eE;
            ++current;
            break;
        case 'g':
        case 'G':
            formatter.type = TYPE_gG;
            ++current;
            break;
        case 'x':
        case 'X':
            formatter.type = TYPE_xX;
            ++current;
            break;
        case 'o':
            formatter.type = TYPE_o;
            ++current;
            break;
        case 's':
            formatter.type = TYPE_s;
            ++current;
            break;
        case 'c':
            formatter.type = TYPE_c;
            ++current;
            break;
        case 'p':
            formatter.type = TYPE_p;
            ++current;
            break;
        case 'a':
        case 'A':
            formatter.type = TYPE_aA;
            ++current;
            break;
        case 'n':
            formatter.type = TYPE_n;
            ++current;
            break;
        }

        if (formatter.type == TYPE_PERCENT) {
            putchar('%');
        }
        else if (formatter.type == TYPE_u) {
            const unsigned int arg = va_arg(va, unsigned int);

            char buf[20];
            kernaux_itoa(arg, buf, 'd');

            for (const char *arg_ptr = buf; *arg_ptr; ++arg_ptr) {
                putchar(*arg_ptr);
            }
        }
        else if (formatter.type == TYPE_s) {
            const char *const arg = va_arg(va, char*);

            for (const char *arg_ptr = arg; *arg_ptr; ++arg_ptr) {
                putchar(*arg_ptr);
            }
        }
        else if (formatter.type == TYPE_c) {
            const char arg = va_arg(va, int);
            putchar(arg);
        }
    }

    putchar('\0');
}

struct Formatter Formatter_new()
{
    struct Formatter result = {
        .flag_minus      = false,
        .flag_plus       = false,
        .flag_space      = false,
        .flag_zero       = false,
        .flag_apostrophe = false,
        .flag_hash       = false,

        .width = NONE,
        .width_number = 0,

        .precision = NONE,
        .precision_number = 0,

        .length = LEN0,
        .type   = TYPE0,
    };

    return result;
}
