#include <math.h>

double floor(double x) {
    double integerPart;
    if (x >= 0.0) {
        integerPart = (double)((int)x);
    } else {
        integerPart = (double)((int)(x - 1.0));
    }
    return integerPart;
}
