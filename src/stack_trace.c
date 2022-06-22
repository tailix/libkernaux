/**
 * The code was inspired by the Limine bootloader.
 *
 * Copyright (c) 2020-2022 mintsuki
 * Copyright (c) 2022      Alex Kotov
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/stack_trace.h>

#include <stddef.h>

void kernaux_stack_trace_snprint(char *const buffer, const size_t buffer_size)
{
    KERNAUX_ASSERT(buffer);
    KERNAUX_ASSERT(buffer_size > 0);

#if !defined(ASM_I386) && !defined(ASM_X86_64)
    (void)buffer_size; // unused
    buffer[0] = '\0'; // empty string
#else
    size_t *ptr = NULL;
    __asm__ volatile(
#if defined(ASM_I386)
        "movl %%ebp, %0"
#elif defined(ASM_X86_64)
        "movq %%rbp, %0"
#endif
        : "=g"(ptr)
        :: "memory"
    );
#endif // !defined(ASM_I386) && !defined(ASM_X86_64)
}
