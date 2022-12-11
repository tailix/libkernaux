#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/assert.h>
#include <kernaux/generic/mutex.h>
#include <kernaux/macro.h>
#include <kernaux/spinlock.h>

#include <stdint.h>

static void KernAux_Spinlock_lock  (void *mutex);
static void KernAux_Spinlock_unlock(void *mutex);

struct KernAux_Spinlock KernAux_Spinlock_create()
{
    struct KernAux_Spinlock spinlock;
    KernAux_Spinlock_init(&spinlock);
    return spinlock;
}

void KernAux_Spinlock_init(const KernAux_Spinlock spinlock)
{
    KERNAUX_ASSERT(spinlock);

    spinlock->mutex.lock   = KernAux_Spinlock_lock;
    spinlock->mutex.unlock = KernAux_Spinlock_unlock;
    spinlock->locked = 0;
}

void KernAux_Spinlock_lock(void *const mutex)
{
    const KernAux_Spinlock spinlock = mutex;
    KERNAUX_ASSERT(spinlock);

    KERNAUX_ASM(
        "try:                       \n"
        "mov $1, %%eax              \n"
        "lock xchg %[locked], %%eax \n"
        "test %%eax, %%eax          \n"
        "jnz try                    \n"
        : [locked] "=m" (spinlock->locked)
        :
    );
}

void KernAux_Spinlock_unlock(void *const mutex)
{
    const KernAux_Spinlock spinlock = mutex;
    KERNAUX_ASSERT(spinlock);

    KERNAUX_ASM(
        "xor %%eax, %%eax           \n"
        "lock xchg %[locked], %%eax \n"
        : [locked] "=m" (spinlock->locked)
        :
    );
}
