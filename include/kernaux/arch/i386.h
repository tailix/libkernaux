#ifndef KERNAUX_INCLUDED_ARCH_I386
#define KERNAUX_INCLUDED_ARCH_I386 1

#ifdef __cplusplus
extern "C" {
#endif

unsigned long kernaux_arch_i386_read_cr0();
unsigned long kernaux_arch_i386_read_cr4();

void kernaux_arch_i386_write_cr0(volatile unsigned long value);
void kernaux_arch_i386_write_cr3(volatile unsigned long value);
void kernaux_arch_i386_write_cr4(volatile unsigned long value);

#ifdef __cplusplus
}
#endif

#endif
