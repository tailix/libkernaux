#include "main.h"

void Init_default()
{
    init_version();
    init_assert();

#ifdef KERNAUX_VERSION_SUPPORTS_CMDLINE
    init_cmdline();
#endif // KERNAUX_VERSION_SUPPORTS_CMDLINE
#ifdef KERNAUX_VERSION_SUPPORTS_FILE
    init_file();
#endif // KERNAUX_VERSION_SUPPORTS_FILE
#ifdef KERNAUX_VERSION_SUPPORTS_NTOA
    init_ntoa();
#endif // KERNAUX_VERSION_SUPPORTS_NTOA
#ifdef KERNAUX_VERSION_SUPPORTS_PRINTF
    init_printf();
#endif // KERNAUX_VERSION_SUPPORTS_PRINTF
}
