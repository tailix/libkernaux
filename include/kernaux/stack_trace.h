#ifndef KERNAUX_INCLUDED_STACK_TRACE
#define KERNAUX_INCLUDED_STACK_TRACE

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

void kernaux_stack_trace_snprint(char *buffer, size_t buffer_size);

#ifdef __cplusplus
}
#endif

#endif
