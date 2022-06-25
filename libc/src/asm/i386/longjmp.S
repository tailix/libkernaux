/**
 * The code was taken from musl libc.
 *
 * Copyright (c) 2011 Rich Felker
 * Copyright (c) 2022 Alexander Monakov
 * Copyright (c) 2022 Alex Kotov
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

.global longjmp
.type longjmp, @function
longjmp:
    mov   4(%esp) , %edx
    mov   8(%esp) , %eax
    cmp     $1    , %eax
    adc     $0    , %al
    mov    (%edx) , %ebx
    mov   4(%edx) , %esi
    mov   8(%edx) , %edi
    mov  12(%edx) , %ebp
    mov  16(%edx) , %esp
    jmp *20(%edx)
