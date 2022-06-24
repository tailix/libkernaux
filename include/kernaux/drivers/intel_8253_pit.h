/**
 * @brief A driver for Intel 8253-compatible programmable interval timer
 *
 * @see https://en.wikipedia.org/wiki/Intel_8253
 * @see https://wiki.osdev.org/PIT
 */

#ifndef KERNAUX_INCLUDED_DRIVERS_INTEL_8253_PIT
#define KERNAUX_INCLUDED_DRIVERS_INTEL_8253_PIT

#ifdef __cplusplus
extern "C" {
#endif

void kernaux_drivers_intel_8253_pit_initialize(unsigned int freq);

#ifdef __cplusplus
}
#endif

#endif