#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

int atoi(const char* str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    // Пропускаем начальные пробелы
    while (str[i] == ' ') {
        i++;
    }

    // Определяем знак числа
    if (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-') {
            sign = -1;
        }
        i++;
    }

    // Преобразуем цифры строки в число
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return sign * result;
}
