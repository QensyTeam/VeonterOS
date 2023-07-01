#include <stddef.h>

size_t strcspn(const char *str, const char *reject) 
{
    const char *s1 = str;
    size_t count = 0;
    while (*s1) 
    {
        const char *s2 = reject;
        while (*s2) 
        {
            if (*s1 == *s2) 
            {
                return count;
            }
            s2++;
        }
        s1++;
        count++;
    }
    return count;
}
