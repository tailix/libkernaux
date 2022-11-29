#ifndef INCLUDED_DYNARG
#define INCLUDED_DYNARG

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include <kernaux/macro.h>

#include <kernaux/macro/packing_start.run>

struct DynArg {
    bool use_dbl;
    double dbl;
    // TODO: check if this will work on different endianness.
    union {
        char chr;
        long long ll;
        const char *str;
        unsigned long long ull;
    } KERNAUX_PACKED arg;
}
KERNAUX_PACKED;

#include <kernaux/macro/packing_end.run>

struct DynArg DynArg_create();
void DynArg_init(struct DynArg *dynarg);

void DynArg_use_char(struct DynArg *dynarg, char chr);
void DynArg_use_double(struct DynArg *dynarg, double dbl);
void DynArg_use_long_long(struct DynArg *dynarg, long long ll);
void DynArg_use_str(struct DynArg *dynarg, const char *str);
void DynArg_use_unsigned_long_long(struct DynArg *dynarg, unsigned long long ull);

#ifdef __cplusplus
}
#endif

#endif
