#ifndef __MAIN_H__
#define __MAIN_H__

#include <kernaux.h>
#include <ruby.h>

void init_version();
void init_assert();

#ifdef KERNAUX_VERSION_WITH_CMDLINE
void init_cmdline();
#endif // KERNAUX_VERSION_WITH_CMDLINE
#ifdef KERNAUX_VERSION_WITH_FILE
void init_file();
#endif // KERNAUX_VERSION_WITH_FILE
#ifdef KERNAUX_VERSION_WITH_NTOA
void init_ntoa();
#endif // KERNAUX_VERSION_WITH_NTOA
#ifdef KERNAUX_VERSION_WITH_PRINTF
void init_printf();
#endif // KERNAUX_VERSION_WITH_PRINTF

#endif
