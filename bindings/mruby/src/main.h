#ifndef __MAIN_H__
#define __MAIN_H__

#include <kernaux.h>
#include <mruby.h>

void current_mrb_start(mrb_state *mrb);
void current_mrb_finish(mrb_state *mrb);
mrb_state *current_mrb_get();

void init_assert(mrb_state *mrb);
void init_version(mrb_state *mrb);

#ifdef KERNAUX_VERSION_SUPPORTS_CMDLINE
void init_cmdline(mrb_state *mrb);
#endif // KERNAUX_VERSION_SUPPORTS_CMDLINE
#ifdef KERNAUX_VERSION_SUPPORTS_NTOA
void init_ntoa(mrb_state *mrb);
#endif // KERNAUX_VERSION_SUPPORTS_NTOA
#ifdef KERNAUX_VERSION_SUPPORTS_PRINTF
void init_printf(mrb_state *mrb);
#endif // KERNAUX_VERSION_SUPPORTS_PRINTF

#endif
