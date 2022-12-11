#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/arch/i386.h>

#include <assert.h>
#include <string.h>

static void test_idte_init_intr();
static void test_idte_init_task();
static void test_idte_init_trap();
static void test_idte_get_and_set_offset();
static void test_idte_get_dpl();

void test_main()
{
    test_idte_init_intr();
    test_idte_init_task();
    test_idte_init_trap();
    test_idte_get_and_set_offset();
    test_idte_get_dpl();
}

void test_idte_init_intr()
{
    struct KernAux_Arch_I386_IDTE idte;
    memset(&idte, 0xff, sizeof(idte));

    KernAux_Arch_I386_IDTE_init_intr(&idte, 0x12345678, 0xcafe, 0);
    assert(KernAux_Arch_I386_IDTE_offset(&idte) == 0x12345678);
    assert(KernAux_Arch_I386_IDTE_dpl(&idte) == 0);
    assert(idte.selector == 0xcafe);
    assert(idte._ == 0);
    assert(idte.flags == 0x8e); // 1-00-01110

    KernAux_Arch_I386_IDTE_init_intr(&idte, 0x12345678, 0xcafe, 3);
    assert(KernAux_Arch_I386_IDTE_offset(&idte) == 0x12345678);
    assert(KernAux_Arch_I386_IDTE_dpl(&idte) == 3);
    assert(idte.selector == 0xcafe);
    assert(idte._ == 0);
    assert(idte.flags == 0xee); // 1-11-01110
}

void test_idte_init_task()
{
    struct KernAux_Arch_I386_IDTE idte;
    memset(&idte, 0xff, sizeof(idte));

    KernAux_Arch_I386_IDTE_init_task(&idte, 0xcafe, 0);
    assert(KernAux_Arch_I386_IDTE_offset(&idte) == 0);
    assert(KernAux_Arch_I386_IDTE_dpl(&idte) == 0);
    assert(idte.selector == 0xcafe);
    assert(idte._ == 0);
    assert(idte.flags == 0x85); // 1-00-00101

    KernAux_Arch_I386_IDTE_init_task(&idte, 0xcafe, 3);
    assert(KernAux_Arch_I386_IDTE_offset(&idte) == 0);
    assert(KernAux_Arch_I386_IDTE_dpl(&idte) == 3);
    assert(idte.selector == 0xcafe);
    assert(idte._ == 0);
    assert(idte.flags == 0xe5); // 1-11-00101
}

void test_idte_init_trap()
{
    struct KernAux_Arch_I386_IDTE idte;
    memset(&idte, 0xff, sizeof(idte));

    KernAux_Arch_I386_IDTE_init_trap(&idte, 0x12345678, 0xcafe, 0);
    assert(KernAux_Arch_I386_IDTE_offset(&idte) == 0x12345678);
    assert(KernAux_Arch_I386_IDTE_dpl(&idte) == 0);
    assert(idte.selector == 0xcafe);
    assert(idte._ == 0);
    assert(idte.flags == 0x8f); // 1-00-01111

    KernAux_Arch_I386_IDTE_init_trap(&idte, 0x12345678, 0xcafe, 3);
    assert(KernAux_Arch_I386_IDTE_offset(&idte) == 0x12345678);
    assert(KernAux_Arch_I386_IDTE_dpl(&idte) == 3);
    assert(idte.selector == 0xcafe);
    assert(idte._ == 0);
    assert(idte.flags == 0xef); // 1-11-01111
}

void test_idte_get_and_set_offset()
{
    struct KernAux_Arch_I386_IDTE idte;

    memset(&idte, 0xff, sizeof(idte));
    KernAux_Arch_I386_IDTE_set_offset(&idte, 0);
    assert(idte.offset_high == 0);
    assert(idte.offset_low  == 0);
    assert(KernAux_Arch_I386_IDTE_offset(&idte) == 0);

    memset(&idte, 0, sizeof(idte));
    KernAux_Arch_I386_IDTE_set_offset(&idte, 0xffffffff);
    assert(idte.offset_high == 0xffff);
    assert(idte.offset_low  == 0xffff);
    assert(KernAux_Arch_I386_IDTE_offset(&idte) == 0xffffffff);

    memset(&idte, 0, sizeof(idte));
    KernAux_Arch_I386_IDTE_set_offset(&idte, 0x12345678);
    assert(idte.offset_high == 0x1234);
    assert(idte.offset_low  == 0x5678);
    assert(KernAux_Arch_I386_IDTE_offset(&idte) == 0x12345678);
}

void test_idte_get_dpl()
{
    struct KernAux_Arch_I386_IDTE idte;
    memset(&idte, 0, sizeof(idte));

    idte.flags = 0; // 0-00-00000
    assert(KernAux_Arch_I386_IDTE_dpl(&idte) == 0);
    idte.flags = 0x80; // 1-00-00000
    assert(KernAux_Arch_I386_IDTE_dpl(&idte) == 0);

    idte.flags = 0x20; // 0-01-00000
    assert(KernAux_Arch_I386_IDTE_dpl(&idte) == 1);
    idte.flags = 0xa0; // 1-01-00000
    assert(KernAux_Arch_I386_IDTE_dpl(&idte) == 1);

    idte.flags = 0x40; // 0-10-00000
    assert(KernAux_Arch_I386_IDTE_dpl(&idte) == 2);
    idte.flags = 0xc0; // 1-10-00000
    assert(KernAux_Arch_I386_IDTE_dpl(&idte) == 2);

    idte.flags = 0x60; // 0-11-00000
    assert(KernAux_Arch_I386_IDTE_dpl(&idte) == 3);
    idte.flags = 0xe0; // 1-11-00000
    assert(KernAux_Arch_I386_IDTE_dpl(&idte) == 3);
}
