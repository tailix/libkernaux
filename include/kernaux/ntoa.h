#ifndef KERNAUX_INCLUDED_NTOA
#define KERNAUX_INCLUDED_NTOA

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// "1111111111111111111111111111111111111111111111111111111111111111"
#define KERNAUX_UTOA_BUFFER_SIZE 65

// "111111111111111111111111111111111111111111111111111111111111111"
// "-1000000000000000000000000000000000000000000000000000000000000000"
#define KERNAUX_ITOA_BUFFER_SIZE 66

#define KERNAUX_UTOA2_BUFFER_SIZE KERNAUX_UTOA_BUFFER_SIZE
#define KERNAUX_ITOA2_BUFFER_SIZE KERNAUX_ITOA_BUFFER_SIZE

// "1777777777777777777777"
#define KERNAUX_UTOA8_BUFFER_SIZE 22

// "777777777777777777777"
// "-1000000000000000000000"
#define KERNAUX_ITOA8_BUFFER_SIZE 23

// "18446744073709551615"
#define KERNAUX_UTOA10_BUFFER_SIZE 21

// "9223372036854775807"
// "-9223372036854775808"
#define KERNAUX_ITOA10_BUFFER_SIZE 21

// "ffffffffffffffff"
#define KERNAUX_UTOA16_BUFFER_SIZE 17

// "7fffffffffffffff"
// "-8000000000000000"
#define KERNAUX_ITOA16_BUFFER_SIZE 18

char *kernaux_utoa(uint64_t  value, char *buffer, int base);
char *kernaux_utoax(uint64_t value, char *buffer, int base, const char *prefix);
char *kernaux_itoa(int64_t   value, char *buffer, int base);
char *kernaux_itoax(int64_t  value, char *buffer, int base, const char *prefix);

char *kernaux_utoa2(uint64_t  value, char *buffer);
char *kernaux_utoa2x(uint64_t value, char *buffer, const char *prefix);
char *kernaux_itoa2(int64_t   value, char *buffer);
char *kernaux_itoa2x(int64_t  value, char *buffer, const char *prefix);

char *kernaux_utoa8(uint64_t  value, char *buffer);
char *kernaux_utoa8x(uint64_t value, char *buffer, const char *prefix);
char *kernaux_itoa8(int64_t   value, char *buffer);
char *kernaux_itoa8x(int64_t  value, char *buffer, const char *prefix);

char *kernaux_utoa10(uint64_t  value, char *buffer);
char *kernaux_utoa10x(uint64_t value, char *buffer, const char *prefix);
char *kernaux_itoa10(int64_t   value, char *buffer);
char *kernaux_itoa10x(int64_t  value, char *buffer, const char *prefix);

char *kernaux_utoa16(uint64_t  value, char *buffer);
char *kernaux_utoa16x(uint64_t value, char *buffer, const char *prefix);
char *kernaux_itoa16(int64_t   value, char *buffer);
char *kernaux_itoa16x(int64_t  value, char *buffer, const char *prefix);

#ifdef __cplusplus
}
#endif

#endif
