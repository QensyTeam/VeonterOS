#ifndef _MATH_H
#define _MATH_H 1

#include <sys/cdefs.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

double pow(double base, double exponent);
double floor(double x);
float floorf(float x);
double round(double x);
float roundf(float x);
int isnan(double value);
int isinf(double value);

#ifdef __cplusplus
}
#endif

#endif
