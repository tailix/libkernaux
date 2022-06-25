/**
 * The code was taken from musl libc.
 *
 * Copyright (c) 2011      Nicholas J. Kain
 * Copyright (c) 2011-2012 Rich Felker
 * Copyright (c) 2022      Alexander Monakov
 * Copyright (c) 2022      Alex Kotov
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

.global longjmp
.type longjmp, @function
longjmp:
    xor     %eax  , %eax
    cmp     $1    , %esi /* CF = val ? 0 : 1 */
    adc     %esi  , %eax /* eax = val + !val */
    mov    (%rdi) , %rbx /* rdi is the jmp_buf, restore regs from it */
    mov   8(%rdi) , %rbp
    mov  16(%rdi) , %r12
    mov  24(%rdi) , %r13
    mov  32(%rdi) , %r14
    mov  40(%rdi) , %r15
    mov  48(%rdi) , %rsp
    jmp *56(%rdi)        /* goto saved address without altering rsp */
