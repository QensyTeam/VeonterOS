#include <string.h>

int isnan(double value) {
    // Проверяем, является ли значение не числом (NaN)
    // В стандартном математическом определении NaN != NaN
    return (value != value);
}

