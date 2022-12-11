#ifndef KERNAUX_INCLUDED_MACRO
#define KERNAUX_INCLUDED_MACRO

#ifdef __cplusplus
extern "C" {
#endif

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

#define KERNAUX_STATIC_TEST(name, cond) \
    KERNAUX_UNUSED \
    static const int \
    _kernaux_static_test_##name[(cond) ? 1 : -1]

#define KERNAUX_STATIC_TEST_STRUCT_SIZE(name, size) \
    KERNAUX_STATIC_TEST(struct_size_##name, sizeof(struct name) == (size))

#define KERNAUX_STATIC_TEST_UNION_SIZE(name, size)  \
    KERNAUX_STATIC_TEST(union_size_##name,  sizeof(union  name) == (size))

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

/*********************
 * Safe type casting *
 *********************/

#define KERNAUX_CAST_VAR(type, name, value) \
    KERNAUX_STATIC_TEST(cast_pos_##name, sizeof(value)    <= sizeof(type)); \
    KERNAUX_STATIC_TEST(cast_neg_##name, sizeof(-(value)) <= sizeof(type)); \
    type name = (type)(value);                                              \
    do {} while (0)

#define KERNAUX_CAST_CONST(type, name, value) \
    KERNAUX_CAST_VAR(const type, name, value)

#ifdef __cplusplus
}
#endif

#endif
