#include "main.h"

void Init_default()
{
    init_version();
    init_assert();

#ifdef KERNAUX_VERSION_WITH_CMDLINE
    init_cmdline();
#endif // KERNAUX_VERSION_WITH_CMDLINE
#ifdef KERNAUX_VERSION_WITH_FILE
    init_file();
#endif // KERNAUX_VERSION_WITH_FILE
#ifdef KERNAUX_VERSION_WITH_NTOA
    init_ntoa();
#endif // KERNAUX_VERSION_WITH_NTOA
#ifdef KERNAUX_VERSION_WITH_PRINTF
    init_printf();
#endif // KERNAUX_VERSION_WITH_PRINTF
}
