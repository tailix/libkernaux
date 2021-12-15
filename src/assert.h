#ifndef _ASSERT_H
#define _ASSERT_H

#include <kernaux/assert.h>

#ifdef ENABLE_ASSERT
#define assert(cond) kernaux_assert(cond)
#else
#define assert(cond) ((void)sizeof((cond)))
#endif

#define assert_return(cond)       { assert(cond); if (!(cond)) return;       }
#define assert_retval(cond, val)  { assert(cond); if (!(cond)) return (val); }

#ifdef ENABLE_NULL_GUARD
#define notnull_return(cond)      { assert_return(cond);      }
#define notnull_retval(cond, val) { assert_retval(cond, val); }
#else
#define notnull_return(cond)      { assert(cond); }
#define notnull_retval(cond, val) { assert(cond); }
#endif

#endif
