#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

.global kernaux_asm_i386_flush_gdt
.global kernaux_asm_i386_flush_idt
.global kernaux_asm_i386_flush_tss
.global kernaux_asm_i386_read_cr0
.global kernaux_asm_i386_read_cr4
.global kernaux_asm_i386_write_cr0
.global kernaux_asm_i386_write_cr3
.global kernaux_asm_i386_write_cr4

kernaux_asm_i386_flush_gdt:
    mov 4(%esp), %eax
    mov 8(%esp), %edx
    lgdt (%eax)
    mov %edx, %ds
    mov %edx, %es
    mov %edx, %fs
    mov %edx, %gs
    mov %edx, %ss
    pushl 12(%esp)
    push $.flush
    ljmp *(%esp)
  .flush:
    ret

kernaux_asm_i386_flush_idt:
    mov 4(%esp), %eax
    lidt (%eax)
    ret

kernaux_asm_i386_flush_tss:
    mov 4(%esp), %ax
    ltr %ax
    ret

kernaux_asm_i386_read_cr0:
    mov %cr0, %eax
    ret

kernaux_asm_i386_read_cr4:
    mov %cr4, %eax
    ret

kernaux_asm_i386_write_cr0:
    mov 4(%esp), %eax
    mov %eax, %cr0
    ret

kernaux_asm_i386_write_cr3:
    mov 4(%esp), %eax
    mov %eax, %cr3
    ret

kernaux_asm_i386_write_cr4:
    mov 4(%esp), %eax
    mov %eax, %cr4
    ret
