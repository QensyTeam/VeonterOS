#ifndef _STDLIB_H
#define _STDLIB_H 1

#include <sys/cdefs.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((__noreturn__))
void abort(void);
void* malloc(size_t size);
void itoa(int32_t value, char* buffer, int base);
void utoa(unsigned int num, char *str, int base);
int atoi(const char* str);
double atof(const char *str);
long atol(const char* str);
char* ultoa(unsigned long long int value, char* str, int base);
char* ltoa(long value, char* str, int base);
char* lltoa(long long int value, char* str, int base);
char* ftoa(float value, char* buffer, int precision);
float strtof(const char* str, char** endptr);
double strtod(const char* str, char** endptr);
long strtol(const char* str, char** endptr, int base);

#ifdef __cplusplus
}
#endif

#endif
