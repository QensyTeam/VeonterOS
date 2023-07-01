#include <stdlib.h>
#include <string.h>
#include <ctype.h>

long strtol(const char* str, char** endptr, int base) {
    long result = 0;
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
    
    // Определяем базу числа
    if (base == 0) {
        if (*str == '0') {
            if (str[1] == 'x' || str[1] == 'X') {
                base = 16;
                str += 2;
            } else {
                base = 8;
                str++;
            }
        } else {
            base = 10;
        }
    } else if (base == 16 && *str == '0' && (str[1] == 'x' || str[1] == 'X')) {
        str += 2;
    }
    
    // Обрабатываем цифры числа
    while (isalnum(*str)) {
        int digit;
        
        if (isdigit(*str)) {
            digit = *str - '0';
        } else {
            digit = tolower(*str) - 'a' + 10;
        }
        
        if (digit >= base) {
            break;
        }
        
        result = result * base + digit;
        str++;
        hasDigits = 1;
    }
    
    // Устанавливаем указатель на символ, следующий за числом
    if (endptr != NULL) {
        *endptr = (hasDigits) ? (char*)str : (char*)str - 1;
    }
    
    return result * sign;
}