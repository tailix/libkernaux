#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/arch/i386.h>

#include <assert.h>
#include <string.h>

static void test_idte_set_offset();

void test_main()
{
    test_idte_set_offset();
}

void test_idte_set_offset()
{
    struct KernAux_Arch_I386_IDTE idte;
    memset(&idte, 0, sizeof(idte));

    KernAux_Arch_I386_IDTE_set_offset(&idte, 0);
    assert(idte.offset_high == 0);
    assert(idte.offset_low  == 0);

    KernAux_Arch_I386_IDTE_set_offset(&idte, 0xFFFFFFFF);
    assert(idte.offset_high == 0xFFFF);
    assert(idte.offset_low  == 0xFFFF);

    KernAux_Arch_I386_IDTE_set_offset(&idte, 0x12345678);
    assert(idte.offset_high == 0x1234);
    assert(idte.offset_low  == 0x5678);
}
