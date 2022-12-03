#ifndef KERNAUX_INCLUDED_STACK_TRACE
#define KERNAUX_INCLUDED_STACK_TRACE

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct KernAux_StackTrace_Frame {
    const void *KERNAUX_PRIVATE_FIELD(ptr);
} *KernAux_StackTrace_Frame;

struct KernAux_StackTrace_Frame KernAux_StackTrace_Frame_create();

bool KernAux_StackTrace_Frame_has_next(KernAux_StackTrace_Frame frame);
void KernAux_StackTrace_Frame_use_next(KernAux_StackTrace_Frame frame);

const void *KernAux_StackTrace_Frame_get_ptr(KernAux_StackTrace_Frame frame);

#ifdef __cplusplus
}
#endif

#endif
