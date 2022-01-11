#ifndef KERNAUX_INCLUDED_ASM_X86_64
#define KERNAUX_INCLUDED_ASM_X86_64

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/arch/x86_64.h>

void kernaux_asm_x86_64_hang() __attribute__((noreturn));

#ifdef __cplusplus
}
#endif

#endif
