#include "main.h"
#include "dynarg.h"

#include <mruby/array.h>
#include <mruby/error.h>
#include <mruby/presym.h>
#include <mruby/string.h>

#ifdef KERNAUX_VERSION_WITH_PRINTF

void init_printf(mrb_state *const mrb) {}

#endif // KERNAUX_VERSION_WITH_PRINTF
