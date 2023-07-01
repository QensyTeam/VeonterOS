#include <stddef.h>

char* strcat(char* dest, const char* src) {
    // Найти конец строки dest
    size_t dest_length = 0;
    while (dest[dest_length] != '\0') {
        dest_length++;
    }

    // Копировать символы из src в конец dest
    size_t i = 0;
    while (src[i] != '\0') {
        dest[dest_length + i] = src[i];
        i++;
    }

    // Добавить завершающий нулевой символ
    dest[dest_length + i] = '\0';

    return dest;
}
