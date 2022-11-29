#include <kernaux/printf_fmt.h>

#include <assert.h>
#include <stddef.h>

void example_main()
{
    {
        const char *const format = "s";

        struct KernAux_PrintfFmt_Spec spec = KernAux_PrintfFmt_Spec_create(format);

        if (spec.set_width) {
            // Actually this line won't be executed.
            KernAux_PrintfFmt_Spec_set_width(&spec, 0);
        }
        if (spec.set_precision) {
            // Actually this line won't be executed.
            KernAux_PrintfFmt_Spec_set_precision(&spec, 0);
        }

        assert(spec.format_start == format);
        assert(spec.format_limit == &format[1]);

        assert(spec.flags == 0);
        assert(spec.width == 0);
        assert(spec.precision == 0);
        assert(spec.type == KERNAUX_PRINTF_FMT_TYPE_STR);
        assert(spec.base == 0);

        assert(!spec.set_width);
        assert(!spec.set_precision);
    }

    {
        const char *format = "012.34f";

        struct KernAux_PrintfFmt_Spec spec = KernAux_PrintfFmt_Spec_create_out(&format);

        if (spec.set_width) {
            // Actually this line won't be executed.
            KernAux_PrintfFmt_Spec_set_width(&spec, 0);
        }
        if (spec.set_precision) {
            // Actually this line won't be executed.
            KernAux_PrintfFmt_Spec_set_precision(&spec, 0);
        }

        assert(spec.format_start == &format[-7]);
        assert(spec.format_limit == format);

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

        assert(!spec.set_width);
        assert(!spec.set_precision);
    }

    {
        const char *const format = " *.*ld";
        const char *new_format = NULL;

        struct KernAux_PrintfFmt_Spec spec = KernAux_PrintfFmt_Spec_create_out_new(format, &new_format);

        if (spec.set_width) {
            KernAux_PrintfFmt_Spec_set_width(&spec, 12);
        }
        if (spec.set_precision) {
            KernAux_PrintfFmt_Spec_set_precision(&spec, 34);
        }

        assert(spec.format_start == format);
        assert(spec.format_limit == &format[6]);
        assert(new_format == &format[6]);

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

        assert(spec.set_width);
        assert(spec.set_precision);
    }
}
