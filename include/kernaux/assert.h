#ifndef KERNAUX_INCLUDED_ASSERT
#define KERNAUX_INCLUDED_ASSERT 1

#ifdef __cplusplus
extern "C" {
#endif

#define kernaux_assert(cond) \
    { if (!(cond)) kernaux_assert_do(__FILE__, __LINE__, #cond); }

void kernaux_assert_do(const char *file, int line, const char *str);

extern void (*kernaux_assert_cb)(const char *file, int line, const char *str);

#ifdef __cplusplus
}
#endif

#endif
