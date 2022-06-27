#include "main.h"

#ifdef KERNAUX_VERSION_WITH_CMDLINE

#define ARG_COUNT_MAX 256
#define BUFFER_SIZE 4096

struct Data {
    char error_msg[KERNAUX_CMDLINE_ERROR_MSG_SIZE_MAX];
    char *argv[ARG_COUNT_MAX];
    char buffer[BUFFER_SIZE];
};

static VALUE rb_ANON_Data_ALLOC(VALUE klass);
static VALUE rb_KernAux_cmdline(VALUE self, VALUE cmdline);

static const struct rb_data_type_struct info = {
    .wrap_struct_name = "cmdline",
    .function = {
        .dmark = NULL,
        .dfree = RUBY_DEFAULT_FREE,
        .dsize = NULL,
        .dcompact = NULL,
        .reserved = { 0 },
    },
    .parent = NULL,
    .data = NULL,
    .flags = RUBY_TYPED_FREE_IMMEDIATELY,
};

static VALUE rb_KernAux_CmdlineError = Qnil;
static VALUE rb_ANON_Data = Qnil;

void init_cmdline()
{
    rb_gc_register_mark_object(rb_KernAux_CmdlineError =
        rb_define_class_under(rb_KernAux, "CmdlineError", rb_KernAux_Error));
    rb_gc_register_mark_object(rb_ANON_Data =
        rb_funcall(rb_cClass, rb_intern_new, 1, rb_cObject));

    rb_define_alloc_func(rb_ANON_Data, rb_ANON_Data_ALLOC);
    rb_define_singleton_method(rb_KernAux, "cmdline", rb_KernAux_cmdline, 1);
}

VALUE rb_ANON_Data_ALLOC(const VALUE klass)
{
    struct Data *data;
    return TypedData_Make_Struct(klass, struct Data, &info, data);
}

VALUE rb_KernAux_cmdline(const VALUE self_rb, VALUE cmdline_rb)
{
    const char *const cmdline = StringValueCStr(cmdline_rb);
    size_t argc;

    const VALUE data_rb = rb_funcall(rb_ANON_Data, rb_intern_new, 0);
    struct Data *data;
    TypedData_Get_Struct(data_rb, struct Data, &info, data);
    if (!data) rb_raise(rb_KernAux_CmdlineError, "internal error");

    const bool result = kernaux_cmdline(
        cmdline,
        data->error_msg,
        &argc,
        data->argv,
        data->buffer,
        ARG_COUNT_MAX,
        BUFFER_SIZE
    );

    if (!result) rb_raise(rb_KernAux_CmdlineError, "%s", data->error_msg);

    VALUE result_rb = rb_ary_new2(argc);
    for (size_t index = 0; index < argc; ++index) {
        rb_ary_push(
            result_rb,
            rb_funcall(rb_str_new2(data->argv[index]), rb_intern_freeze, 0)
        );
    }
    return rb_funcall(result_rb, rb_intern_freeze, 0);
}

#endif // KERNAUX_VERSION_WITH_CMDLINE
