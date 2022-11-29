#ifndef KERNAUX_INCLUDED_ASM_I386
#define KERNAUX_INCLUDED_ASM_I386

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/arch/i386.h>
#include <kernaux/asm/x86.h>

void kernaux_asm_i386_flush_gdt(
    volatile uint32_t pointer,
    volatile uint32_t data_selector,
    volatile uint32_t code_selector
);
void kernaux_asm_i386_flush_idt(volatile uint32_t pointer);
void kernaux_asm_i386_flush_tss(volatile uint16_t selector);

uint32_t kernaux_asm_i386_read_cr0();
uint32_t kernaux_asm_i386_read_cr4();

void kernaux_asm_i386_write_cr0(volatile uint32_t value);
void kernaux_asm_i386_write_cr3(volatile uint32_t value);
void kernaux_asm_i386_write_cr4(volatile uint32_t value);

#ifdef __cplusplus
}
#endif

#endif
