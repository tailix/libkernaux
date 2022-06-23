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

#define MASTER_COMMAND_PORT 0x20
#define SLAVE_COMMAND_PORT  0xA0

#define MASTER_DATA_PORT 0x21
#define SLAVE_DATA_PORT  0xA1

#define IRQS_COUNT 8
#define IRQS_TOTAL 16

#undef AVAILABLE
#define NOT_AVAILABLE_MSG "Intel 8259-compatible PIC is not available"
#ifdef ASM_I386
#   define AVAILABLE
#   define inportb  kernaux_asm_i386_inportb
#   define outportb kernaux_asm_i386_outportb
#endif

static unsigned char master_start = 0;
static unsigned char slave_start  = 8;

void kernaux_drivers_intel_8259_pic_enable_all()
{
#ifndef AVAILABLE
    KERNAUX_PANIC(NOT_AVAILABLE_MSG);
#else
    outportb(MASTER_DATA_PORT, 0);
    outportb(SLAVE_DATA_PORT,  0);
#endif
}

void kernaux_drivers_intel_8259_pic_disable_all()
{
#ifndef AVAILABLE
    KERNAUX_PANIC(NOT_AVAILABLE_MSG);
#else
    outportb(MASTER_DATA_PORT, 0xFF);
    outportb(SLAVE_DATA_PORT,  0xFF);
#endif
}

void kernaux_drivers_intel_8259_pic_enable(const unsigned char number)
{
#ifndef AVAILABLE
    (void)number;
    KERNAUX_PANIC(NOT_AVAILABLE_MSG);
#else
    KERNAUX_ASSERT(number < IRQS_TOTAL);

    if (number < IRQS_COUNT) {
        const uint8_t mask = inportb(MASTER_DATA_PORT);
        outportb(MASTER_DATA_PORT, mask & ~(1 << number));
    } else {
        const uint8_t mask = inportb(SLAVE_DATA_PORT);
        outportb(SLAVE_DATA_PORT, mask & ~(1 << (number - IRQS_COUNT)));
    }
#endif
}

void kernaux_drivers_intel_8259_pic_disable(const unsigned char number)
{
#ifndef AVAILABLE
    (void)number;
    KERNAUX_PANIC(NOT_AVAILABLE_MSG);
#else
    KERNAUX_ASSERT(number < IRQS_TOTAL);

    if (number < IRQS_COUNT) {
        const uint8_t mask = inportb(MASTER_DATA_PORT);
        outportb(MASTER_DATA_PORT, mask | (1 << number));
    } else {
        const uint8_t mask = inportb(SLAVE_DATA_PORT);
        outportb(SLAVE_DATA_PORT, mask | (1 << (number - IRQS_COUNT)));
    }
#endif
}

void kernaux_drivers_intel_8259_pic_remap(
    const unsigned char new_master_start,
    const unsigned char new_slave_start
) {
#ifndef AVAILABLE
    KERNAUX_PANIC(NOT_AVAILABLE_MSG);
#else
    master_start = new_master_start;
    slave_start  = new_slave_start;

    // Save masks
    const uint8_t master_mask = inportb(MASTER_DATA_PORT);
    const uint8_t slave_mask  = inportb(SLAVE_DATA_PORT);

    // Start the initialization sequence
    outportb(MASTER_COMMAND_PORT, 0x11);
    outportb(SLAVE_COMMAND_PORT,  0x11);

    // Set IRQ vectors
    outportb(MASTER_DATA_PORT, new_master_start);
    outportb(SLAVE_DATA_PORT,  new_slave_start);

    // Connect master and slave with each other
    outportb(MASTER_DATA_PORT, 0x04);
    outportb(SLAVE_DATA_PORT,  0x02);

    // 8086/88 (MCS-80/85) mode
    outportb(MASTER_DATA_PORT, 0x01);
    outportb(SLAVE_DATA_PORT,  0x01);

    // Restore masks
    outportb(MASTER_DATA_PORT, master_mask);
    outportb(SLAVE_DATA_PORT,  slave_mask);
#endif
}

void kernaux_drivers_intel_8259_pic_eoi(const unsigned char number)
{
#ifndef AVAILABLE
    KERNAUX_PANIC(NOT_AVAILABLE_MSG);
#else
    KERNAUX_ASSERT(number < IRQS_TOTAL);

    const bool to_slave =
        number >= slave_start && number < slave_start + IRQS_COUNT;
    const bool to_master = to_slave ||
        (number >= master_start && number < master_start + IRQS_COUNT);

    if (to_slave)  outportb(SLAVE_COMMAND_PORT,  0x20);
    if (to_master) outportb(MASTER_COMMAND_PORT, 0x20);
#endif
}
