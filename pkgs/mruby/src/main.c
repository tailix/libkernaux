#include "main.h"

#include <stddef.h>

#include <mruby.h>

// TODO: implement locking
// TODO: turn into stack to support nested callbacks
static mrb_state *current_mrb = NULL;

void mrb_mruby_kernaux_gem_final(mrb_state *const mrb) {}

void mrb_mruby_kernaux_gem_init(mrb_state *const mrb)
{
    init_assert(mrb);
}

void current_mrb_start(mrb_state *mrb)
{
    mrb_assert(current_mrb == NULL);
    mrb_assert(mrb != NULL);

    current_mrb = mrb;
}

void current_mrb_finish(mrb_state *mrb)
{
    mrb_assert(current_mrb != NULL);
    mrb_assert(current_mrb == mrb);

    current_mrb = NULL;
}

mrb_state *current_mrb_get()
{
    mrb_assert(current_mrb != NULL);

    return current_mrb;
}
