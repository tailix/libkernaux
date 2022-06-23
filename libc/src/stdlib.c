#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

// TODO: stub
void exit(const int status __attribute__((unused)))
{
    for (;;);
}

// TODO: stub
void abort()
{
    exit(EXIT_FAILURE);
}

int atoi(const char *str)
{
    while (isspace(*str)) ++str;
    bool is_negative = false;
    switch (*str) {
    case '-': is_negative = true; // fall through
    case '+': ++str;
    }
    int result = 0;
    while (isdigit(*str)) result = 10 * result - (*str++ - '0');
    return is_negative ? result : -result;
}
