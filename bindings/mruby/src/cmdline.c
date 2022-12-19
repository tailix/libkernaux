#include "main.h"

#include <mruby/array.h>
#include <mruby/presym.h>
#include <mruby/string.h>

#define ARG_COUNT_MAX 256
#define BUFFER_SIZE 4096

#ifdef KERNAUX_VERSION_WITH_CMDLINE

static mrb_value rb_KernAux_cmdline(mrb_state *mrb, mrb_value self);

void init_cmdline(mrb_state *const mrb)
{
    struct RClass *const rb_KernAux = mrb_module_get_id(mrb, MRB_SYM(KernAux));
    struct RClass *const rb_KernAux_Error =
        mrb_class_get_under_id(mrb, rb_KernAux, MRB_SYM(Error));

    mrb_define_class_under_id(mrb, rb_KernAux, MRB_SYM(CmdlineError),
                              rb_KernAux_Error);

    mrb_define_class_method(mrb, rb_KernAux, "cmdline",
                            rb_KernAux_cmdline, MRB_ARGS_REQ(1));
}

mrb_value rb_KernAux_cmdline(mrb_state *const mrb, mrb_value self)
{
    const char *str;
    mrb_get_args(mrb, "z", &str);
    size_t argc;
    char error_msg[KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX];
    char **const argv = malloc(sizeof(char*) * ARG_COUNT_MAX);
    char *const buffer = malloc(BUFFER_SIZE);

    const bool status = kernaux_cmdline(
        str,
        error_msg,
        &argc,
        argv,
        buffer,
        ARG_COUNT_MAX,
        BUFFER_SIZE
    );

    if (!status) {
        free(argv);
        free(buffer);
        struct RClass *const rb_KernAux =
            mrb_module_get_id(mrb, MRB_SYM(KernAux));
        struct RClass *const rb_KernAux_CmdlineError =
            mrb_class_get_under_id(mrb, rb_KernAux, MRB_SYM(CmdlineError));
        mrb_raise(mrb, rb_KernAux_CmdlineError, error_msg);
    }

    mrb_value values[argc];
    for (size_t index = 0; index < argc; ++index) {
        values[index] = mrb_obj_freeze(
            mrb,
            mrb_str_cat_cstr(mrb, mrb_str_new_lit(mrb, ""), argv[index])
        );
    }
    free(argv);
    free(buffer);
    return mrb_obj_freeze(mrb, mrb_ary_new_from_values(mrb, argc, values));
}

#endif // KERNAUX_VERSION_WITH_CMDLINE
