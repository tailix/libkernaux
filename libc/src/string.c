#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stddef.h>
#include <string.h>

int memcmp(const void *s1, const void *s2, size_t n)
{
    for (const unsigned char *p1 = s1, *p2 = s2; n--; ++p1, ++p2) {
        if (*p1 != *p2) return *p1 - *p2;
    }
    return 0;
}

void *memcpy(void *dest, const void *src, size_t n)
{
    char *dest_cell = dest;
    char *src_cell = (char*)src;
    while (n--) *dest_cell++ = *src_cell++;
    return dest;
}

void *memmove(void *dest, const void *src, size_t n)
{
    char *dest_cell = dest;
    char *src_cell = (char*)src;
    if (dest_cell <= src_cell) {
        while (n--) *dest_cell++ = *src_cell++;
    } else {
        dest_cell += n;
        src_cell += n;
        while (n--) *--dest_cell = *--src_cell;
    }
    return dest;
}

void *memchr(const void *s, int c, size_t n)
{
    for (const unsigned char *p = s; n--; ++p) {
        if ((unsigned char)c == *p) return (void*)p;
    }
    return NULL;
}

void *memset(void *s, int c, size_t n)
{
    char *ss = s;
    while (n--) *ss++ = c;
    return s;
}

char *strcat(char *dest, const char *src)
{
    char *const dest_start = dest;
    while (*dest) ++dest;
    while ((*dest++ = *src++));
    return dest_start;
}

char *strchr(const char *s, int c)
{
    for (; *s != (char)c; ++s) if (*s == '\0') return NULL;
    return (char*)s;
}

int strcmp(const char *s1, const char *s2)
{
    for (; *s1; ++s1, ++s2) if (*s1 != *s2) return *s1 < *s2 ? -1 : 1;
    return 0;
}

char *strcpy(char *dest, const char *src)
{
    char *tmp = dest;
    while ((*dest++ = *src++) != '\0');
    return tmp;
}

size_t strlen(const char *s)
{
    const char *ss = s;
    while (*ss != '\0') ++ss;
    return ss - s;
}

char *strncat(char *dest, const char *src, size_t n)
{
    char *const dest_start = dest;
    if (n) {
        while (*dest) ++dest;
        while ((*dest++ = *src++)) {
            if (--n == 0) {
                *dest = '\0';
                break;
            }
        }
    }
    return dest_start;
}

int strncmp(const char *s1, const char *s2, size_t n)
{
    for (; *s1 && n; ++s1, ++s2, --n) if (*s1 != *s2) return *s1 < *s2 ? -1 : 1;
    return 0;
}

char *strncpy(char *dest, const char *src, size_t n)
{
    char *tmp = dest;
    while (n-- && (*dest++ = *src++) != '\0');
    return tmp;
}

size_t strnlen(const char *s, size_t maxlen)
{
    const char *ss = s;
    while (*ss != '\0' && maxlen--) ++ss;
    return ss - s;
}

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
