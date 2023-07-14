#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

double atof(const char *str) {
    double result = 0.0;
    double factor = 1.0;
    int sign = 1;

    // Пропускаем начальные пробелы
    while (*str == ' ') {
        str++;
    }

    // Определяем знак числа
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // Числовая часть
    while (*str != '\0' && (*str >= '0' && *str <= '9')) {
        result = result * 10.0 + (*str - '0');
        str++;
    }

    // Десятичная точка и дробная часть
    if (*str == '.') {
        str++;
        while (*str != '\0' && (*str >= '0' && *str <= '9')) {
            result = result * 10.0 + (*str - '0');
            factor *= 10.0;
            str++;
        }
    }

    // Применяем знак и дробную часть
    result = sign * result / factor;

    return result;
}