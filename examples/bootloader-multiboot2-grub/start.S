.section .bss

.global _kernel_stack_start
.global _kernel_stack_end

.align 16
_kernel_stack_start:
.skip 16384 # 16 KiB
_kernel_stack_end:



.section .text

.global _start

.type _start,   @function
.type main,     @function
.type poweroff, @function

_start:
    mov $_kernel_stack_end, %esp // Initialize stack

    push %ebx // Multiboot information pointer
    push %eax // Multiboot magic number
    call main

    call poweroff

.size _start, . - _start
