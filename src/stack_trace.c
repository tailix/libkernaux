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
#include <kernaux/stack_trace.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct KernAux_StackTrace_Frame KernAux_StackTrace_Frame_create()
{
    struct KernAux_StackTrace_Frame frame = { .cur_ptr = NULL };

#if defined(ASM_I386)
    const size_t *cur_ptr = frame.cur_ptr;
    KERNAUX_ASM("movl %%ebp, %0" : "=g" (cur_ptr) :: "memory");
#elif defined(ASM_X86_64)
    const size_t *cur_ptr = frame.cur_ptr;
    KERNAUX_ASM("movq %%rbp, %0" : "=g" (cur_ptr) :: "memory");
#endif

    return frame;
}

bool KernAux_StackTrace_Frame_has_next(const KernAux_StackTrace_Frame frame)
{
    KERNAUX_ASSERT(frame);

    if (!frame->cur_ptr) return false;

#if defined(ASM_X86)
    const size_t *const cur_ptr = frame->cur_ptr;
    return cur_ptr[1];
#else
    return false;
#endif
}

void KernAux_StackTrace_Frame_use_next(const KernAux_StackTrace_Frame frame)
{
    KERNAUX_ASSERT(frame);

    if (!frame->cur_ptr) return;

#if defined(ASM_X86)
    const size_t *const cur_ptr = frame->cur_ptr;
    frame->cur_ptr = (const void*)cur_ptr[0];
#endif
}

const void *KernAux_StackTrace_Frame_get_ptr(
    const KernAux_StackTrace_Frame frame
) {
    KERNAUX_ASSERT(frame);

#if defined(ASM_X86)
    const size_t *const cur_ptr = frame->cur_ptr;
    return (const void*)cur_ptr[1];
#else
    return NULL;
#endif
}
