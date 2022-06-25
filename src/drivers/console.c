#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/drivers/console.h>
#include <kernaux/generic/file.h>

#ifdef ASM_I386
#include <kernaux/asm/i386.h>
#endif
#ifdef ASM_X86_64
#include <kernaux/asm/x86_64.h>
#endif

#ifdef WITH_PRINTF
#include <kernaux/printf.h>
#endif

#include <stddef.h>

#ifdef WITH_PRINTF
static int file_putc(void *file, unsigned char c);

static const struct KernAux_File file = {
    .putc = file_putc,
    .puts = NULL,
    .write = NULL,
};
#endif

void kernaux_drivers_console_putc(const char c __attribute__((unused)))
{
#ifdef ASM_I386
    kernaux_asm_i386_outportb(0x3f8, c);
#endif
#ifdef ASM_X86_64
    kernaux_asm_x86_64_outportb(0x3f8, c);
#endif
}

void kernaux_drivers_console_print(const char *const s)
{
    KERNAUX_ASSERT(s);

    for (const char *c = s; *c; ++c) {
        kernaux_drivers_console_putc(*c);
    }
}

#ifdef WITH_PRINTF
void kernaux_drivers_console_printf(const char *format, ...)
{
    KERNAUX_ASSERT(format);

    va_list va;
    va_start(va, format);
    kernaux_vfprintf(&file, format, va);
    va_end(va);
}
#endif

void kernaux_drivers_console_puts(const char *const s)
{
    KERNAUX_ASSERT(s);

    kernaux_drivers_console_print(s);
    kernaux_drivers_console_putc('\n');
}

void kernaux_drivers_console_write(const char *const data, const size_t size)
{
    KERNAUX_ASSERT(data);

    for (size_t i = 0; i < size; i++) {
        kernaux_drivers_console_putc(data[i]);
    }
}

#ifdef WITH_PRINTF
int file_putc(__attribute__((unused)) void *const file, const unsigned char c)
{
    kernaux_drivers_console_putc(c);
    return 1;
}
#endif
