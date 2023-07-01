#include <string.h>
#include <float.h>

int isinf(double value) {
    // Проверяем, является ли значение бесконечностью (Inf или -Inf)
    // Проверяем два условия: значение больше максимального числа типа double или меньше минимального отрицательного числа типа double
    return (value > DBL_MAX || value < -DBL_MAX);
}
