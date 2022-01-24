#ifndef KERNAUX_INCLUDED_ASSERT
#define KERNAUX_INCLUDED_ASSERT

#ifdef __cplusplus
extern "C" {
#endif

#define KERNAUX_PANIC(msg) (kernaux_assert_do(__FILE__, __LINE__, #msg))
#define KERNAUX_ASSERT(cond) ((cond) ? (void)0 : KERNAUX_PANIC(cond))

#define KERNAUX_PANIC_RETURN(msg)         do { KERNAUX_PANIC(msg);                return;       } while (0)
#define KERNAUX_PANIC_RETVAL(msg, val)    do { KERNAUX_PANIC(msg);                return (val); } while (0)

#define KERNAUX_ASSERT_RETURN(cond)       do { KERNAUX_ASSERT(cond); if (!(cond)) return;       } while (0)
#define KERNAUX_ASSERT_RETVAL(cond, val)  do { KERNAUX_ASSERT(cond); if (!(cond)) return (val); } while (0)

#define KERNAUX_NOTNULL_RETURN(cond)      do { KERNAUX_ASSERT(cond); if (!(cond)) return;       } while (0)
#define KERNAUX_NOTNULL_RETVAL(cond, val) do { KERNAUX_ASSERT(cond); if (!(cond)) return (val); } while (0)

void kernaux_assert_do(const char *file, int line, const char *str);

extern void (*kernaux_assert_cb)(const char *file, int line, const char *str);

#ifdef __cplusplus
}
#endif

#endif
