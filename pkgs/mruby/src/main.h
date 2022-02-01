#ifndef __MAIN_H__
#define __MAIN_H__

#include <mruby.h>

void current_mrb_start(mrb_state *mrb);
void current_mrb_finish(mrb_state *mrb);
mrb_state *current_mrb_get();

void init_assert(mrb_state *mrb);
void init_ntoa(mrb_state *mrb);

#endif
