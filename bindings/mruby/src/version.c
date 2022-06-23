#include "main.h"

#include <mruby/presym.h>
#include <mruby/value.h>

static mrb_value rb_KernAux_Version_with_cmdlineQN(mrb_state *mrb, mrb_value self);
static mrb_value rb_KernAux_Version_with_ntoaQN(mrb_state *mrb, mrb_value self);
static mrb_value rb_KernAux_Version_with_printfQN(mrb_state *mrb, mrb_value self);

void init_version(mrb_state *const mrb)
{
    struct RClass *const rb_KernAux = mrb_module_get_id(mrb, MRB_SYM(KernAux));
    struct RClass *const rb_KernAux_Version =
        mrb_define_module_under_id(mrb, rb_KernAux, MRB_SYM(Version));

    mrb_define_class_method(mrb, rb_KernAux_Version, "with_cmdline?",
                            rb_KernAux_Version_with_cmdlineQN, MRB_ARGS_REQ(0));
    mrb_define_class_method(mrb, rb_KernAux_Version, "with_ntoa?",
                            rb_KernAux_Version_with_ntoaQN, MRB_ARGS_REQ(0));
    mrb_define_class_method(mrb, rb_KernAux_Version, "with_printf?",
                            rb_KernAux_Version_with_printfQN, MRB_ARGS_REQ(0));
}

mrb_value rb_KernAux_Version_with_cmdlineQN(mrb_state *const mrb, const mrb_value self)
{
#ifdef KERNAUX_VERSION_WITH_CMDLINE
    return mrb_true_value();
#else
    return mrb_false_value();
#endif
}

mrb_value rb_KernAux_Version_with_ntoaQN(mrb_state *const mrb, const mrb_value self)
{
#ifdef KERNAUX_VERSION_WITH_NTOA
    return mrb_true_value();
#else
    return mrb_false_value();
#endif
}

mrb_value rb_KernAux_Version_with_printfQN(mrb_state *const mrb, const mrb_value self)
{
#ifdef KERNAUX_VERSION_WITH_PRINTF
    return mrb_true_value();
#else
    return mrb_false_value();
#endif
}
