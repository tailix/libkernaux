#include "dynarg.h"

struct DynArg DynArg_create()
{
    struct DynArg dynarg;
    DynArg_init(&dynarg);
    return dynarg;
}

void DynArg_init(struct DynArg *const dynarg)
{
    dynarg->use_dbl = false;
    dynarg->dbl = 0.0;
    dynarg->arg.str = "";
}

void DynArg_use_char(struct DynArg *const dynarg, const char chr)
{
    dynarg->use_dbl = false;
    dynarg->arg.chr = chr;
}

void DynArg_use_double(struct DynArg *const dynarg, const double dbl)
{
    dynarg->use_dbl = true;
    dynarg->dbl = dbl;
}

void DynArg_use_long_long(struct DynArg *const dynarg, const long long ll)
{
    dynarg->use_dbl = false;
    dynarg->arg.ll = ll;
}

void DynArg_use_str(struct DynArg *const dynarg, const char *const str)
{
    dynarg->use_dbl = false;
    dynarg->arg.str = str;
}

void DynArg_use_unsigned_long_long(struct DynArg *const dynarg, const unsigned long long ull)
{
    dynarg->use_dbl = false;
    dynarg->arg.ull = ull;
}
