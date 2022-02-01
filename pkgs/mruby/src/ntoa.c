#include "main.h"

#include <stdint.h>

#include <kernaux.h>

#include <mruby.h>
#include <mruby/presym.h>
#include <mruby/string.h>

static mrb_value rb_KernAux_utoa10(mrb_state *mrb, mrb_value self);
static mrb_value rb_KernAux_itoa10(mrb_state *mrb, mrb_value self);
static mrb_value rb_KernAux_utoa16(mrb_state *mrb, mrb_value self);
static mrb_value rb_KernAux_itoa16(mrb_state *mrb, mrb_value self);

void init_ntoa(mrb_state *const mrb)
{
    struct RClass *const rb_KernAux = mrb_module_get_id(mrb, MRB_SYM(KernAux));

    mrb_define_class_method(mrb, rb_KernAux, "utoa10",
                            rb_KernAux_utoa10, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, rb_KernAux, "itoa10",
                            rb_KernAux_itoa10, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, rb_KernAux, "utoa16",
                            rb_KernAux_utoa16, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, rb_KernAux, "itoa16",
                            rb_KernAux_itoa16, MRB_ARGS_REQ(1));
}

mrb_value rb_KernAux_utoa10(mrb_state *mrb, mrb_value self)
{
    mrb_int value = 0;
    mrb_get_args(mrb, "i", &value);

    if (value < 0) {
        mrb_raise(mrb, E_RANGE_ERROR,
                  "can't convert negative number to uint64_t");
    }

    char buffer[KERNAUX_UTOA10_BUFFER_SIZE];
    current_mrb_start(mrb);
    kernaux_utoa10(value, buffer);
    current_mrb_finish(mrb);

    mrb_value result = mrb_str_new_lit(mrb, "");
    result = mrb_str_cat_cstr(mrb, result, buffer);
    return result;
}

mrb_value rb_KernAux_itoa10(mrb_state *mrb, mrb_value self)
{
    mrb_int value = 0;
    mrb_get_args(mrb, "i", &value);

    char buffer[KERNAUX_ITOA10_BUFFER_SIZE];
    current_mrb_start(mrb);
    kernaux_itoa10(value, buffer);
    current_mrb_finish(mrb);

    mrb_value result = mrb_str_new_lit(mrb, "");
    result = mrb_str_cat_cstr(mrb, result, buffer);
    return result;
}

mrb_value rb_KernAux_utoa16(mrb_state *mrb, mrb_value self)
{
    mrb_int value = 0;
    mrb_get_args(mrb, "i", &value);

    if (value < 0) {
        mrb_raise(mrb, E_RANGE_ERROR,
                  "can't convert negative number to uint64_t");
    }

    char buffer[KERNAUX_UTOA16_BUFFER_SIZE];
    current_mrb_start(mrb);
    kernaux_utoa16(value, buffer);
    current_mrb_finish(mrb);

    mrb_value result = mrb_str_new_lit(mrb, "");
    result = mrb_str_cat_cstr(mrb, result, buffer);
    return result;
}

mrb_value rb_KernAux_itoa16(mrb_state *mrb, mrb_value self)
{
    mrb_int value = 0;
    mrb_get_args(mrb, "i", &value);

    char buffer[KERNAUX_ITOA16_BUFFER_SIZE];
    current_mrb_start(mrb);
    kernaux_itoa16(value, buffer);
    current_mrb_finish(mrb);

    mrb_value result = mrb_str_new_lit(mrb, "");
    result = mrb_str_cat_cstr(mrb, result, buffer);
    return result;
}
