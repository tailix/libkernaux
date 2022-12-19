#include "main.h"

#include <mruby/numeric.h>
#include <mruby/presym.h>
#include <mruby/string.h>

#ifdef KERNAUX_VERSION_WITH_NTOA

static mrb_value rb_KernAux_utoa(mrb_state *mrb, mrb_value self);
static mrb_value rb_KernAux_itoa(mrb_state *mrb, mrb_value self);

static mrb_value rb_KernAux_utoa2(mrb_state *mrb, mrb_value self);
static mrb_value rb_KernAux_itoa2(mrb_state *mrb, mrb_value self);

static mrb_value rb_KernAux_utoa8(mrb_state *mrb, mrb_value self);
static mrb_value rb_KernAux_itoa8(mrb_state *mrb, mrb_value self);

static mrb_value rb_KernAux_utoa10(mrb_state *mrb, mrb_value self);
static mrb_value rb_KernAux_itoa10(mrb_state *mrb, mrb_value self);

static mrb_value rb_KernAux_utoa16(mrb_state *mrb, mrb_value self);
static mrb_value rb_KernAux_itoa16(mrb_state *mrb, mrb_value self);

static int convert_base(mrb_state *mrb, mrb_value base);

void init_ntoa(mrb_state *const mrb)
{
    struct RClass *const rb_KernAux = mrb_module_get_id(mrb, MRB_SYM(KernAux));
    struct RClass *const rb_KernAux_Error =
        mrb_class_get_under_id(mrb, rb_KernAux, MRB_SYM(Error));

    mrb_define_class_under_id(mrb, rb_KernAux, MRB_SYM(InvalidNtoaBaseError),
                              rb_KernAux_Error);
    mrb_define_class_under_id(mrb, rb_KernAux, MRB_SYM(TooLongNtoaPrefixError),
                              rb_KernAux_Error);

    mrb_define_class_method(mrb, rb_KernAux, "utoa",
                            rb_KernAux_utoa, MRB_ARGS_REQ(2) | MRB_ARGS_OPT(1));
    mrb_define_class_method(mrb, rb_KernAux, "itoa",
                            rb_KernAux_itoa, MRB_ARGS_REQ(2) | MRB_ARGS_OPT(1));

    mrb_define_class_method(mrb, rb_KernAux, "utoa2",
                            rb_KernAux_utoa2, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, rb_KernAux, "itoa2",
                            rb_KernAux_itoa2, MRB_ARGS_REQ(1));

    mrb_define_class_method(mrb, rb_KernAux, "utoa8",
                            rb_KernAux_utoa8, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, rb_KernAux, "itoa8",
                            rb_KernAux_itoa8, MRB_ARGS_REQ(1));

    mrb_define_class_method(mrb, rb_KernAux, "utoa10",
                            rb_KernAux_utoa10, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, rb_KernAux, "itoa10",
                            rb_KernAux_itoa10, MRB_ARGS_REQ(1));

    mrb_define_class_method(mrb, rb_KernAux, "utoa16",
                            rb_KernAux_utoa16, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, rb_KernAux, "itoa16",
                            rb_KernAux_itoa16, MRB_ARGS_REQ(1));
}

mrb_value rb_KernAux_utoa(mrb_state *mrb, mrb_value self)
{
    mrb_int value = 0;
    mrb_value base;
    const char *prefix = NULL;
    mrb_int prefix_len = 0;
    mrb_get_args(mrb, "io|s!", &value, &base, &prefix, &prefix_len);

    if (value < 0) {
        mrb_raise(mrb, E_RANGE_ERROR,
                  "can't convert negative number to uint64_t");
    }
    if (prefix_len > KERNAUX_NTOA_MAX_PREFIX_LEN || prefix_len < 0) {
        struct RClass *const rb_KernAux =
            mrb_module_get_id(mrb, MRB_SYM(KernAux));
        struct RClass *const rb_KernAux_TooLongNtoaPrefixError =
            mrb_class_get_under_id(
                mrb,
                rb_KernAux,
                MRB_SYM(TooLongNtoaPrefixError)
            );
        mrb_raisef(mrb, rb_KernAux_TooLongNtoaPrefixError,
                   "prefix length %d is too long", prefix_len);
    }

    char buffer[KERNAUX_UTOA_MIN_BUFFER_SIZE + prefix_len];
    current_mrb_start(mrb);
    kernaux_utoa(value, buffer, convert_base(mrb, base), prefix);
    current_mrb_finish(mrb);

    mrb_value result = mrb_str_new_lit(mrb, "");
    result = mrb_str_cat_cstr(mrb, result, buffer);
    return mrb_obj_freeze(mrb, result);
}

mrb_value rb_KernAux_itoa(mrb_state *mrb, mrb_value self)
{
    mrb_int value = 0;
    mrb_value base;
    const char *prefix = NULL;
    mrb_int prefix_len = 0;
    mrb_get_args(mrb, "io|s!", &value, &base, &prefix, &prefix_len);

    if (prefix_len > KERNAUX_NTOA_MAX_PREFIX_LEN || prefix_len < 0) {
        struct RClass *const rb_KernAux =
            mrb_module_get_id(mrb, MRB_SYM(KernAux));
        struct RClass *const rb_KernAux_TooLongNtoaPrefixError =
            mrb_class_get_under_id(
                mrb,
                rb_KernAux,
                MRB_SYM(TooLongNtoaPrefixError)
            );
        mrb_raisef(mrb, rb_KernAux_TooLongNtoaPrefixError,
                   "prefix length %d is too long", prefix_len);
    }

    char buffer[KERNAUX_ITOA_MIN_BUFFER_SIZE + prefix_len];
    current_mrb_start(mrb);
    kernaux_itoa(value, buffer, convert_base(mrb, base), prefix);
    current_mrb_finish(mrb);

    mrb_value result = mrb_str_new_lit(mrb, "");
    result = mrb_str_cat_cstr(mrb, result, buffer);
    return mrb_obj_freeze(mrb, result);
}

mrb_value rb_KernAux_utoa2(mrb_state *mrb, mrb_value self)
{
    mrb_int value = 0;
    mrb_get_args(mrb, "i", &value);

    if (value < 0) {
        mrb_raise(mrb, E_RANGE_ERROR,
                  "can't convert negative number to uint64_t");
    }

    char buffer[KERNAUX_UTOA2_BUFFER_SIZE];
    current_mrb_start(mrb);
    kernaux_utoa2(value, buffer);
    current_mrb_finish(mrb);

    mrb_value result = mrb_str_new_lit(mrb, "");
    result = mrb_str_cat_cstr(mrb, result, buffer);
    return mrb_obj_freeze(mrb, result);
}

mrb_value rb_KernAux_itoa2(mrb_state *mrb, mrb_value self)
{
    mrb_int value = 0;
    mrb_get_args(mrb, "i", &value);

    char buffer[KERNAUX_ITOA2_BUFFER_SIZE];
    current_mrb_start(mrb);
    kernaux_itoa2(value, buffer);
    current_mrb_finish(mrb);

    mrb_value result = mrb_str_new_lit(mrb, "");
    result = mrb_str_cat_cstr(mrb, result, buffer);
    return mrb_obj_freeze(mrb, result);
}

mrb_value rb_KernAux_utoa8(mrb_state *mrb, mrb_value self)
{
    mrb_int value = 0;
    mrb_get_args(mrb, "i", &value);

    if (value < 0) {
        mrb_raise(mrb, E_RANGE_ERROR,
                  "can't convert negative number to uint64_t");
    }

    char buffer[KERNAUX_UTOA8_BUFFER_SIZE];
    current_mrb_start(mrb);
    kernaux_utoa8(value, buffer);
    current_mrb_finish(mrb);

    mrb_value result = mrb_str_new_lit(mrb, "");
    result = mrb_str_cat_cstr(mrb, result, buffer);
    return mrb_obj_freeze(mrb, result);
}

mrb_value rb_KernAux_itoa8(mrb_state *mrb, mrb_value self)
{
    mrb_int value = 0;
    mrb_get_args(mrb, "i", &value);

    char buffer[KERNAUX_ITOA8_BUFFER_SIZE];
    current_mrb_start(mrb);
    kernaux_itoa8(value, buffer);
    current_mrb_finish(mrb);

    mrb_value result = mrb_str_new_lit(mrb, "");
    result = mrb_str_cat_cstr(mrb, result, buffer);
    return mrb_obj_freeze(mrb, result);
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
    return mrb_obj_freeze(mrb, result);
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
    return mrb_obj_freeze(mrb, result);
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
    return mrb_obj_freeze(mrb, result);
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
    return mrb_obj_freeze(mrb, result);
}

int convert_base(mrb_state *mrb, mrb_value base_rb)
{
    if (mrb_obj_is_kind_of(mrb, base_rb, mrb->symbol_class)) {
        mrb_sym base_sym = mrb_obj_to_sym(mrb, base_rb);
        switch (base_sym) {
        case MRB_SYM(b): return 'b';
        case MRB_SYM(B): return 'B';
        case MRB_SYM(h): return 'h';
        case MRB_SYM(H): return 'H';
        case MRB_SYM(o): return 'o';
        case MRB_SYM(O): return 'O';
        case MRB_SYM(d): return 'd';
        case MRB_SYM(D): return 'D';
        case MRB_SYM(x): return 'x';
        case MRB_SYM(X): return 'X';
        default:
        {
            struct RClass *const rb_KernAux =
                mrb_module_get_id(mrb, MRB_SYM(KernAux));
            struct RClass *const rb_KernAux_Error =
                mrb_class_get_under_id(mrb, rb_KernAux, MRB_SYM(Error));
            mrb_raise(mrb, rb_KernAux_Error, "invalid base");
        }
        }
    } else {
        return mrb_integer(base_rb);
    }
}

#endif // KERNAUX_VERSION_WITH_NTOA
