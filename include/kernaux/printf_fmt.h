#ifndef KERNAUX_INCLUDED_PRINTF_FMT
#define KERNAUX_INCLUDED_PRINTF_FMT

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>

#include <stdbool.h>

#define KERNAUX_PRINTF_FMT_FLAGS_ZEROPAD   KERNAUX_BITS(0)
#define KERNAUX_PRINTF_FMT_FLAGS_LEFT      KERNAUX_BITS(1)
#define KERNAUX_PRINTF_FMT_FLAGS_PLUS      KERNAUX_BITS(2)
#define KERNAUX_PRINTF_FMT_FLAGS_SPACE     KERNAUX_BITS(3)
#define KERNAUX_PRINTF_FMT_FLAGS_HASH      KERNAUX_BITS(4)
#define KERNAUX_PRINTF_FMT_FLAGS_UPPERCASE KERNAUX_BITS(5)
#define KERNAUX_PRINTF_FMT_FLAGS_CHAR      KERNAUX_BITS(6)
#define KERNAUX_PRINTF_FMT_FLAGS_SHORT     KERNAUX_BITS(7)
#define KERNAUX_PRINTF_FMT_FLAGS_LONG      KERNAUX_BITS(8)
#define KERNAUX_PRINTF_FMT_FLAGS_LONG_LONG KERNAUX_BITS(9)
#define KERNAUX_PRINTF_FMT_FLAGS_PRECISION KERNAUX_BITS(10)
#define KERNAUX_PRINTF_FMT_FLAGS_ADAPT_EXP KERNAUX_BITS(11)

enum KernAux_PrintfFmt_Type {
    KERNAUX_PRINTF_FMT_TYPE_NONE,
    KERNAUX_PRINTF_FMT_TYPE_INT,
    KERNAUX_PRINTF_FMT_TYPE_UINT,
    KERNAUX_PRINTF_FMT_TYPE_FLOAT,
    KERNAUX_PRINTF_FMT_TYPE_EXP,
    KERNAUX_PRINTF_FMT_TYPE_CHAR,
    KERNAUX_PRINTF_FMT_TYPE_STR,
    KERNAUX_PRINTF_FMT_TYPE_PTR,
    KERNAUX_PRINTF_FMT_TYPE_PERCENT,
};

struct KernAux_PrintfFmt_Spec {
    const char *format_start;
    const char *format_limit;

    unsigned int flags;
    unsigned int width;
    unsigned int precision;
    enum KernAux_PrintfFmt_Type type;
    unsigned int base;

    bool set_width;
    bool set_precision;
};

struct KernAux_PrintfFmt_Spec KernAux_PrintfFmt_Spec_create(
    const char *format
);
struct KernAux_PrintfFmt_Spec KernAux_PrintfFmt_Spec_create_out(
    const char **format
);
struct KernAux_PrintfFmt_Spec KernAux_PrintfFmt_Spec_create_out_new(
    const char *format,
    const char **new_format
);

void KernAux_PrintfFmt_Spec_set_width(
    struct KernAux_PrintfFmt_Spec *spec,
    int width
);
void KernAux_PrintfFmt_Spec_set_precision(
    struct KernAux_PrintfFmt_Spec *spec,
    int precision
);

#ifdef __cplusplus
}
#endif

#endif
