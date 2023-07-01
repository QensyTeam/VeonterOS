#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <kernel/tty.h>

double pow(double base, double exponent) {
    if (exponent == 0.0) {
        return 1.0;
    }

    double result = 1.0;
    int negativeExponent = 0;

    // Check if the exponent is negative
    if (exponent < 0) {
        exponent = -exponent;
        negativeExponent = 1;
    }

    // Calculate the power using the binary exponentiation algorithm
    while (exponent > 0) {
        if ((int)exponent & 1) {
            result *= base;
        }
        base *= base;
        exponent /= 2;
    }

    // Handle negative exponents
    if (negativeExponent) {
        result = 1.0 / result;
    }

    return result;
}