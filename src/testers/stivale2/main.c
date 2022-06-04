#include <stdint.h>
#include <stddef.h>

#include <kernaux/console.h>

#include "stivale2.h"

static void poweroff();

uint8_t stack[8192];
 
// We will now write a helper function which will allow us to scan for tags
// that we want FROM the bootloader (structure tags).
void *stivale2_get_tag(struct stivale2_struct *stivale2_struct, uint64_t id) {
    struct stivale2_tag *current_tag = (void *)stivale2_struct->tags;
    for (;;) {
        // If the tag pointer is NULL (end of linked list), we did not find
        // the tag. Return NULL to signal this.
        if (current_tag == NULL) {
            return NULL;
        }
 
        // Check whether the identifier matches. If it does, return a pointer
        // to the matching tag.
        if (current_tag->identifier == id) {
            return current_tag;
        }
 
        // Get a pointer to the next tag in the linked list and repeat.
        current_tag = (void *)current_tag->next;
    }
}
 
// The following will be our kernel's entry point.
void _start(struct stivale2_struct *stivale2_struct __attribute__((unused))) {
    kernaux_console_puts("Hello, World!");
    poweroff();
}

void poweroff()
{
    const uint16_t port  = 0x604;
    const uint16_t value = 0x2000;
    __asm__ volatile("outw %1, %0" : : "dN" (port), "a" (value));
}
