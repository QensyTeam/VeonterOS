#ifndef _STDIO_H
#define _STDIO_H 1

#include <sys/cdefs.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char* __restrict, ...);
int scanf(const char* format, ...);
int putchar(int);
int puts(const char*);
void read_line(char *buffer, size_t size);
void reverse(char* str, int length);

#ifdef __cplusplus
}
#endif

#endif
