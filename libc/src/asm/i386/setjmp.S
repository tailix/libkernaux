/**
 * The code was taken from musl libc.
 *
 * Copyright (c) 2011-2015 Rich Felker
 * Copyright (c) 2022      Alex Kotov
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

.global setjmp
.type setjmp, @function
setjmp:
    mov 4(%esp) ,    %eax
    mov   %ebx  ,   (%eax)
    mov   %esi  ,  4(%eax)
    mov   %edi  ,  8(%eax)
    mov   %ebp  , 12(%eax)
    lea 4(%esp) ,    %ecx
    mov   %ecx  , 16(%eax)
    mov  (%esp) ,    %ecx
    mov   %ecx  , 20(%eax)
    xor   %eax  ,    %eax
    ret
