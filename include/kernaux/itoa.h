#ifndef KERNAUX_INCLUDED_ITOA
#define KERNAUX_INCLUDED_ITOA

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// uint64_t: "18446744073709551615"
#define KERNAUX_ITOA_BUFFER_SIZE 21

// TODO: remove this
void kernaux_itoa(int d, char *buf, int base);

void kernaux_utoa10(uint64_t value, char *buffer);

#ifdef __cplusplus
}
#endif

#endif
