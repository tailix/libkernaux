#ifndef KERNAUX_INCLUDED_FILE
#define KERNAUX_INCLUDED_FILE

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>

typedef int (*KernAux_File_Putc)(void *file, int c);

typedef struct KernAux_File {
    KernAux_File_Putc KERNAUX_PROTECTED_FIELD(putc);
} *KernAux_File;

int KernAux_File_Putc(KernAux_File file, int c);

#ifdef __cplusplus
}
#endif

#endif
