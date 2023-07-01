#include <math.h>

float floorf(float x) {
    float integerPart;
    if (x >= 0.0f) {
        integerPart = (float)((int)x);
    } else {
        integerPart = (float)((int)(x - 1.0f));
    }
    return integerPart;
}
