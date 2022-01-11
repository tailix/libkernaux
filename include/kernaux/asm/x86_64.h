#ifndef KERNAUX_INCLUDED_ASM_X86_64
#define KERNAUX_INCLUDED_ASM_X86_64

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/arch/x86_64.h>

void kernaux_asm_x86_64_hang() __attribute__((noreturn));

inline static uint8_t  kernaux_asm_x86_64_inportb(uint16_t port);
inline static uint16_t kernaux_asm_x86_64_inportw(uint16_t port);
inline static uint32_t kernaux_asm_x86_64_inportd(uint16_t port);

inline static void kernaux_asm_x86_64_outportb(uint16_t port, uint8_t  value);
inline static void kernaux_asm_x86_64_outportw(uint16_t port, uint16_t value);
inline static void kernaux_asm_x86_64_outportd(uint16_t port, uint32_t value);

uint8_t kernaux_asm_x86_64_inportb(const uint16_t port)
{
    register uint8_t result;
    __asm__ volatile("inb %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

uint16_t kernaux_asm_x86_64_inportw(const uint16_t port)
{
    register uint16_t result;
    __asm__ volatile("inw %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

uint32_t kernaux_asm_x86_64_inportd(const uint16_t port)
{
    register uint32_t result;
    __asm__ volatile("inl %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

void kernaux_asm_x86_64_outportb(const uint16_t port, const uint8_t value)
{
    __asm__ volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

void kernaux_asm_x86_64_outportw(const uint16_t port, const uint16_t value)
{
    __asm__ volatile("outw %1, %0" : : "dN" (port), "a" (value));
}

void kernaux_asm_x86_64_outportd(const uint16_t port, const uint32_t value)
{
    __asm__ volatile("outl %1, %0" : : "dN" (port), "a" (value));
}

#ifdef __cplusplus
}
#endif

#endif
