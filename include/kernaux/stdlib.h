#ifndef KERNAUX_INCLUDED_STDLIB
#define KERNAUX_INCLUDED_STDLIB 1

#define KERNAUX_NULL ((void*)0)

#define KERNAUX_FALSE ((kernaux_bool)0)
#define KERNAUX_TRUE  ((kernaux_bool)1)

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char kernaux_bool;

void kernaux_memset(
    void *buffer,
    unsigned char value,
    unsigned long size
)
__attribute__((nonnull));

unsigned int kernaux_strlen(const char *s) __attribute__((nonnull));

char *kernaux_strncpy(
    char *dest,
    const char *src,
    unsigned long slen
)
__attribute__((nonnull));

void kernaux_itoa(int d, char *buf, int base) __attribute__((nonnull));

#ifdef __cplusplus
}
#endif

#endif
