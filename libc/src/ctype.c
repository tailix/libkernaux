#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <ctype.h>

int isdigit(const int c)
{
    return (unsigned)c - '0' < 10;
}

int isspace(const int c)
{
    return c == ' ' || (unsigned)c - '\t' < 5;
}
