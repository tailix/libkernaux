#include "main.h"

#include <kernaux.h>

#include <mruby.h>
#include <mruby/array.h>
#include <mruby/presym.h>

static mrb_value rb_KernAux_snprintf1(mrb_state *mrb, mrb_value self);

void init_printf(mrb_state *const mrb)
{
    struct RClass *const rb_KernAux = mrb_module_get_id(mrb, MRB_SYM(KernAux));

    mrb_define_class_method(mrb, rb_KernAux, "snprintf1", rb_KernAux_snprintf1,
                            MRB_ARGS_REQ(2) | MRB_ARGS_OPT(2));
}

mrb_value rb_KernAux_snprintf1(mrb_state *const mrb, mrb_value self)
{
    mrb_value values[2];
    values[0] = mrb_obj_freeze(mrb, mrb_str_new_lit(mrb, ""));
    values[1] = mrb_nil_value();
    return mrb_obj_freeze(mrb, mrb_ary_new_from_values(mrb, 2, values));
}
