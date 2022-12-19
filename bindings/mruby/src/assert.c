#include "main.h"

#include <mruby/presym.h>
#include <mruby/string.h>
#include <mruby/variable.h>

static void assert_cb(const char *file, int line, const char *msg);

static mrb_value rb_KernAux_assert_cb(mrb_state *mrb, mrb_value self);
static mrb_value rb_KernAux_assert_cb_EQ(mrb_state *mrb, mrb_value self);
static mrb_value rb_KernAux_assert_do(mrb_state *mrb, mrb_value self);

void init_assert(mrb_state *const mrb)
{
    kernaux_assert_cb = assert_cb;

    struct RClass *const rb_KernAux = mrb_module_get_id(mrb, MRB_SYM(KernAux));
    mrb_define_class_method(mrb, rb_KernAux, "assert_cb",
                            rb_KernAux_assert_cb, MRB_ARGS_NONE());
    mrb_define_class_method(mrb, rb_KernAux, "assert_cb=",
                            rb_KernAux_assert_cb_EQ, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, rb_KernAux, "assert_do",
                            rb_KernAux_assert_do, MRB_ARGS_REQ(3));
}

void assert_cb(const char *const file, const int line, const char *const msg)
{
    mrb_state *const mrb = current_mrb_get();
    if (!mrb) return;

    struct RClass *const self_rbc = mrb_module_get_id(mrb, MRB_SYM(KernAux));
    mrb_value self_rb = mrb_obj_value(self_rbc);

    mrb_value assert_cb_rb = mrb_iv_get(mrb, self_rb, MRB_IVSYM(assert_cb));
    if (mrb_nil_p(assert_cb_rb)) return;

    mrb_value file_rb = mrb_str_new_lit(mrb, "");
    file_rb = mrb_str_cat_cstr(mrb, file_rb, file);

    mrb_value line_rb = mrb_fixnum_value(line);

    mrb_value msg_rb = mrb_str_new_lit(mrb, "");
    msg_rb = mrb_str_cat_cstr(mrb, msg_rb, msg);

    mrb_funcall_id(
        mrb, assert_cb_rb, MRB_SYM(call), 3, file_rb, line_rb, msg_rb);
}

mrb_value rb_KernAux_assert_cb(mrb_state *const mrb, const mrb_value self_rb)
{
    return mrb_iv_get(mrb, self_rb, MRB_IVSYM(assert_cb));
}

mrb_value rb_KernAux_assert_cb_EQ(mrb_state *const mrb, const mrb_value self_rb)
{
    mrb_value assert_cb_rb = mrb_nil_value();
    mrb_get_args(mrb, "o", &assert_cb_rb);
    mrb_iv_set(mrb, self_rb, MRB_IVSYM(assert_cb), assert_cb_rb);
    return assert_cb_rb;
}

mrb_value rb_KernAux_assert_do(mrb_state *const mrb, const mrb_value self_rb)
{
    const char *file = NULL;
    mrb_int line_rb = 0;
    const char *msg = NULL;
    mrb_get_args(mrb, "ziz", &file, &line_rb, &msg);

    current_mrb_start(mrb);
    kernaux_assert_do(file, 0, msg);
    current_mrb_finish(mrb);

    return mrb_nil_value();
}
