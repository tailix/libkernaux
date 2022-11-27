#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/libc.h>

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void exit(const int status)
{
    // Custom implementation
    kernaux_libc.exit(status);
}

void abort()
{
    // Custom implementation
    if (kernaux_libc.abort) kernaux_libc.abort();

    // Default implementation
    exit(EXIT_FAILURE);
}

void *calloc(const size_t nmemb, const size_t size)
{
    // Custom implementation
    if (kernaux_libc.calloc) return kernaux_libc.calloc(nmemb, size);

    // Default implementation
    const size_t total_size = nmemb * size;
    if (!total_size) return NULL;
    if (total_size / nmemb != size) return NULL;
    void *const ptr = malloc(total_size);
    if (ptr) memset(ptr, 0, total_size);
    return ptr;
}

void free(void *const ptr)
{
    // Custom implementation
    kernaux_libc.free(ptr);
}

void *malloc(const size_t size)
{
    // Custom implementation
    return kernaux_libc.malloc(size);
}

void *realloc(void *const ptr, const size_t size)
{
    // Custom implementation
    return kernaux_libc.realloc(ptr, size);
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
