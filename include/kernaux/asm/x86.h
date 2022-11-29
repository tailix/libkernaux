#ifndef KERNAUX_INCLUDED_ASM_X86
#define KERNAUX_INCLUDED_ASM_X86

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/arch/x86.h>
#include <kernaux/macro.h>

#include <stdint.h>

inline static uint8_t  kernaux_asm_x86_inportb(uint16_t port);
inline static uint16_t kernaux_asm_x86_inportw(uint16_t port);
inline static uint32_t kernaux_asm_x86_inportd(uint16_t port);

inline static void kernaux_asm_x86_outportb(uint16_t port, uint8_t  value);
inline static void kernaux_asm_x86_outportw(uint16_t port, uint16_t value);
inline static void kernaux_asm_x86_outportd(uint16_t port, uint32_t value);

uint8_t kernaux_asm_x86_inportb(const uint16_t port)
{
    register uint8_t result;
    KERNAUX_ASM("inb %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

uint16_t kernaux_asm_x86_inportw(const uint16_t port)
{
    register uint16_t result;
    KERNAUX_ASM("inw %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

uint32_t kernaux_asm_x86_inportd(const uint16_t port)
{
    register uint32_t result;
    KERNAUX_ASM("inl %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

void kernaux_asm_x86_outportb(const uint16_t port, const uint8_t value)
{
    KERNAUX_ASM("outb %1, %0" : : "dN" (port), "a" (value));
}

void kernaux_asm_x86_outportw(const uint16_t port, const uint16_t value)
{
    KERNAUX_ASM("outw %1, %0" : : "dN" (port), "a" (value));
}

void kernaux_asm_x86_outportd(const uint16_t port, const uint32_t value)
{
    KERNAUX_ASM("outl %1, %0" : : "dN" (port), "a" (value));
}

#ifdef __cplusplus
}
#endif

#endif
