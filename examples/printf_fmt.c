#include <kernaux/printf_fmt.h>

#include <assert.h>

int main()
{
    {
        const char *format = "012.34f";

        struct KernAux_PrintfFmt_Spec spec = KernAux_PrintfFmt_Spec_create();
        KernAux_PrintfFmt_Spec_eval_flags(&spec, &format);
        if (KernAux_PrintfFmt_Spec_eval_width1(&spec, &format)) {
            KernAux_PrintfFmt_Spec_eval_width2(&spec, 0);
        }
        if (KernAux_PrintfFmt_Spec_eval_precision1(&spec, &format)) {
            KernAux_PrintfFmt_Spec_eval_precision2(&spec, 0);
        }
        KernAux_PrintfFmt_Spec_eval_length(&spec, &format);
        KernAux_PrintfFmt_Spec_eval_type(&spec, &format);

        assert(
            spec.flags ==
            (
                KERNAUX_PRINTF_FMT_FLAGS_ZEROPAD |
                KERNAUX_PRINTF_FMT_FLAGS_PRECISION
            )
        );
        assert(spec.width == 12);
        assert(spec.precision == 34);
        assert(spec.type == KERNAUX_PRINTF_FMT_TYPE_FLOAT);
        assert(spec.base == 0);
    }

    {
        const char *format = " *.*ld";

        struct KernAux_PrintfFmt_Spec spec = KernAux_PrintfFmt_Spec_create();
        KernAux_PrintfFmt_Spec_eval_flags(&spec, &format);
        if (KernAux_PrintfFmt_Spec_eval_width1(&spec, &format)) {
            KernAux_PrintfFmt_Spec_eval_width2(&spec, 12);
        }
        if (KernAux_PrintfFmt_Spec_eval_precision1(&spec, &format)) {
            KernAux_PrintfFmt_Spec_eval_precision2(&spec, 34);
        }
        KernAux_PrintfFmt_Spec_eval_length(&spec, &format);
        KernAux_PrintfFmt_Spec_eval_type(&spec, &format);

        assert(
            spec.flags ==
            (
                KERNAUX_PRINTF_FMT_FLAGS_SPACE |
                KERNAUX_PRINTF_FMT_FLAGS_LONG |
                KERNAUX_PRINTF_FMT_FLAGS_PRECISION
            )
        );
        assert(spec.width == 12);
        assert(spec.precision == 34);
        assert(spec.type == KERNAUX_PRINTF_FMT_TYPE_INT);
        assert(spec.base == 10);
    }

    return 0;
}
