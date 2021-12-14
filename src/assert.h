#include <kernaux/assert.h>

#ifdef ENABLE_ASSERT
#define assert(cond) kernaux_assert((cond))
#else
#define assert(cond) ((void)sizeof((cond)))
#endif

#define assert_return(cond)      { assert((cond)); if (!(cond)) return; }
#define assert_retval(cond, val) { assert((cond)); if (!(cond)) return (val); }
