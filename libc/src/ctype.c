#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <ctype.h>

int isdigit(const int c)
{
    return (unsigned)c - '0' < 10;
}

int islower(const int c)
{
    return (unsigned)c - 'a' < 26;
}

int isspace(const int c)
{
    return c == ' ' || (unsigned)c - '\t' < 5;
}

int isupper(const int c)
{
    return (unsigned)c - 'A' < 26;
}

int tolower(const int c)
{
    return isupper(c) ? (c + ('a' - 'A')) : c;
}

int toupper(const int c)
{
    return islower(c) ? (c - ('a' - 'A')) : c;
}
