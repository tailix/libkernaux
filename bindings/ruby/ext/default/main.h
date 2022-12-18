#ifndef __MAIN_H__
#define __MAIN_H__

#include <kernaux.h>
#include <ruby.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern ID rb_intern_call;
extern ID rb_intern_freeze;
extern ID rb_intern_LESS;
extern ID rb_intern_new;

extern VALUE rb_KernAux;
extern VALUE rb_KernAux_Error;

void init_version();
void init_assert();

#ifdef KERNAUX_VERSION_WITH_CMDLINE
void init_cmdline();
#endif // KERNAUX_VERSION_WITH_CMDLINE
#ifdef KERNAUX_VERSION_WITH_NTOA
void init_ntoa();
#endif // KERNAUX_VERSION_WITH_NTOA
#ifdef KERNAUX_VERSION_WITH_PRINTF
void init_printf();
#endif // KERNAUX_VERSION_WITH_PRINTF

#endif
