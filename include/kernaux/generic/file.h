#ifndef KERNAUX_INCLUDED_FILE
#define KERNAUX_INCLUDED_FILE

#ifdef __cplusplus
extern "C" {
#endif

#include <kernaux/macro.h>

#include <stddef.h>

typedef int  (*KernAux_File_Getc)  (void *file);
typedef int  (*KernAux_File_Putc)  (void *file, unsigned char c);
typedef int  (*KernAux_File_Puts)  (void *file, const char *s);
typedef int  (*KernAux_File_Write) (void *file, const void *buffer, size_t count);
typedef void (*KernAux_File_Rewind)(void *file);

typedef const struct KernAux_File {
    KernAux_File_Getc   KERNAUX_PROTECTED_FIELD(getc);
    KernAux_File_Putc   KERNAUX_PROTECTED_FIELD(putc);
    KernAux_File_Puts   KERNAUX_PROTECTED_FIELD(puts);
    KernAux_File_Write  KERNAUX_PROTECTED_FIELD(write);
    KernAux_File_Rewind KERNAUX_PROTECTED_FIELD(rewind);
} *KernAux_File;

int  KernAux_File_getc  (KernAux_File file);
int  KernAux_File_putc  (KernAux_File file, int c);
int  KernAux_File_puts  (KernAux_File file, const char *s);
int  KernAux_File_write (KernAux_File file, const void *buffer, size_t count);
void KernAux_File_rewind(KernAux_File file);

#ifdef __cplusplus
}
#endif

#endif
