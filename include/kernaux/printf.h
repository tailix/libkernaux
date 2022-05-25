#ifndef KERNAUX_INCLUDED_PRINTF
#define KERNAUX_INCLUDED_PRINTF

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

/**
 * Tiny printf/vprintf implementation
 * \param out An output function which takes one character and an argument pointer
 * \param arg An argument pointer for user data passed to output function
 * \param format A string that specifies the format of the output
 * \param va A value identifying a variable arguments list
 * \return The number of characters that are sent to the output function, not counting the terminating null character
 */
int  kernaux_printf(void (*out)(char character, void* arg), void* arg, const char* format, ...);
int kernaux_vprintf(void (*out)(char character, void* arg), void* arg, const char* format, va_list va);

/**
 * Tiny snprintf/vsnprintf implementation
 * \param buffer A pointer to the buffer where to store the formatted string
 * \param count The maximum number of characters to store in the buffer, including a terminating null character
 * \param format A string that specifies the format of the output
 * \param va A value identifying a variable arguments list
 * \return The number of characters that COULD have been written into the buffer, not counting the terminating
 *         null character. A value equal or larger than count indicates truncation. Only when the returned value
 *         is non-negative and less than count, the string has been completely written.
 */
int  kernaux_snprintf(char* buffer, size_t count, const char* format, ...);
int kernaux_vsnprintf(char* buffer, size_t count, const char* format, va_list va);

/**
 * Tiny sprintf implementation
 * Due to security reasons (buffer overflow) YOU SHOULD CONSIDER USING (V)SNPRINTF INSTEAD!
 * \param buffer A pointer to the buffer where to store the formatted string. MUST be big enough to store the output!
 * \param format A string that specifies the format of the output
 * \return The number of characters that are WRITTEN into the buffer, not counting the terminating null character
 */
int kernaux_sprintf(char* buffer, const char* format, ...);

/*****************
 * Auxiliary API *
 *****************/

#define KERNAUX_PRINTF_FLAGS_ZEROPAD   (1u <<  0u)
#define KERNAUX_PRINTF_FLAGS_LEFT      (1u <<  1u)
#define KERNAUX_PRINTF_FLAGS_PLUS      (1u <<  2u)
#define KERNAUX_PRINTF_FLAGS_SPACE     (1u <<  3u)
#define KERNAUX_PRINTF_FLAGS_HASH      (1u <<  4u)
#define KERNAUX_PRINTF_FLAGS_UPPERCASE (1u <<  5u)
#define KERNAUX_PRINTF_FLAGS_CHAR      (1u <<  6u)
#define KERNAUX_PRINTF_FLAGS_SHORT     (1u <<  7u)
#define KERNAUX_PRINTF_FLAGS_LONG      (1u <<  8u)
#define KERNAUX_PRINTF_FLAGS_LONG_LONG (1u <<  9u)
#define KERNAUX_PRINTF_FLAGS_PRECISION (1u << 10u)
#define KERNAUX_PRINTF_FLAGS_ADAPT_EXP (1u << 11u)
#define KERNAUX_PRINTF_FLAGS_CUSTOM    (1u << 12u)

struct KernAux_Printf_Spec {
    unsigned int flags;
    unsigned int width;
    unsigned int precision;
};

struct KernAux_Printf_Spec KernAux_Printf_Spec_create();
void KernAux_Printf_Spec_init(struct KernAux_Printf_Spec *spec);

void KernAux_Printf_Spec_eval_flags(struct KernAux_Printf_Spec *spec, const char **format);
bool KernAux_Printf_Spec_eval_width1(struct KernAux_Printf_Spec *spec, const char **format);
void KernAux_Printf_Spec_eval_width2(struct KernAux_Printf_Spec *spec, const char **format, int w);
bool KernAux_Printf_Spec_eval_precision1(struct KernAux_Printf_Spec *spec, const char **format);
void KernAux_Printf_Spec_eval_precision2(struct KernAux_Printf_Spec *spec, const char **format, int prec);
void KernAux_Printf_Spec_eval_length(struct KernAux_Printf_Spec *spec, const char **format);

#ifdef __cplusplus
}
#endif

#endif
