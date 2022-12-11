#ifndef KERNAUX_INCLUDED_ARCH_X86_64
#define KERNAUX_INCLUDED_ARCH_X86_64

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/arch/x86.h>

/**
 * @brief CR0 bits
 *
 * @details
 * Contains system control flags that control
 * operating mode and states of the processor.
 *
 * @see https://en.wikipedia.org/wiki/Control_register#CR0
 * @see https://wiki.osdev.org/CPU_Registers_x86#CR0
 */
KERNAUX_ARCH_X86_DEFINE_CR0(X86_64, uint64_t);
KERNAUX_STATIC_TEST_UNION_SIZE(KernAux_Arch_X86_64_CR0, 8);

/**
 * @brief CR4 bits
 *
 * @details
 * Contains a group of flags that enable several architectural extensions,
 * and indicate operating system or executive support for specific processor
 * capabilities.
 *
 * @see https://en.wikipedia.org/wiki/Control_register#CR4
 * @see https://wiki.osdev.org/CPU_Registers_x86#CR4
 */
KERNAUX_ARCH_X86_DEFINE_CR4(X86_64, uint64_t);
KERNAUX_STATIC_TEST_UNION_SIZE(KernAux_Arch_X86_64_CR4, 8);

#ifdef __cplusplus
}
#endif

#endif
