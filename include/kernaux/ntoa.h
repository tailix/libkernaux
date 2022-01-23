#ifndef KERNAUX_INCLUDED_NTOA
#define KERNAUX_INCLUDED_NTOA

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// uint64_t: "18446744073709551615"
// int64_t:  "9223372036854775807"
// int64_t:  "-9223372036854775808"
#define KERNAUX_ITOA10_BUFFER_SIZE 21

// uint64_t: "ffffffffffffffff"
// int64_t:  "7fffffffffffffff"
// int64_t:  "-8000000000000000"
#define KERNAUX_ITOA16_BUFFER_SIZE 18

void kernaux_utoa10(uint64_t value, char *buffer);
void kernaux_itoa10(int64_t  value, char *buffer);

void kernaux_utoa16(uint64_t value, char *buffer);
void kernaux_itoa16(int64_t  value, char *buffer);

#ifdef __cplusplus
}
#endif

#endif
