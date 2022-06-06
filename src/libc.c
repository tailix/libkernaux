#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/libc.h>

#include <stdbool.h>

#ifdef WITH_LIBC_ATOI
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
#endif // WITH_LIBC_ATOI

#ifdef WITH_LIBC_ISDIGIT
int isdigit(const int c)
{
    return (unsigned)c - '0' < 10;
}
#endif // WITH_LIBC_ISDIGIT

#ifdef WITH_LIBC_ISSPACE
int isspace(const int c)
{
    return c == ' ' || (unsigned)c - '\t' < 5;
}
#endif // WITH_LIBC_ISSPACE

#ifdef WITH_LIBC_MEMCPY
void *memcpy(void *dest, const void *src, size_t n)
{
    char *dest_cell = dest;
    char *src_cell = src;
    while (n--) *dest_cell++ = *src_cell++;
    return dest;
}
#endif // WITH_LIBC_MEMCPY

#ifdef WITH_LIBC_MEMMOVE
void *memmove(void *dest, const void *src, size_t n)
{
    char *dest_cell = dest;
    char *src_cell = src;
    if (dest_cell <= src_cell) {
        while (n--) *dest_cell++ = *src_cell++;
    } else {
        dest_cell += n;
        src_cell += n;
        while (n--) *--dest_cell = *--src_cell;
    }
    return dest;
}
#endif // WITH_LIBC_MEMMOVE

#ifdef WITH_LIBC_MEMSET
void *memset(void *s, int c, size_t n)
{
    char *ss = s;
    while (n--) *ss++ = c;
    return s;
}
#endif // WITH_LIBC_MEMSET

#ifdef WITH_LIBC_STRCMP
int strcmp(const char *s1, const char *s2)
{
    for (; *s1; ++s1, ++s2) if (*s1 != *s2) return *s1 < *s2 ? -1 : 1;
    return 0;
}
#endif // WITH_LIBC_STRCMP

#ifdef WITH_LIBC_STRCPY
char *strcpy(char *dest, const char *src)
{
    char *tmp = dest;
    while ((*dest++ = *src++) != '\0');
    return tmp;
}
#endif // WITH_LIBC_STRCPY

#ifdef WITH_LIBC_STRLEN
size_t strlen(const char *s)
{
    const char *ss = s;
    while (*ss != '\0') ++ss;
    return ss - s;
}
#endif // WITH_LIBC_STRLEN

#ifdef WITH_LIBC_STRNCMP
int strncmp(const char *s1, const char *s2, size_t n)
{
    for (; *s1 && n; ++s1, ++s2, --n) if (*s1 != *s2) return *s1 < *s2 ? -1 : 1;
    return 0;
}
#endif // WITH_LIBC_STRNCMP

#ifndef WITH_LIBC_STRNCPY
char *strncpy(char *dest, const char *src, size_t n)
{
    char *tmp = dest;
    while (n-- && (*dest++ = *src++) != '\0');
    return tmp;
}
#endif // WITH_LIBC_STRNCPY

#ifdef WITH_LIBC_STRNLEN
size_t strnlen(const char *s, size_t maxlen)
{
    const char *ss = s;
    while (*ss != '\0' && maxlen--) ++ss;
    return ss - s;
}
#endif // WITH_LIBC_STRNLEN

#ifdef WITH_LIBC_STRSTR
char *strstr(const char *haystack, const char *needle)
{
    const size_t needle_slen = strlen(needle);
    if (!needle_slen) return (char*)haystack;

    size_t haystack_slen = strlen(haystack);
    while (haystack_slen >= needle_slen) {
        --haystack_slen;
        if (!memcmp(haystack, needle, needle_slen)) return (char*)haystack;
        ++haystack;
    }

    return NULL;
}
#endif // WITH_LIBC_STRSTR
