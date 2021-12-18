#ifndef KERNAUX_INCLUDED_ARCH_I386
#define KERNAUX_INCLUDED_ARCH_I386 1

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// CR0 bits
#define KERNAUX_ARCH_I386_CR0_PE ((uint32_t)0x00000001) // 0:  Protected Mode Enable
#define KERNAUX_ARCH_I386_CR0_MP ((uint32_t)0x00000002) // 1:  Monitor co-processor
#define KERNAUX_ARCH_I386_CR0_EM ((uint32_t)0x00000004) // 2:  x87 FPU Emulation
#define KERNAUX_ARCH_I386_CR0_TS ((uint32_t)0x00000008) // 3:  Task switched
#define KERNAUX_ARCH_I386_CR0_ET ((uint32_t)0x00000010) // 4:  Extension type
#define KERNAUX_ARCH_I386_CR0_NE ((uint32_t)0x00000020) // 5:  Numeric error
#define KERNAUX_ARCH_I386_CR0_WP ((uint32_t)0x00010000) // 16: Write protect
#define KERNAUX_ARCH_I386_CR0_AM ((uint32_t)0x00040000) // 18: Alignment mask
#define KERNAUX_ARCH_I386_CR0_NW ((uint32_t)0x20000000) // 29: Not-write trough
#define KERNAUX_ARCH_I386_CR0_CD ((uint32_t)0x40000000) // 30: Cache disable
#define KERNAUX_ARCH_I386_CR0_PG ((uint32_t)0x80000000) // 31: Paging

inline static uint8_t  kernaux_arch_i386_inportb(uint16_t port);
inline static uint16_t kernaux_arch_i386_inportw(uint16_t port);
inline static uint32_t kernaux_arch_i386_inportd(uint16_t port);

inline static void kernaux_arch_i386_outportb(uint16_t port, uint8_t  value);
inline static void kernaux_arch_i386_outportw(uint16_t port, uint16_t value);
inline static void kernaux_arch_i386_outportd(uint16_t port, uint32_t value);

void kernaux_arch_i386_hang() __attribute__((noreturn));

uint16_t kernaux_arch_i386_read_cr0();
uint16_t kernaux_arch_i386_read_cr4();

void kernaux_arch_i386_write_cr0(volatile uint16_t value);
void kernaux_arch_i386_write_cr3(volatile uint16_t value);
void kernaux_arch_i386_write_cr4(volatile uint16_t value);

uint8_t kernaux_arch_i386_inportb(const uint16_t port)
{
    register uint8_t result;
    __asm__ volatile("inb %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

uint16_t kernaux_arch_i386_inportw(const uint16_t port)
{
    register uint16_t result;
    __asm__ volatile("inw %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

uint32_t kernaux_arch_i386_inportd(const uint16_t port)
{
    register uint32_t result;
    __asm__ volatile("ind %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

void kernaux_arch_i386_outportb(const uint16_t port, const uint8_t value)
{
    __asm__ volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

void kernaux_arch_i386_outportw(const uint16_t port, const uint16_t value)
{
    __asm__ volatile("outw %1, %0" : : "dN" (port), "a" (value));
}

void kernaux_arch_i386_outportd(const uint16_t port, const uint32_t value)
{
    __asm__ volatile("outd %1, %0" : : "dN" (port), "a" (value));
}

#ifdef __cplusplus
}
#endif

#endif
