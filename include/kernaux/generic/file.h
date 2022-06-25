#ifndef KERNAUX_INCLUDED_FILE
#define KERNAUX_INCLUDED_FILE

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>

#define KERNAUX_EOF (-1)

typedef int (*KernAux_File_Putc)(void *file, int c);
typedef int (*KernAux_File_Puts)(void *file, const char *s);

typedef struct KernAux_File {
    KernAux_File_Putc KERNAUX_PROTECTED_FIELD(putc);
    KernAux_File_Puts KERNAUX_PROTECTED_FIELD(puts);
} *KernAux_File;

int KernAux_File_putc(KernAux_File file, int c);
int KernAux_File_puts(KernAux_File file, const char *s);

#ifdef __cplusplus
}
#endif

#endif
