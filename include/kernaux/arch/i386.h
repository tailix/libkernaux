// TODO: Use [u]int(8|16|32)_t when problem with <stdint.h> is fixed.

#ifndef KERNAUX_INCLUDED_ARCH_I386
#define KERNAUX_INCLUDED_ARCH_I386 1

#ifdef __cplusplus
extern "C" {
#endif

inline static unsigned char  kernaux_arch_i386_inportb(unsigned short port);
inline static unsigned short kernaux_arch_i386_inportw(unsigned short port);
inline static unsigned int   kernaux_arch_i386_inportd(unsigned short port);

inline static void
kernaux_arch_i386_outportb(unsigned short port, unsigned char  value);

inline static void
kernaux_arch_i386_outportw(unsigned short port, unsigned short value);

inline static void
kernaux_arch_i386_outportd(unsigned short port, unsigned int   value);

void kernaux_arch_i386_hang() __attribute__((noreturn));

unsigned long kernaux_arch_i386_read_cr0();
unsigned long kernaux_arch_i386_read_cr4();

void kernaux_arch_i386_write_cr0(volatile unsigned long value);
void kernaux_arch_i386_write_cr3(volatile unsigned long value);
void kernaux_arch_i386_write_cr4(volatile unsigned long value);

unsigned char kernaux_arch_i386_inportb(const unsigned short port)
{
    register unsigned char result;
    __asm__ volatile("inb %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

unsigned short kernaux_arch_i386_inportw(const unsigned short port)
{
    register unsigned short result;
    __asm__ volatile("inw %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

unsigned int kernaux_arch_i386_inportd(const unsigned short port)
{
    register unsigned int result;
    __asm__ volatile("ind %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

void kernaux_arch_i386_outportb(
    const unsigned short port,
    const unsigned char value
) {
    __asm__ volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

void kernaux_arch_i386_outportw(
    const unsigned short port,
    const unsigned short value
) {
    __asm__ volatile("outw %1, %0" : : "dN" (port), "a" (value));
}

void kernaux_arch_i386_outportd(
    const unsigned short port,
    const unsigned int value
) {
    __asm__ volatile("outd %1, %0" : : "dN" (port), "a" (value));
}

#ifdef __cplusplus
}
#endif

#endif
