#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/drivers/intel_8259_pic.h>

#ifdef ASM_I386
#include <kernaux/asm/i386.h>
#endif

#include <stdbool.h>
#include <stdint.h>

#define NOT_AVAILABLE_MSG "Intel 8259-compatible PIC is not available"

#define MASTER_COMMAND_PORT 0x20
#define SLAVE_COMMAND_PORT  0xA0

#define MASTER_DATA_PORT 0x21
#define SLAVE_DATA_PORT  0xA1

#define IRQS_COUNT 8
#define IRQS_TOTAL 16

static unsigned char slave_start  = 8;

void kernaux_drivers_intel_8259_pic_enable_all()
{
#ifdef ASM_I386
    kernaux_asm_i386_outportb(MASTER_DATA_PORT, 0);
    kernaux_asm_i386_outportb(SLAVE_DATA_PORT,  0);
#else
    KERNAUX_PANIC(NOT_AVAILABLE_MSG);
#endif
}

void kernaux_drivers_intel_8259_pic_disable_all()
{
#ifdef ASM_I386
    kernaux_asm_i386_outportb(MASTER_DATA_PORT, 0xFF);
    kernaux_asm_i386_outportb(SLAVE_DATA_PORT,  0xFF);
#else
    KERNAUX_PANIC(NOT_AVAILABLE_MSG);
#endif
}

void kernaux_drivers_intel_8259_pic_enable(const unsigned char number)
{
    KERNAUX_ASSERT(number < IRQS_TOTAL);

#ifdef ASM_I386
    if (number < IRQS_COUNT) {
        const uint8_t mask = kernaux_asm_i386_inportb(MASTER_DATA_PORT);
        kernaux_asm_i386_outportb(MASTER_DATA_PORT, mask & ~(1 << number));
    } else {
        const uint8_t mask = kernaux_asm_i386_inportb(SLAVE_DATA_PORT);
        kernaux_asm_i386_outportb(SLAVE_DATA_PORT, mask & ~(1 << (number - IRQS_COUNT)));
    }
#else
    (void)number;
    KERNAUX_PANIC(NOT_AVAILABLE_MSG);
#endif
}

void kernaux_drivers_intel_8259_pic_disable(const unsigned char number)
{
    KERNAUX_ASSERT(number < IRQS_TOTAL);

#ifdef ASM_I386
    if (number < IRQS_COUNT) {
        const uint8_t mask = kernaux_asm_i386_inportb(MASTER_DATA_PORT);
        kernaux_asm_i386_outportb(MASTER_DATA_PORT, mask | (1 << number));
    } else {
        const uint8_t mask = kernaux_asm_i386_inportb(SLAVE_DATA_PORT);
        kernaux_asm_i386_outportb(SLAVE_DATA_PORT, mask | (1 << (number - IRQS_COUNT)));
    }
#else
    (void)number;
    KERNAUX_PANIC(NOT_AVAILABLE_MSG);
#endif
}

void kernaux_drivers_intel_8259_pic_remap(
    const unsigned char new_master_start,
    const unsigned char new_slave_start
) {
    slave_start = new_slave_start;

#ifdef ASM_I386
    // Save masks
    const uint8_t master_mask = kernaux_asm_i386_inportb(MASTER_DATA_PORT);
    const uint8_t slave_mask  = kernaux_asm_i386_inportb(SLAVE_DATA_PORT);

    // Start the initialization sequence
    kernaux_asm_i386_outportb(MASTER_COMMAND_PORT, 0x11);
    kernaux_asm_i386_outportb(SLAVE_COMMAND_PORT,  0x11);

    // Set IRQ vectors
    kernaux_asm_i386_outportb(MASTER_DATA_PORT, new_master_start);
    kernaux_asm_i386_outportb(SLAVE_DATA_PORT,  new_slave_start);

    // Connect master and slave with each other
    kernaux_asm_i386_outportb(MASTER_DATA_PORT, 0x04);
    kernaux_asm_i386_outportb(SLAVE_DATA_PORT,  0x02);

    // 8086/88 (MCS-80/85) mode
    kernaux_asm_i386_outportb(MASTER_DATA_PORT, 0x01);
    kernaux_asm_i386_outportb(SLAVE_DATA_PORT,  0x01);

    // Restore masks
    kernaux_asm_i386_outportb(MASTER_DATA_PORT, master_mask);
    kernaux_asm_i386_outportb(SLAVE_DATA_PORT,  slave_mask);
#else
    (void)new_master_start;
    KERNAUX_PANIC(NOT_AVAILABLE_MSG);
#endif
}

void kernaux_drivers_intel_8259_pic_eoi(const unsigned char number)
{
    KERNAUX_ASSERT(number < IRQS_TOTAL);

    const bool to_slave =
        slave_start <= number && number < slave_start + IRQS_COUNT;

#ifdef ASM_I386
    if (to_slave) kernaux_asm_i386_outportb(SLAVE_COMMAND_PORT, 0x20);
    kernaux_asm_i386_outportb(MASTER_COMMAND_PORT, 0x20);
#else
    (void)to_slave;
    KERNAUX_PANIC(NOT_AVAILABLE_MSG);
#endif
}
