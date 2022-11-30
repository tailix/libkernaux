#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/drivers/intel_8259_pic.h>
#include <kernaux/macro.h>

#ifdef ASM_I386
#include <kernaux/asm/i386.h>
#endif

#include <stdbool.h>
#include <stdint.h>

#define MASTER_COMMAND_PORT 0x20
#define SLAVE_COMMAND_PORT  0xA0

#define MASTER_DATA_PORT 0x21
#define SLAVE_DATA_PORT  0xA1

#define IRQS_COUNT 8
#define IRQS_TOTAL 16

static unsigned char master_start = 0;
static unsigned char slave_start  = 8;

void kernaux_drivers_intel_8259_pic_enable_all()
{
    kernaux_asm_x86_outportb(MASTER_DATA_PORT, 0);
    kernaux_asm_x86_outportb(SLAVE_DATA_PORT,  0);
}

void kernaux_drivers_intel_8259_pic_disable_all()
{
    kernaux_asm_x86_outportb(MASTER_DATA_PORT, 0xFF);
    kernaux_asm_x86_outportb(SLAVE_DATA_PORT,  0xFF);
}

void kernaux_drivers_intel_8259_pic_enable(const unsigned char number)
{
    KERNAUX_ASSERT(number < IRQS_TOTAL);

    if (number < IRQS_COUNT) {
        const uint8_t mask = kernaux_asm_x86_inportb(MASTER_DATA_PORT);
        kernaux_asm_x86_outportb(MASTER_DATA_PORT,
                                 mask & ~KERNAUX_BITS8(number));
    } else {
        const uint8_t mask = kernaux_asm_x86_inportb(SLAVE_DATA_PORT);
        kernaux_asm_x86_outportb(SLAVE_DATA_PORT,
                                 mask & ~KERNAUX_BITS8((number - IRQS_COUNT)));
    }
}

void kernaux_drivers_intel_8259_pic_disable(const unsigned char number)
{
    KERNAUX_ASSERT(number < IRQS_TOTAL);

    if (number < IRQS_COUNT) {
        const uint8_t mask = kernaux_asm_x86_inportb(MASTER_DATA_PORT);
        kernaux_asm_x86_outportb(MASTER_DATA_PORT,
                                 mask | KERNAUX_BITS8(number));
    } else {
        const uint8_t mask = kernaux_asm_x86_inportb(SLAVE_DATA_PORT);
        kernaux_asm_x86_outportb(SLAVE_DATA_PORT,
                                 mask | KERNAUX_BITS8((number - IRQS_COUNT)));
    }
}

void kernaux_drivers_intel_8259_pic_remap(
    const unsigned char new_master_start,
    const unsigned char new_slave_start
) {
    master_start = new_master_start;
    slave_start  = new_slave_start;

    // Save masks
    const uint8_t master_mask = kernaux_asm_x86_inportb(MASTER_DATA_PORT);
    const uint8_t slave_mask  = kernaux_asm_x86_inportb(SLAVE_DATA_PORT);

    // Start the initialization sequence
    kernaux_asm_x86_outportb(MASTER_COMMAND_PORT, 0x11);
    kernaux_asm_x86_outportb(SLAVE_COMMAND_PORT,  0x11);

    // Set IRQ vectors
    kernaux_asm_x86_outportb(MASTER_DATA_PORT, new_master_start);
    kernaux_asm_x86_outportb(SLAVE_DATA_PORT,  new_slave_start);

    // Connect master and slave with each other
    kernaux_asm_x86_outportb(MASTER_DATA_PORT, 0x04);
    kernaux_asm_x86_outportb(SLAVE_DATA_PORT,  0x02);

    // 8086/88 (MCS-80/85) mode
    kernaux_asm_x86_outportb(MASTER_DATA_PORT, 0x01);
    kernaux_asm_x86_outportb(SLAVE_DATA_PORT,  0x01);

    // Restore masks
    kernaux_asm_x86_outportb(MASTER_DATA_PORT, master_mask);
    kernaux_asm_x86_outportb(SLAVE_DATA_PORT,  slave_mask);
}

void kernaux_drivers_intel_8259_pic_eoi(const unsigned char number)
{
    KERNAUX_ASSERT(number < IRQS_TOTAL);

    const bool to_slave =
        number >= slave_start && number < slave_start + IRQS_COUNT;
    const bool to_master = to_slave ||
        (number >= master_start && number < master_start + IRQS_COUNT);

    if (to_slave)  kernaux_asm_x86_outportb(SLAVE_COMMAND_PORT,  0x20);
    if (to_master) kernaux_asm_x86_outportb(MASTER_COMMAND_PORT, 0x20);
}
