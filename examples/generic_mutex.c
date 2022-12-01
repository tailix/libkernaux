//============
// my_mutex.c
//============

// To not always use macro "KERNAUX_PROTECTED_FIELD" around the names of
// structure fields you may define "KERNAUX_ACCESS_PROTECTED" before including
// any other headers, but ONLY in the file where you implement a generic type.
//
#define KERNAUX_ACCESS_PROTECTED

//============
// my_mutex.h
//============

#include <kernaux/generic/mutex.h>
#include <pthread.h>

typedef struct MyMutex {
    struct KernAux_Mutex mutex;
    pthread_mutex_t pthread_mutex;
} *MyMutex;

struct MyMutex MyMytex_create();

//============
// my_mutex.c
//============

#include <kernaux/generic/mutex.h>
#include <pthread.h>
#include <stdlib.h>

static void MyMutex_lock  (void *mutex);
static void MyMutex_unlock(void *mutex);

struct MyMutex MyMutex_create()
{
    struct MyMutex my_mutex = {
        .mutex = {
            .lock   = MyMutex_lock,
            .unlock = MyMutex_unlock,
        },
    };
    if (pthread_mutex_init(&my_mutex.pthread_mutex, NULL) != 0) abort();
    return my_mutex;
}

void MyMutex_lock(void *const mutex)
{
    const MyMutex my_mutex = mutex;
    pthread_mutex_lock(&my_mutex->pthread_mutex);
}

void MyMutex_unlock(void *const mutex)
{
    const MyMutex my_mutex = mutex;
    pthread_mutex_unlock(&my_mutex->pthread_mutex);
}

//========
// main.c
//========

static int shared_counter = 0;

void example_main()
{
    // Create mutex
    struct MyMutex my_mutex = MyMutex_create();

    // Lock mutex
    KernAux_Mutex_lock(&my_mutex.mutex);

    // Access shared data
    ++shared_counter;

    // Unlock mutex
    KernAux_Mutex_unlock(&my_mutex.mutex);
}
