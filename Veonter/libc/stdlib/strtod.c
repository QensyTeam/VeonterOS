#include <stdlib.h>
#include <ctype.h>
#include <math.h>

double strtod(const char* str, char** endptr) {
    double result = 0.0;
    int sign = 1;
    int hasDigits = 0;
    
    // Пропускаем начальные пробелы
    while (isspace(*str)) {
        str++;
    }
    
    // Проверяем знак числа
    if (*str == '+' || *str == '-') {
        sign = (*str++ == '+') ? 1 : -1;
    }
    
    // Обрабатываем целую часть числа
    while (isdigit(*str)) {
        result = result * 10 + (*str - '0');
        str++;
        hasDigits = 1;
    }
    
    // Обрабатываем дробную часть числа
    if (*str == '.') {
        double factor = 0.1;
        str++;
        
        while (isdigit(*str)) {
            result += (*str - '0') * factor;
            factor *= 0.1;
            str++;
            hasDigits = 1;
        }
    }
    
    // Обрабатываем экспоненту числа
    if (*str == 'e' || *str == 'E') {
        int exponent = 0;
        int expSign = 1;
        str++;
        
        // Проверяем знак экспоненты
        if (*str == '+' || *str == '-') {
            expSign = (*str++ == '+') ? 1 : -1;
        }
        
        // Обрабатываем значение экспоненты
        while (isdigit(*str)) {
            exponent = exponent * 10 + (*str - '0');
            str++;
        }
        
        result *= pow(10, exponent * expSign);
    }
    
    // Устанавливаем указатель на символ, следующий за числом
    if (endptr != NULL) {
        *endptr = (hasDigits) ? (char*)str : (char*)str - 1;
    }
    
    return result * sign;
}