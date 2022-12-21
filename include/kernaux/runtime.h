#ifndef KERNAUX_INCLUDED_RUNTIME
#define KERNAUX_INCLUDED_RUNTIME

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*KernAux_Assert_Cb)(const char *file, int line, const char *msg);

extern KernAux_Assert_Cb kernaux_assert_cb;

#ifdef __cplusplus
}
#endif

#endif
