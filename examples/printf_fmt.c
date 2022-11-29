#include <kernaux/printf_fmt.h>

#include <assert.h>

void example_main()
{
    {
        const char *format = "s";

        struct KernAux_PrintfFmt_Spec spec = KernAux_PrintfFmt_Spec_create();

        format = KernAux_PrintfFmt_Spec_parse(&spec, format);

        if (spec.set_width) {
            // Actually this line won't be executed.
            KernAux_PrintfFmt_Spec_set_width(&spec, 0);
        }
        if (spec.set_precision) {
            // Actually this line won't be executed.
            KernAux_PrintfFmt_Spec_set_precision(&spec, 0);
        }

        assert(spec.flags == 0);
        assert(spec.width == 0);
        assert(spec.precision == 0);
        assert(spec.type == KERNAUX_PRINTF_FMT_TYPE_STR);
        assert(spec.base == 0);
    }

    {
        const char *format = "012.34f";

        struct KernAux_PrintfFmt_Spec spec = KernAux_PrintfFmt_Spec_create();

        format = KernAux_PrintfFmt_Spec_parse(&spec, format);

        if (spec.set_width) {
            // Actually this line won't be executed.
            KernAux_PrintfFmt_Spec_set_width(&spec, 0);
        }
        if (spec.set_precision) {
            // Actually this line won't be executed.
            KernAux_PrintfFmt_Spec_set_precision(&spec, 0);
        }

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
        const char *const format = " *.*ld";

        struct KernAux_PrintfFmt_Spec spec = KernAux_PrintfFmt_Spec_create();

        // Returning value may be ignored.
        KernAux_PrintfFmt_Spec_parse(&spec, format);

        if (spec.set_width) {
            KernAux_PrintfFmt_Spec_set_width(&spec, 12);
        }
        if (spec.set_precision) {
            KernAux_PrintfFmt_Spec_set_precision(&spec, 34);
        }

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
}
