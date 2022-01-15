/*
    We don't include <kernaux/asm/*.h> because they
    contain architecture-specific assembly functions.

    We don't include <kernaux/libc.h> because it may
    conflict with actual freestanding or hosted libc.
*/

#include <kernaux/assert.h>
#include <kernaux/cmdline.h>
#include <kernaux/console.h>
#include <kernaux/elf.h>
#include <kernaux/framebuffer.h>
#include <kernaux/itoa.h>
#include <kernaux/multiboot2.h>
#include <kernaux/pfa.h>
#include <kernaux/printf.h>
#include <kernaux/units.h>

#include <kernaux/arch/i386.h>
#include <kernaux/arch/riscv64.h>
#include <kernaux/arch/x86_64.h>
