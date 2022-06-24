#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

.global kernaux_asm_i386_flush_idt
.global kernaux_asm_i386_read_cr0
.global kernaux_asm_i386_read_cr4
.global kernaux_asm_i386_write_cr0
.global kernaux_asm_i386_write_cr3
.global kernaux_asm_i386_write_cr4

kernaux_asm_i386_flush_idt:
    mov 4(%esp), %eax
    lidt (%eax)
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
