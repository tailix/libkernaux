#ifndef _SETJMP_H
#define _SETJMP_H 1

#ifdef __cplusplus
extern "C" {
#endif

// TODO: define in architecture-specific header
typedef unsigned long __jmp_buf[sizeof(long) == 8 ? 8 : 6];

typedef struct __jmp_buf_tag {
    __jmp_buf __jb;
    unsigned long __fl;
    unsigned long __ss[128 / sizeof(long)];
} jmp_buf[1];

__attribute__((returns_twice))
int setjmp(jmp_buf env);

__attribute__((noreturn))
void longjmp(jmp_buf env, int val);

#ifdef __cplusplus
}
#endif

#endif
