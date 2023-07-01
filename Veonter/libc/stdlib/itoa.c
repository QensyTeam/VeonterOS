#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <kernel/tty.h>

void itoa(int32_t value, char* buffer, int base) {
    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    int32_t i = value;
    int32_t j = 0;
    char temp;
    int32_t is_negative = 0;

    if (value < 0 && base == 10) {
        is_negative = 1;
        i = -i;
    }

    while (i != 0) {
        int32_t remainder = i % base;
        buffer[j++] = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
        i /= base;
    }

    if (is_negative)
        buffer[j++] = '-';

    buffer[j] = '\0';

    // Reverse the string
    int32_t length = j;
    for (int32_t k = 0; k < length / 2; k++) {
        temp = buffer[k];
        buffer[k] = buffer[length - k - 1];
        buffer[length - k - 1] = temp;
    }
}