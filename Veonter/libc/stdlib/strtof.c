#include <stdlib.h>
#include <string.h>
#include <ctype.h>

float strtof(const char* str, char** endptr) {
    float result = 0.0;
    int sign = 1;
    int decimal_part = 0;
    int decimal_place = 1;

    // Пропуск пробелов
    while (isspace(*str)) {
        str++;
    }

    // Определение знака
    if (*str == '+' || *str == '-') {
        if (*str == '-') {
            sign = -1;
        }
        str++;
    }

    // Преобразование целой части
    while (isdigit(*str)) {
        result = result * 10 + (*str - '0');
        str++;
    }

    // Преобразование десятичной части
    if (*str == '.') {
        str++;
        while (isdigit(*str)) {
            decimal_part = decimal_part * 10 + (*str - '0');
            decimal_place *= 10;
            str++;
        }
    }

    // Расчет окончательного значения
    result += (float)decimal_part / decimal_place;

    // Обработка endptr
    if (endptr != NULL) {
        *endptr = (char*)str;
    }

    return result * sign;
}
