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
#include <kernaux/macro.h>
#include <kernaux/printf.h>
#include <kernaux/stack_trace.h>

#include <stddef.h>

void kernaux_stack_trace_snprint(char *buffer, size_t buffer_size)
{
    KERNAUX_ASSERT(buffer);
    KERNAUX_ASSERT(buffer_size > 0);

#ifndef ASM_X86
    (void)buffer_size; // unused
    buffer[0] = '\0'; // empty string
#else
    size_t *ptr = NULL;
#if defined(ASM_I386)
    KERNAUX_ASM("movl %%ebp, %0" : "=g"(ptr) :: "memory");
#elif defined(ASM_X86_64)
    KERNAUX_ASM("movq %%rbp, %0" : "=g"(ptr) :: "memory");
#endif

    for (size_t index = 0;; ++index) {
        size_t old_bp   = ptr[0];
        size_t ret_addr = ptr[1];
        if (!ret_addr) break;

        int snprintf_result = kernaux_snprintf(
            buffer,
            buffer_size,
            "%lu: 0x%p\n",
            index,
            ret_addr
        );

        if (snprintf_result > 0 && (size_t)snprintf_result < buffer_size) {
            buffer_size -= snprintf_result;
            buffer += snprintf_result;
        }

        if (!old_bp) break;
        ptr = (void*)old_bp;
    }
#endif // ASM_X86
}
