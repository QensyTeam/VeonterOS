#include <stdlib.h>
#include <string.h>

char* lltoa(long long int value, char* str, int base) {
    if (value < 0) {
        *str++ = '-';
        return ultoa((unsigned long long int)(-value), str, base);
    }

    return ultoa((unsigned long long int)value, str, base);
}