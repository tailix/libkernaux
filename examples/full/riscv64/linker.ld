ENTRY(_start);

SECTIONS
{
    . = 0x80000000;

    .text : ALIGN(4K)
    {
        *(.init);
        *(.text);
    }

    .rodata : ALIGN(4K)
    {
        *(.rodata);
    }

    .data : ALIGN(4K)
    {
        *(.data);
    }

    .bss : ALIGN(4K)
    {
        PROVIDE(bss_start = .);
        *(.bss);
        . += 4096;
        PROVIDE(stack_top = .);
        . += 4096;
        PROVIDE(global_pointer = .);
        PROVIDE(bss_end = .);
    }
}
