#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

.global kernaux_asm_x86_64_hang

kernaux_asm_x86_64_hang:
    cli
    hlt
    jmp kernaux_asm_x86_64_hang
