#ifndef KERNAUX_INCLUDED_MACRO
#define KERNAUX_INCLUDED_MACRO

#ifdef __cplusplus
extern "C" {
#endif

#ifdef KERNAUX_ACCESS_MOD_OFF
#define KERNAUX_PRIVATE_FIELD(id) id
#define KERNAUX_PROTECTED_FIELD(id) id
#else
#define KERNAUX_PRIVATE_FIELD(id) _private_##id
#define KERNAUX_PROTECTED_FIELD(id) _protected_##id
#endif

#ifdef __cplusplus
}
#endif

#endif
