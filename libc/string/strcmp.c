#include <string.h>

int strcmp (const char* s1, const char* s2)
{
    // Пока символы в обеих строках одинаковые и не равны нулю
    while (*s1 && (*s1 == *s2))
    {
        // Переходим к следующей паре символов
        s1++;
        s2++;
    }
    // Возвращаем разницу между символами, приведенными к типу unsigned char
    return * (const unsigned char*)s1 - * (const unsigned char*)s2;
}