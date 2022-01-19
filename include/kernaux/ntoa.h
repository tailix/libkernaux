#ifndef KERNAUX_INCLUDED_NTOA
#define KERNAUX_INCLUDED_NTOA

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// uint64_t: "18446744073709551615"
// int64_t:  "-9223372036854775808"
#define KERNAUX_ITOA_BUFFER_SIZE 21

void kernaux_utoa10(uint64_t value, char *buffer);
void kernaux_itoa10(int64_t  value, char *buffer);

#ifdef __cplusplus
}
#endif

#endif
