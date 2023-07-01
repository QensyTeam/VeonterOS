#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <kernel/tty.h>

long atol(const char* str) {
    long result = 0;
    int sign = 1;

    // Skip leading whitespace
    while (*str == ' ')
        str++;

    // Check for sign
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // Process digits
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }

    // Apply the sign
    result *= sign;

    return result;
}
