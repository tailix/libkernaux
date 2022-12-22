#ifndef KERNAUX_INCLUDED_ASSERT
#define KERNAUX_INCLUDED_ASSERT

#include <kernaux/runtime.h>

#ifdef ENABLE_ASSERT
#define KERNAUX_PANIC(msg) (kernaux_assert_do(__FILE__, __LINE__, msg))
#define KERNAUX_ASSERT(cond) ((cond) ? (void)0 : KERNAUX_PANIC(#cond))
#else
#define KERNAUX_PANIC(msg) ((void)0)
#define KERNAUX_ASSERT(cond) ((void)0)
#endif

#define KERNAUX_NOTNULL(cond) KERNAUX_ASSERT(cond)

#endif
