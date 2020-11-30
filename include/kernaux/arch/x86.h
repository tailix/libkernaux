#ifndef KERNAUX_INCLUDED_ARCH_X86
#define KERNAUX_INCLUDED_ARCH_X86 1

#ifdef __cplusplus
extern "C" {
#endif

inline static unsigned char  kernaux_arch_x86_inportb(unsigned short port);
inline static unsigned short kernaux_arch_x86_inportw(unsigned short port);
inline static unsigned int   kernaux_arch_x86_inportd(unsigned short port);

inline static void
kernaux_arch_x86_outportb(unsigned short port, unsigned char  value);

inline static void
kernaux_arch_x86_outportw(unsigned short port, unsigned short value);

inline static void
kernaux_arch_x86_outportd(unsigned short port, unsigned int   value);

void kernaux_arch_x86_hang() __attribute__((noreturn));

unsigned long kernaux_arch_x86_read_cr0();
unsigned long kernaux_arch_x86_read_cr4();

void kernaux_arch_x86_write_cr0(volatile unsigned long value);
void kernaux_arch_x86_write_cr3(volatile unsigned long value);
void kernaux_arch_x86_write_cr4(volatile unsigned long value);

unsigned char kernaux_arch_x86_inportb(const unsigned short port)
{
    register unsigned char result;
    asm volatile("inb %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

unsigned short kernaux_arch_x86_inportw(const unsigned short port)
{
    register unsigned short result;
    asm volatile("inw %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

unsigned int kernaux_arch_x86_inportd(const unsigned short port)
{
    register unsigned int result;
    asm volatile("ind %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

void kernaux_arch_x86_outportb(
    const unsigned short port,
    const unsigned char value
) {
    asm volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

void kernaux_arch_x86_outportw(
    const unsigned short port,
    const unsigned short value
) {
    asm volatile("outw %1, %0" : : "dN" (port), "a" (value));
}

void kernaux_arch_x86_outportd(
    const unsigned short port,
    const unsigned int value
) {
    asm volatile("outd %1, %0" : : "dN" (port), "a" (value));
}

#ifdef __cplusplus
}
#endif

#endif
