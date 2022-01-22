#ifndef KERNAUX_INCLUDED_ASSERT
#define KERNAUX_INCLUDED_ASSERT

#ifdef __cplusplus
extern "C" {
#endif

#define KERNAUX_PANIC(msg) (kernaux_assert_do(__FILE__, __LINE__, #msg))

#ifdef KERNAUX_ENABLE_ASSERT
#define KERNAUX_ASSERT(cond) \
    ((cond) ? (void)0 : kernaux_assert_do(__FILE__, __LINE__, #cond))
#else
#define KERNAUX_ASSERT(cond) ((void)sizeof((cond)))
#endif

#ifdef KERNAUX_ENABLE_GUARD
#define KERNAUX_ASSERT_RETURN(cond)       { KERNAUX_ASSERT(cond); if (!(cond)) return;       }
#define KERNAUX_ASSERT_RETVAL(cond, val)  { KERNAUX_ASSERT(cond); if (!(cond)) return (val); }
#else
#define KERNAUX_ASSERT_RETURN(cond)       { KERNAUX_ASSERT(cond); }
#define KERNAUX_ASSERT_RETVAL(cond, val)  { KERNAUX_ASSERT(cond); }
#endif

#ifdef KERNAUX_ENABLE_GUARD
#define KERNAUX_NOTNULL_RETURN(cond)      { KERNAUX_ASSERT(cond); if (!(cond)) return;       }
#define KERNAUX_NOTNULL_RETVAL(cond, val) { KERNAUX_ASSERT(cond); if (!(cond)) return (val); }
#else
#define KERNAUX_NOTNULL_RETURN(cond)      { KERNAUX_ASSERT(cond); }
#define KERNAUX_NOTNULL_RETVAL(cond, val) { KERNAUX_ASSERT(cond); }
#endif

#ifdef KERNAUX_ENABLE_GUARD
#define KERNAUX_PANIC_RETURN(msg)         { KERNAUX_PANIC(msg); return;       }
#define KERNAUX_PANIC_RETVAL(msg, val)    { KERNAUX_PANIC(msg); return (val); }
#else
#define KERNAUX_PANIC_RETURN(msg)         { KERNAUX_PANIC(msg); }
#define KERNAUX_PANIC_RETVAL(msg, val)    { KERNAUX_PANIC(msg); }
#endif

void kernaux_assert_do(const char *file, int line, const char *str);

extern void (*kernaux_assert_cb)(const char *file, int line, const char *str);

#ifdef __cplusplus
}
#endif

#endif
