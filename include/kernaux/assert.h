#ifndef KERNAUX_INCLUDED_ASSERT
#define KERNAUX_INCLUDED_ASSERT

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>

#ifdef KERNAUX_DISABLE_ASSERT
#define KERNAUX_PANIC(msg) ((void)0)
#define KERNAUX_ASSERT(cond) ((void)0)
#else
#define KERNAUX_PANIC(msg) (kernaux_assert_do(__FILE__, __LINE__, msg))
#define KERNAUX_ASSERT(cond) ((cond) ? (void)0 : KERNAUX_PANIC(#cond))
#endif

#define KERNAUX_NOTNULL(cond) KERNAUX_ASSERT(cond)

typedef void (*KernAux_Assert_Cb)(const char *file, int line, const char *msg);

extern KernAux_Assert_Cb kernaux_assert_cb;

KERNAUX_NORETURN
void kernaux_assert_do(const char *file, int line, const char *msg);

#ifdef __cplusplus
}
#endif

#endif
