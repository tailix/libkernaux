#include <mruby.h>

void init_assert(mrb_state *mrb);

void mrb_mruby_kernaux_gem_final(mrb_state *const mrb) {}

void mrb_mruby_kernaux_gem_init(mrb_state *const mrb)
{
    init_assert(mrb);
}
