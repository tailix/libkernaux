#ifndef KERNAUX_INCLUDED_MACRO
#define KERNAUX_INCLUDED_MACRO

#ifdef __cplusplus
extern "C" {
#endif

#ifdef KERNAUX_PRIVATE_NO
#define KERNAUX_PRIVATE_FIELD(id) id
#else
#define KERNAUX_PRIVATE_FIELD(id) _private_##id
#endif

#ifdef __cplusplus
}
#endif

#endif
