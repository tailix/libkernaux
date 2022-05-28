#include <kernaux/printf_fmt.h>

#include <assert.h>

int main()
{
    {
        const char *format = "s";

        struct KernAux_PrintfFmt_Spec spec = KernAux_PrintfFmt_Spec_create();
        KernAux_PrintfFmt_Spec_parse_flags(&spec, &format);
        if (KernAux_PrintfFmt_Spec_parse_width(&spec, &format)) {
            // Actually this line won't be executed.
            KernAux_PrintfFmt_Spec_set_width(&spec, 0);
        }
        if (KernAux_PrintfFmt_Spec_parse_precision(&spec, &format)) {
            // Actually this line won't be executed.
            KernAux_PrintfFmt_Spec_set_precision(&spec, 0);
        }
        KernAux_PrintfFmt_Spec_parse_length(&spec, &format);
        KernAux_PrintfFmt_Spec_parse_type(&spec, &format);

        assert(spec.flags == 0);
        assert(spec.width == 0);
        assert(spec.precision == 0);
        assert(spec.type == KERNAUX_PRINTF_FMT_TYPE_STR);
        assert(spec.base == 0);
    }

    {
        const char *format = "012.34f";

        struct KernAux_PrintfFmt_Spec spec = KernAux_PrintfFmt_Spec_create();
        KernAux_PrintfFmt_Spec_parse_flags(&spec, &format);
        if (KernAux_PrintfFmt_Spec_parse_width(&spec, &format)) {
            // Actually this line won't be executed.
            KernAux_PrintfFmt_Spec_set_width(&spec, 0);
        }
        if (KernAux_PrintfFmt_Spec_parse_precision(&spec, &format)) {
            // Actually this line won't be executed.
            KernAux_PrintfFmt_Spec_set_precision(&spec, 0);
        }
        KernAux_PrintfFmt_Spec_parse_length(&spec, &format);
        KernAux_PrintfFmt_Spec_parse_type(&spec, &format);

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
        KernAux_PrintfFmt_Spec_parse_flags(&spec, &format);
        if (KernAux_PrintfFmt_Spec_parse_width(&spec, &format)) {
            KernAux_PrintfFmt_Spec_set_width(&spec, 12);
        }
        if (KernAux_PrintfFmt_Spec_parse_precision(&spec, &format)) {
            KernAux_PrintfFmt_Spec_set_precision(&spec, 34);
        }
        KernAux_PrintfFmt_Spec_parse_length(&spec, &format);
        KernAux_PrintfFmt_Spec_parse_type(&spec, &format);

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
