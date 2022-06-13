#ifndef __MAIN_H__
#define __MAIN_H__

#include <kernaux.h>
#include <ruby.h>

void init_version();
void init_assert();

#ifdef KERNAUX_VERSION_SUPPORTS_CMDLINE
void init_cmdline();
#endif // KERNAUX_VERSION_SUPPORTS_CMDLINE
#ifdef KERNAUX_VERSION_SUPPORTS_FILE
void init_file();
#endif // KERNAUX_VERSION_SUPPORTS_FILE
#ifdef KERNAUX_VERSION_SUPPORTS_NTOA
void init_ntoa();
#endif // KERNAUX_VERSION_SUPPORTS_NTOA
#ifdef KERNAUX_VERSION_SUPPORTS_PRINTF
void init_printf();
#endif // KERNAUX_VERSION_SUPPORTS_PRINTF

#endif
