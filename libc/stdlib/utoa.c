#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

void utoa(unsigned int num, char *str, int base) {
    int i = 0;
    do {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num /= base;
    } while (num != 0);
    str[i] = '\0';
    reverse(str, i);
}