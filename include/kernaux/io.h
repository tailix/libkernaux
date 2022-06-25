#ifndef KERNAUX_INCLUDED_IO
#define KERNAUX_INCLUDED_IO

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*KernAux_OldFile_Out)(char c, void *arg);

typedef struct KernAux_OldFile {
    KernAux_OldFile_Out out;
} *KernAux_OldFile;

struct KernAux_OldFile KernAux_OldFile_create(KernAux_OldFile_Out out);
void KernAux_OldFile_init(KernAux_OldFile file, KernAux_OldFile_Out out);

#ifdef __cplusplus
}
#endif

#endif
