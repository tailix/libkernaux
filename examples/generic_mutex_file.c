/**
 * This is an implementation of a mutex based on lock file, which is NOT very
 * usable. It however doesn't introduce new dependencies (such as libpthread)
 * while still gives an example of how to inherit the generic type.
 */

//===================
// lock_file_mutex.c
//===================

// To not always use macro "KERNAUX_PROTECTED_FIELD" around the names of
// structure fields you may define "KERNAUX_ACCESS_PROTECTED" before including
// any other headers, but ONLY in the file where you implement a generic type.
//
#define KERNAUX_ACCESS_PROTECTED

//===================
// lock_file_mutex.h
//===================

#include <kernaux/generic/mutex.h>
#include <stdio.h>

#define LOCK_FILE_MUTEX_FILENAME_SLEN 40

typedef struct LockFileMutex {
    struct KernAux_Mutex mutex;
    char filename[LOCK_FILE_MUTEX_FILENAME_SLEN + 1];
    FILE *fd;
} *LockFileMutex;

struct LockFileMutex LockFileMutex_create(const char *filename);

//===================
// lock_file_mutex.c
//===================

#include <kernaux/generic/mutex.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>

static void LockFileMutex_lock  (void *mutex);
static void LockFileMutex_unlock(void *mutex);

struct LockFileMutex LockFileMutex_create(const char *filename)
{
    struct LockFileMutex lock_file_mutex;
    lock_file_mutex.mutex.lock = LockFileMutex_lock;
    lock_file_mutex.mutex.unlock = LockFileMutex_unlock;
    strncpy(lock_file_mutex.filename, filename, LOCK_FILE_MUTEX_FILENAME_SLEN);
    lock_file_mutex.filename[LOCK_FILE_MUTEX_FILENAME_SLEN] = '\0';
    return lock_file_mutex;
}

void LockFileMutex_lock(void *const mutex)
{
    LockFileMutex lock_file_mutex = mutex;
    FILE *fd = NULL;
    while (!fd) {
        if (!(fd = fopen(lock_file_mutex->filename, "w"))) {
            sleep(1);
        }
    }
    lock_file_mutex->fd = fd;
}

void LockFileMutex_unlock(void *const mutex)
{
    LockFileMutex lock_file_mutex = mutex;
    FILE *const fd = lock_file_mutex->fd;
    if (!fd) {
        return;
    }
    lock_file_mutex->fd = NULL;
    fclose(fd);
}

//========
// main.c
//========

static int shared_counter = 0;

void example_main()
{
    // Create mutex
    struct LockFileMutex lock_file_mutex =
        LockFileMutex_create("./generic_mutex_file.lock");

    // Lock mutex
    KernAux_Mutex_lock(&lock_file_mutex.mutex);

    // Access shared data
    ++shared_counter;

    // Unlock mutex
    KernAux_Mutex_unlock(&lock_file_mutex.mutex);
}
