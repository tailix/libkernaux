#ifndef KERNAUX_INCLUDED_MACRO
#define KERNAUX_INCLUDED_MACRO

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

#define KERNAUX_EOF (-1)

#define KERNAUX_CONTAINER_OF(ptr, type, member) \
    ((type*)((uintptr_t)(ptr) - offsetof(type, member)))

#define KERNAUX_BITS(n) (1u << (n))

#define KERNAUX_BITS8(n)  ((uint8_t )(((uint8_t )1) << (n)))
#define KERNAUX_BITS16(n) ((uint16_t)(((uint16_t)1) << (n)))
#define KERNAUX_BITS32(n) ((uint32_t)(((uint32_t)1) << (n)))
#define KERNAUX_BITS64(n) ((uint64_t)(((uint64_t)1) << (n)))

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

#ifdef __TINYC__
#   define KERNAUX_PACKING_ATTR
#else
#   define KERNAUX_PACKING_ATTR __attribute__((packed))
#endif

#define KERNAUX_STATIC_TEST_STRUCT_SIZE(name, size) \
__attribute__((unused))                             \
static const int                                    \
_kernaux_static_test_struct_size_##name[            \
    sizeof(struct name) == (size) ? 1 : -1          \
]

#ifdef __cplusplus
}
#endif

#endif
