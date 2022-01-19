#ifndef KERNAUX_INCLUDED_PRINTF
#define KERNAUX_INCLUDED_PRINTF

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
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

#ifdef __cplusplus
}
#endif

#endif
