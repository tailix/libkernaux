#include "main.h"

#include <stddef.h>

#include <mruby/presym.h>

#define MRB_STACK_SIZE 100

// TODO: implement locking
// TODO: replace assertions with actual abort
static size_t mrb_stack_count = 0;
static mrb_state *mrb_stack[MRB_STACK_SIZE];

void mrb_mruby_kernaux_gem_final(mrb_state *const mrb) {}

void mrb_mruby_kernaux_gem_init(mrb_state *const mrb)
{
    for (size_t index = mrb_stack_count; index < MRB_STACK_SIZE; ++index) {
        mrb_stack[index] = NULL;
    }

    struct RClass *const rb_KernAux =
        mrb_define_module_id(mrb, MRB_SYM(KernAux));
    mrb_define_class_under_id(mrb, rb_KernAux, MRB_SYM(Error), E_RUNTIME_ERROR);

    init_assert(mrb);
    init_version(mrb);

#ifdef KERNAUX_VERSION_WITH_CMDLINE
    init_cmdline(mrb);
#endif // KERNAUX_VERSION_WITH_CMDLINE
#ifdef KERNAUX_VERSION_WITH_NTOA
    init_ntoa(mrb);
#endif // KERNAUX_VERSION_WITH_NTOA
#ifdef KERNAUX_VERSION_WITH_PRINTF
    init_printf(mrb);
#endif // KERNAUX_VERSION_WITH_PRINTF
}

void current_mrb_start(mrb_state *const mrb)
{
    mrb_assert(mrb_stack_count < MRB_STACK_SIZE - 1);
    mrb_assert(mrb_stack[mrb_stack_count] == NULL);
    mrb_assert(mrb != NULL);

    mrb_stack[mrb_stack_count++] = mrb;
}

void current_mrb_finish(mrb_state *const mrb)
{
    mrb_assert(mrb_stack_count > 0);
    mrb_assert(mrb_stack[mrb_stack_count - 1] != NULL);
    mrb_assert(mrb_stack[mrb_stack_count - 1] == mrb);

    mrb_stack[--mrb_stack_count] = NULL;
}

mrb_state *current_mrb_get()
{
    mrb_assert(mrb_stack_count > 0);
    mrb_assert(mrb_stack[mrb_stack_count - 1] != NULL);

    return mrb_stack[mrb_stack_count - 1];
}
