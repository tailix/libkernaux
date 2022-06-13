#ifndef KERNAUX_INCLUDED_ASSERT
#define KERNAUX_INCLUDED_ASSERT

#ifdef __cplusplus
extern "C" {
#endif

#define KERNAUX_PANIC(msg) (kernaux_assert_do(__FILE__, __LINE__, msg))
#define KERNAUX_ASSERT(cond) ((cond) ? (void)0 : KERNAUX_PANIC(#cond))

void kernaux_assert_do(const char *file, int line, const char *msg);

extern void (*kernaux_assert_cb)(const char *file, int line, const char *msg);

#ifdef __cplusplus
}
#endif

#endif
