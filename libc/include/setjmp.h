#ifndef _SETJMP_H
#define _SETJMP_H 1

#ifdef __cplusplus
extern "C" {
#endif

typedef int jmp_buf;

int setjmp(jmp_buf env);
void longjmp(jmp_buf env, int val);

#ifdef __cplusplus
}
#endif

#endif
