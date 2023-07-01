#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <kernel/tty.h>
#include <ctype.h>
#include <string.h>

char* ftoa(float value, char* buffer, int precision) {
    int int_part = (int)value;                     // Целая часть числа
    float fraction_part = value - (float)int_part;  // Дробная часть числа

    // Преобразование целой части в строку
    itoa(int_part, buffer, 10);

    // Добавление точки в конец строки
    strcat(buffer, ".");

    // Преобразование дробной части в строку
    char fraction_buffer[16];
    int i = 0;
    while (i < precision) {
        fraction_part *= 10;
        int digit = (int)fraction_part;
        fraction_buffer[i++] = '0' + digit;
        fraction_part -= digit;
    }
    fraction_buffer[i] = '\0';
    strcat(buffer, fraction_buffer);

    return buffer;
}
