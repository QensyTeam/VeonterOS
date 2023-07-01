#include <stdlib.h>
#include <string.h>

char* ultoa(unsigned long long int value, char* str, int base) {
    char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* p = str;
    char* p1, * p2;

    // Определение направления
    if (base < 2 || base > 36) {
        *p = '\0';
        return str;
    }

    // Сохранение знака и создание обратной строки
    do {
        *p++ = digits[value % base];
        value /= base;
    } while (value);

    // Обратное направление строки
    p1 = str;
    p2 = p - 1;
    while (p1 < p2) {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }

    *p = '\0';

    return str;
}
