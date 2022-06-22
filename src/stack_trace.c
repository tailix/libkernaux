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
#include <kernaux/printf.h>
#include <kernaux/stack_trace.h>

#include <stddef.h>

static const char *trace(size_t *offset, size_t ret_addr);

void kernaux_stack_trace_snprint(char *buffer, size_t buffer_size)
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

    for (;;) {
        size_t old_bp   = ptr[0];
        size_t ret_addr = ptr[1];
        if (!ret_addr) break;

        size_t offset = 0;
        const char *const name = trace(&offset, ret_addr);
        int snprintf_result;
        if (name) {
            snprintf_result = kernaux_snprintf(
                buffer,
                buffer_size,
                "[%p] <%s + %p>\n",
                ret_addr,
                name,
                offset
            );
        } else {
            snprintf_result = kernaux_snprintf(
                buffer,
                buffer_size,
                "[%p]\n",
                ret_addr
            );
        }
        if (snprintf_result > 0 && (size_t)snprintf_result < buffer_size) {
            buffer_size -= snprintf_result;
            buffer += snprintf_result;
        }

        if (!old_bp) break;
        ptr = (void*)old_bp;
    }
#endif // !defined(ASM_I386) && !defined(ASM_X86_64)
}

static const char *trace(size_t *const offset, const size_t ret_addr)
{
    *offset = 0;
    (void)ret_addr;
    return NULL;
}
