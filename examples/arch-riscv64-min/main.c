#include <stddef.h>
#include <stdint.h>

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
}
