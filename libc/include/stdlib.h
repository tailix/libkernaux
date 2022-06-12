#ifndef _STDLIB_H
#define _STDLIB_H 1

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int atoi(const char *str);

void abort();
void exit(int status);

void free(void *ptr);
void *realloc(void *ptr, size_t size);

#ifdef __cplusplus
}
#endif

#endif
