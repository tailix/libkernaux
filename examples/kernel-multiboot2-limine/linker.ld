OUTPUT_ARCH("i386")
ENTRY(_start)

_kernel_offset = 0xC0000000; /* 3 GB */

_kernel_phys_base = 4M;
_kernel_virt_base = (_kernel_phys_base + _kernel_offset);

_kernel_stack_size = _kernel_stack_end - _kernel_stack_start;

SECTIONS
{
    . = _kernel_phys_base;

    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.multiboot)
        *(.text)
    }

    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }

    _kernel_size = . - _kernel_phys_base;
}
