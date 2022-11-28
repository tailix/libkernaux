#ifndef _CTYPE_H
#define _CTYPE_H 1

#ifdef __cplusplus
extern "C" {
#endif

int isdigit(int c);
int islower(int c);
int isspace(int c);
int isupper(int c);

int tolower(int c);
int toupper(int c);

#ifdef __cplusplus
}
#endif

#endif
