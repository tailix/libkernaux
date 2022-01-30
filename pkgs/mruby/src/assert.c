#include <kernaux.h>

#include <mruby.h>
#include <mruby/variable.h>

static void assert_cb(const char *file, int line, const char *msg);

static mrb_value rb_KernAux_assert_cb(mrb_state *mrb, mrb_value self);
static mrb_value rb_KernAux_assert_cb_EQ(mrb_state *mrb, mrb_value self);
static mrb_value rb_KernAux_assert_do(mrb_state *mrb, mrb_value self);

void init_assert(mrb_state *const mrb)
{
    kernaux_assert_cb = assert_cb;

    struct RClass *const rb_KernAux = mrb_define_module(mrb, "KernAux");
    mrb_define_class_method(mrb, rb_KernAux, "assert_cb",
                            rb_KernAux_assert_cb, MRB_ARGS_NONE());
    mrb_define_class_method(mrb, rb_KernAux, "assert_cb=",
                            rb_KernAux_assert_cb_EQ, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, rb_KernAux, "assert_do",
                            rb_KernAux_assert_do, MRB_ARGS_REQ(3));
}

void assert_cb(const char *const file, const int line, const char *const msg)
{
}

mrb_value rb_KernAux_assert_cb(mrb_state *const mrb, const mrb_value self_rb)
{
    return mrb_iv_get(mrb, self_rb, mrb_intern_lit(mrb, "@assert_cb"));
}

mrb_value rb_KernAux_assert_cb_EQ(mrb_state *const mrb, const mrb_value self_rb)
{
    mrb_value assert_cb_rb = mrb_nil_value();
    mrb_get_args(mrb, "o", &assert_cb_rb);
    mrb_iv_set(mrb, self_rb, mrb_intern_lit(mrb, "@assert_cb"), assert_cb_rb);
    return assert_cb_rb;
}

mrb_value rb_KernAux_assert_do(mrb_state *const mrb, const mrb_value self_rb)
{
    const char *file = NULL;
    mrb_int line_rb = 0;
    const char *msg = NULL;
    mrb_get_args(mrb, "ziz", &file, &line_rb, &msg);
    kernaux_assert_do(file, 0, msg);
    return mrb_nil_value();
}
