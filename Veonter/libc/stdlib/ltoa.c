#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* ltoa(long value, char* str, int base) {
    // Массив символов для представления числа в разрядной записи
    char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    
    // Проверка на ноль и отрицательность значения
    int negative = 0;
    if (value < 0) {
        negative = 1;
        value = -value;
    }
    
    // Количество разрядов числа
    int digits_count = 0;
    long temp = value;
    do {
        digits_count++;
        temp /= base;
    } while (temp > 0);
    
    // Выделение памяти для строки
    int str_size = digits_count + negative + 1;
    if (str == NULL) {
        str = (char*)malloc(str_size * sizeof(char));
    }
    
    // Заполнение строки разрядами числа
    str[str_size - 1] = '\0';
    for (int i = str_size - 2; i >= negative; i--) {
        str[i] = digits[value % base];
        value /= base;
    }
    
    // Добавление знака минуса при необходимости
    if (negative) {
        str[0] = '-';
    }
    
    return str;
}
