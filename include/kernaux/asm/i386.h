#ifndef KERNAUX_INCLUDED_ASM_I386
#define KERNAUX_INCLUDED_ASM_I386

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/arch/i386.h>

inline static uint8_t  kernaux_asm_i386_inportb(uint16_t port);
inline static uint16_t kernaux_asm_i386_inportw(uint16_t port);
inline static uint32_t kernaux_asm_i386_inportd(uint16_t port);

inline static void kernaux_asm_i386_outportb(uint16_t port, uint8_t  value);
inline static void kernaux_asm_i386_outportw(uint16_t port, uint16_t value);
inline static void kernaux_asm_i386_outportd(uint16_t port, uint32_t value);

void kernaux_asm_i386_flush_idt(volatile uint32_t value);

uint32_t kernaux_asm_i386_read_cr0();
uint32_t kernaux_asm_i386_read_cr4();

void kernaux_asm_i386_write_cr0(volatile uint32_t value);
void kernaux_asm_i386_write_cr3(volatile uint32_t value);
void kernaux_asm_i386_write_cr4(volatile uint32_t value);

uint8_t kernaux_asm_i386_inportb(const uint16_t port)
{
    register uint8_t result;
    __asm__ volatile("inb %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

uint16_t kernaux_asm_i386_inportw(const uint16_t port)
{
    register uint16_t result;
    __asm__ volatile("inw %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

uint32_t kernaux_asm_i386_inportd(const uint16_t port)
{
    register uint32_t result;
    __asm__ volatile("inl %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

void kernaux_asm_i386_outportb(const uint16_t port, const uint8_t value)
{
    __asm__ volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

void kernaux_asm_i386_outportw(const uint16_t port, const uint16_t value)
{
    __asm__ volatile("outw %1, %0" : : "dN" (port), "a" (value));
}

void kernaux_asm_i386_outportd(const uint16_t port, const uint32_t value)
{
    __asm__ volatile("outl %1, %0" : : "dN" (port), "a" (value));
}

#ifdef __cplusplus
}
#endif

#endif
