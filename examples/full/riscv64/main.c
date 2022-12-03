#include <stddef.h>
#include <stdint.h>

#include <kernaux/drivers/shutdown.h>

static unsigned char *const uart = (unsigned char*)0x10000000;

static void putchar(char c) {
    *uart = c;
}

static void print(const char * str) {
    while (*str != '\0') {
        putchar(*str);
        str++;
    }
}

void main() {
    print("Hello world!\r\n");
    kernaux_drivers_shutdown_poweroff();
}
