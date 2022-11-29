#ifndef KERNAUX_INCLUDED_LIBC
#define KERNAUX_INCLUDED_LIBC

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

struct KernAux_Libc {
    void (*abort)() __attribute__((noreturn));
    void (*exit)(int status) __attribute__((noreturn));

    void *(*calloc)(size_t nmemb, size_t size);
    void  (*free)(void *ptr);
    void *(*malloc)(size_t size);
    void *(*realloc)(void *ptr, size_t size);
};

extern struct KernAux_Libc kernaux_libc;

#ifdef __cplusplus
}
#endif

#endif
