#ifndef KERNAUX_INCLUDED_MACRO
#define KERNAUX_INCLUDED_MACRO

#ifdef __cplusplus
extern "C" {
#endif

#include <limits.h>
#include <stddef.h>
#include <stdint.h>

/*********************
 * Language features *
 *********************/

#define KERNAUX_NORETURN      __attribute__((noreturn))
#define KERNAUX_RETURNS_TWICE __attribute__((returns_twice))
#define KERNAUX_UNUSED        __attribute__((unused))
#define KERNAUX_USED          __attribute__((used))

#define KERNAUX_ALIGNED(num)      __attribute__((aligned(num)))
#define KERNAUX_PRINTF(fmt, rest) __attribute__((format(printf, fmt, rest)))
#define KERNAUX_SECTION(name)     __attribute__((section(name)))

#ifdef __TINYC__
#   define KERNAUX_PACKED
#else
#   define KERNAUX_PACKED __attribute__((packed))
#endif

#define KERNAUX_ASM(...) do { __asm__ __volatile__(__VA_ARGS__); } while (0)

/**************
 * Visibility *
 **************/

#ifdef KERNAUX_ACCESS_PRIVATE
#   define KERNAUX_PRIVATE_FIELD(id) id
#   define KERNAUX_PROTECTED_FIELD(id) id
#else
#   define KERNAUX_PRIVATE_FIELD(id) _private_##id

#   ifdef KERNAUX_ACCESS_PROTECTED
#       define KERNAUX_PROTECTED_FIELD(id) id
#   else
#       define KERNAUX_PROTECTED_FIELD(id) _protected_##id
#   endif
#endif // KERNAUX_ACCESS_PRIVATE

/*********************
 * Static assertions *
 *********************/

#define KERNAUX_STATIC_TEST_STRUCT_SIZE(name, size) \
KERNAUX_UNUSED                                      \
static const int                                    \
_kernaux_static_test_struct_size_##name[            \
    sizeof(struct name) == (size) ? 1 : -1          \
]

#define KERNAUX_STATIC_TEST_UNION_SIZE(name, size)  \
KERNAUX_UNUSED                                      \
static const int                                    \
_kernaux_static_test_union_size_##name[             \
    sizeof(union name) == (size) ? 1 : -1           \
]

/*****************
 * Simple values *
 *****************/

#define KERNAUX_EOF (-1)

/*********************
 * Calculated values *
 *********************/

#define KERNAUX_CONTAINER_OF(ptr, type, member) \
    ((type*)((uintptr_t)(ptr) - offsetof(type, member)))

#define KERNAUX_BITS(n) (1u << (n))

#define KERNAUX_BITS8(n)  ((uint8_t )(((uint8_t )1) << (n)))
#define KERNAUX_BITS16(n) ((uint16_t)(((uint16_t)1) << (n)))
#define KERNAUX_BITS32(n) ((uint32_t)(((uint32_t)1) << (n)))
#define KERNAUX_BITS64(n) ((uint64_t)(((uint64_t)1) << (n)))

/*****************************************
 * Macros for printing format specifiers *
 *****************************************/

// Each variable argument is always adjusted to take at least 32 bits
// (at least on the platforms which we support).
#define KERNAUX_PRIu8  "u"
#define KERNAUX_PRIi8  "i"
#define KERNAUX_PRIu16 "u"
#define KERNAUX_PRIi16 "i"

#if ULONG_MAX > UINT_MAX
#define KERNAUX_PRIu32 "u"
#define KERNAUX_PRIu64 "lu"
#else
#define KERNAUX_PRIu32 "u"
#define KERNAUX_PRIu64 "llu"
#endif

#if LONG_MAX > INT_MAX
#define KERNAUX_PRIi32 "i"
#define KERNAUX_PRIi64 "li"
#else
#define KERNAUX_PRIi32 "i"
#define KERNAUX_PRIi64 "lli"
#endif

#ifdef __cplusplus
}
#endif

#endif
