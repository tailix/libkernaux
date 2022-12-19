#ifndef __MAIN_H__
#define __MAIN_H__

#include <kernaux.h>
#include <mruby.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void current_mrb_start(mrb_state *mrb);
void current_mrb_finish(mrb_state *mrb);
mrb_state *current_mrb_get();

void init_assert(mrb_state *mrb);
void init_version(mrb_state *mrb);

#ifdef KERNAUX_VERSION_WITH_CMDLINE
void init_cmdline(mrb_state *mrb);
#endif // KERNAUX_VERSION_WITH_CMDLINE
#ifdef KERNAUX_VERSION_WITH_NTOA
void init_ntoa(mrb_state *mrb);
#endif // KERNAUX_VERSION_WITH_NTOA
#ifdef KERNAUX_VERSION_WITH_PRINTF
void init_printf(mrb_state *mrb);
#endif // KERNAUX_VERSION_WITH_PRINTF

#endif
