#include <mruby.h>

void mrb_mruby_kernaux_gem_final(mrb_state *mrb) {}

void mrb_mruby_kernaux_gem_init(mrb_state *mrb)
{
    /* struct RClass *const rb_KernAux = */ mrb_define_module(mrb, "KernAux");
}
