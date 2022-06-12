#ifndef KERNAUX_INCLUDED_FILE
#define KERNAUX_INCLUDED_FILE

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*KernAux_File_Out)(char c, void *arg);

typedef struct KernAux_File {
    KernAux_File_Out out;
} *KernAux_File;

struct KernAux_File KernAux_File_create(KernAux_File_Out out);
void KernAux_File_init(KernAux_File file, KernAux_File_Out out);

#ifdef __cplusplus
}
#endif

#endif
