#ifndef _CTYPE_H
#define _CTYPE_H 1

#include <sys/cdefs.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

int isdigit(int c);
int isspace(int c);
int isupper(int c);
int tolower(int c);
int isalpha(int c);
int isalnum(int c);

#ifdef __cplusplus
}
#endif

#endif
