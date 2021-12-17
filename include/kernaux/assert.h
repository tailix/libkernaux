#ifndef KERNAUX_INCLUDED_ASSERT
#define KERNAUX_INCLUDED_ASSERT 1

#ifdef __cplusplus
extern "C" {
#endif

#ifdef KERNAUX_ENABLE_ASSERT
#define KERNAUX_ASSERT(cond) \
    ((cond) ? (void)0 : kernaux_assert_do(__FILE__, __LINE__, #cond))
#else
#define KERNAUX_ASSERT(cond) ((void)sizeof((cond)))
#endif

#define KERNAUX_ASSERT_RETURN(cond) \
    { KERNAUX_ASSERT(cond); if (!(cond)) return; }
#define KERNAUX_ASSERT_RETVAL(cond, val) \
    { KERNAUX_ASSERT(cond); if (!(cond)) return (val); }

#ifdef KERNAUX_ENABLE_NULL_GUARD
#define KERNAUX_NOTNULL_RETURN(cond)      { KERNAUX_ASSERT_RETURN(cond);      }
#define KERNAUX_NOTNULL_RETVAL(cond, val) { KERNAUX_ASSERT_RETVAL(cond, val); }
#else
#define KERNAUX_NOTNULL_RETURN(cond)      { KERNAUX_ASSERT(cond); }
#define KERNAUX_NOTNULL_RETVAL(cond, val) { KERNAUX_ASSERT(cond); }
#endif

void kernaux_assert_do(const char *file, int line, const char *str);

extern void (*kernaux_assert_cb)(const char *file, int line, const char *str);

#ifdef __cplusplus
}
#endif

#endif
