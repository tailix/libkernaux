#ifndef KERNAUX_INCLUDED_NTOA
#define KERNAUX_INCLUDED_NTOA

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define KERNAUX_NTOA_MAX_PREFIX_LEN 100

#define KERNAUX_NTOA_DEFAULT_PREFIX_2  "0b"
#define KERNAUX_NTOA_DEFAULT_PREFIX_8  "0o"
#define KERNAUX_NTOA_DEFAULT_PREFIX_16 "0x"

// "1111111111111111111111111111111111111111111111111111111111111111"
#define KERNAUX_UTOA_MIN_BUFFER_SIZE (64 + 1)

// "111111111111111111111111111111111111111111111111111111111111111"
// "-1000000000000000000000000000000000000000000000000000000000000000"
#define KERNAUX_ITOA_MIN_BUFFER_SIZE (65 + 1)

// "0b1111111111111111111111111111111111111111111111111111111111111111"
#define KERNAUX_UTOA2_BUFFER_SIZE (64 + 2 + 1)

// "0b111111111111111111111111111111111111111111111111111111111111111"
// "-0b1000000000000000000000000000000000000000000000000000000000000000"
#define KERNAUX_ITOA2_BUFFER_SIZE (65 + 2 + 1)

// "0o1777777777777777777777"
#define KERNAUX_UTOA8_BUFFER_SIZE (21 + 2 + 1)

// "0o777777777777777777777"
// "-0o1000000000000000000000"
#define KERNAUX_ITOA8_BUFFER_SIZE (22 + 2 + 1)

// "18446744073709551615"
#define KERNAUX_UTOA10_BUFFER_SIZE (20 + 1)

// "9223372036854775807"
// "-9223372036854775808"
#define KERNAUX_ITOA10_BUFFER_SIZE (20 + 1)

// "0xffffffffffffffff"
#define KERNAUX_UTOA16_BUFFER_SIZE (16 + 2 + 1)

// "0x7fffffffffffffff"
// "-0x8000000000000000"
#define KERNAUX_ITOA16_BUFFER_SIZE (17 + 2 + 1)

char *kernaux_utoa(uint64_t value, char *buffer, int base, const char *prefix);
char *kernaux_itoa(int64_t  value, char *buffer, int base, const char *prefix);

char *kernaux_utoa2(uint64_t value, char *buffer);
char *kernaux_itoa2(int64_t  value, char *buffer);

char *kernaux_utoa8(uint64_t value, char *buffer);
char *kernaux_itoa8(int64_t  value, char *buffer);

char *kernaux_utoa10(uint64_t value, char *buffer);
char *kernaux_itoa10(int64_t  value, char *buffer);

char *kernaux_utoa16(uint64_t value, char *buffer);
char *kernaux_itoa16(int64_t  value, char *buffer);

#ifdef __cplusplus
}
#endif

#endif
