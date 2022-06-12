#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <kernaux.h>
#include <ruby.h>

void init_assert();
void init_ntoa();
#ifdef HAVE_KERNAUX_CMDLINE
void init_cmdline();
#endif // HAVE_KERNAUX_CMDLINE
#ifdef HAVE_KERNAUX_FILE_CREATE
void init_file();
#endif // HAVE_KERNAUX_FILE_CREATE
#ifdef HAVE_KERNAUX_SNPRINTF
void init_printf();
#endif // HAVE_KERNAUX_SNPRINTF

void Init_default()
{
    init_assert();
    init_ntoa();
#ifdef HAVE_KERNAUX_CMDLINE
    init_cmdline();
#endif // HAVE_KERNAUX_CMDLINE
#ifdef HAVE_KERNAUX_FILE_CREATE
    init_file();
#endif // HAVE_KERNAUX_FILE_CREATE
#ifdef HAVE_KERNAUX_SNPRINTF
    init_printf();
#endif // HAVE_KERNAUX_SNPRINTF
}
