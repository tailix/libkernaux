#ifndef KERNAUX_INCLUDED_PANIC
#define KERNAUX_INCLUDED_PANIC

#ifdef __cplusplus
extern "C" {
#endif

#ifdef KERNAUX_DEBUG
#define KERNAUX_PANIC(msg) (kernaux_assert_do(__FILE__, __LINE__, msg))
#define KERNAUX_ASSERT(cond) ((cond) ? (void)0 : KERNAUX_PANIC(#cond))
#else
#define KERNAUX_PANIC(msg) ((void)0)
#define KERNAUX_ASSERT(cond) ((void)0)
#endif

void kernaux_assert_do(const char *file, int line, const char *msg);

extern void (*kernaux_assert_cb)(const char *file, int line, const char *msg);

#ifdef __cplusplus
}
#endif

#endif
