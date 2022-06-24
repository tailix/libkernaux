#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/arch/i386.h>

__attribute__((unused))
static const int
TSS_validation[sizeof(struct KernAux_Arch_I386_TSS) == 104 ? 1 : -1];
