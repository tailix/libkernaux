#include <kernaux/macro.h>

#include <assert.h>
#include <pthread.h>
#include <stddef.h>

#define THREADS_COUNT 10
#define INCR_COUNT 10000000
#define TOTAL_COUNT (THREADS_COUNT * INCR_COUNT)

static unsigned long long count = 0;

static void *work(void *const arg KERNAUX_UNUSED)
{
    for (unsigned long i = 0; i < INCR_COUNT; ++i) {
        ++count;
    }

    return NULL;
}

void example_main()
{
    pthread_t threads[THREADS_COUNT];
    for (unsigned long i = 0; i < THREADS_COUNT; ++i) {
        assert(!pthread_create(&threads[i], NULL, work, NULL));
    }
    for (unsigned long i = 0; i < THREADS_COUNT; ++i) {
        assert(!pthread_join(threads[i], NULL));
    }
    assert(count == TOTAL_COUNT);
}
