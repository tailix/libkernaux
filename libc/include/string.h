#ifndef _STRING_H
#define _STRING_H 1

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

int memcmp(const void *s1, const void *s2, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memchr(const void *s, int c, size_t n);
void *memset(void *s, int c, size_t n);
char *strcat(char *dest, const char *src);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
size_t strlen(const char *s);
int strncmp(const char *s1, const char *s2, size_t n);
char *strncpy(char *dest, const char *src, size_t n);
size_t strnlen(const char *s, size_t maxlen);
char *strstr(const char *haystack, const char *needle);

#ifdef __cplusplus
}
#endif

#endif
