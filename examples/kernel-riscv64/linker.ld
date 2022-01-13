ENTRY(_start);

. = 0x80000000;

SECTIONS {
    /* Include entry point at start of binary */
    .text : ALIGN(4K) {
        *(.init);
        *(.text);
    }
    .bss : ALIGN(4K) {
        PROVIDE(bss_start = .);
        *(.bss);
        . += 4096;
        PROVIDE(stack_top = .);
        . += 4096;
        PROVIDE(global_pointer = .);
        PROVIDE(bss_end = .);
    }
    .rodata : ALIGN(4K) {
        *(.rodata);
    }
    .data : ALIGN(4K) {
        *(.data);
    }
}
