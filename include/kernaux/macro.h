#ifndef KERNAUX_INCLUDED_MACRO
#define KERNAUX_INCLUDED_MACRO

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __TINY_C__
#   define KERNAUX_PACKING_START #pragma pack(push, 1)
#   define KERNAUX_PACKING_END   #pragma pack(pop)
#   define KERNAUX_PACKING_ATTR
#else
#   define KERNAUX_PACKING_START
#   define KERNAUX_PACKING_END
#   define KERNAUX_PACKING_ATTR __attribute__((packed))
#endif

#ifdef __cplusplus
}
#endif

#endif
