#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <kernel/tty.h>
#include <ctype.h>

int printf(const char* format, ...) {
    va_list args;
    va_start(args, format);

    size_t count = 0;
    char buffer[32];

    while (*format) {
        if (*format == '%') {
            format++;
            if (*format == '%') {
                terminal_putchar('%');
                count++;
            } else {
                switch (*format) {
                    case 'd': // Вывод целого числа
                    {
                        int value = va_arg(args, int);
                        itoa(value, buffer, 10);
                        size_t len = strlen(buffer);
                        for (size_t i = 0; i < len; i++) {
                            terminal_putchar(buffer[i]);
                            count++;
                        }
                    }
                    break;
                    case 'u': // Вывод беззнакового целого числа
                    {
                        unsigned int value = va_arg(args, unsigned int);
                        utoa(value, buffer, 10);
                        size_t len = strlen(buffer);
                        for (size_t i = 0; i < len; i++) {
                            terminal_putchar(buffer[i]);
                            count++;
                        }
                    }
                    break;
                    case 's': // Вывод строки
                    {
                        char* str = va_arg(args, char*);
                        size_t len = strlen(str);
                        for (size_t i = 0; i < len; i++) {
                            terminal_putchar(str[i]);
                            count++;
                        }
                    }
                    break;
                    case 'c': // Вывод символа
                    {
                        char c = va_arg(args, int);
                        terminal_putchar(c);
                        count++;
                    }
                    break;
                    case 'f': // Вывод числа с плавающей запятой (float)
                    {
                        double fvalue = va_arg(args, double);
                        ftoa(fvalue, buffer, 6);
                        size_t len = strlen(buffer);
                        for (size_t i = 0; i < len; i++) {
                            terminal_putchar(buffer[i]);
                            count++;
                        }
                    }
                    break;
                    case 'l': // Вывод числа с плавающей запятой (double)
                    {
                        format++;
                        if (*format == 'd') { // Вывод целого числа (long int)
                            long int value = va_arg(args, long int);
                            ltoa(value, buffer, 10);
                            size_t len = strlen(buffer);
                            for (size_t i = 0; i < len; i++) {
                                terminal_putchar(buffer[i]);
                                count++;
                            }
                        } else if (*format == 'u') { // Вывод беззнакового целого числа (unsigned long int)
                            unsigned long int value = va_arg(args, unsigned long int);
                            ultoa(value, buffer, 10);
                            size_t len = strlen(buffer);
                            for (size_t i = 0; i < len; i++) {
                                terminal_putchar(buffer[i]);
                                count++;
                            }
                        } else if (*format == 'f') { // Вывод числа с плавающей запятой (float)
                            double fvalue = va_arg(args, double);
                            ftoa(fvalue, buffer, 6);
                            size_t len = strlen(buffer);
                            for (size_t i = 0; i < len; i++) {
                                terminal_putchar(buffer[i]);
                                count++;
                            }
                        } else if (*format == 'l') { // Форматы, начинающиеся с 'll'
                            format++;
                            if (*format == 'd') { // Вывод целого числа (long long)
                                long long int value = va_arg(args, long long int);
                                char buffer[32];
                                lltoa(value, buffer, 10);
                                size_t len = strlen(buffer);
                                for (size_t i = 0; i < len; i++) {
                                    terminal_putchar(buffer[i]);
                                    count++;
                                }
                            } else if (*format == 'u') { // Вывод беззнакового целого числа (long long)
                                unsigned long long int value = va_arg(args, unsigned long long int);
                                char buffer[32];
                                ultoa(value, buffer, 10);
                                size_t len = strlen(buffer);
                                for (size_t i = 0; i < len; i++) {
                                    terminal_putchar(buffer[i]);
                                    count++;
                                }
                            } else {
                                terminal_putchar('%');
                                terminal_putchar('l');
                                terminal_putchar(*format);
                                count += 3;
                            }
                        } else {
                            terminal_putchar('%');
                            terminal_putchar('l');
                            terminal_putchar(*format);
                            count += 3;
                        }
                    }
                    break;
                    case 'h': // Короткий модификатор
                    {
                        format++;
                        if (*format == 'd') { // Вывод целого числа (short int)
                            short int value = va_arg(args, int);
                            itoa(value, buffer, 10);
                            size_t len = strlen(buffer);
                            for (size_t i = 0; i < len; i++) {
                                terminal_putchar(buffer[i]);
                                count++;
                            }
                        } else if (*format == 'u') { // Вывод беззнакового целого числа (unsigned short int)
                            unsigned short int value = va_arg(args, unsigned int);
                            utoa(value, buffer, 10);
                            size_t len = strlen(buffer);
                            for (size_t i = 0; i < len; i++) {
                                terminal_putchar(buffer[i]);
                                count++;
                            }
                        } else {
                            terminal_putchar('%');
                            terminal_putchar('h');
                            terminal_putchar(*format);
                            count += 3;
                        }
                    }
                    break;
                    case 'L': // Вывод числа с плавающей запятой (long double)
                    {
                        format++;
                        if (*format == 'f') { // Вывод числа с плавающей запятой (float)
                            long double fvalue = va_arg(args, long double);
                            ftoa(fvalue, buffer, 6);
                            size_t len = strlen(buffer);
                            for (size_t i = 0; i < len; i++) {
                                terminal_putchar(buffer[i]);
                                count++;
                            }
                        } else {
                            terminal_putchar('%');
                            terminal_putchar('L');
                            terminal_putchar(*format);
                            count += 3;
                        }
                    }
                    break;
                    case '.': // Точность форматирования для чисел с плавающей запятой
                    {
                        format++;
                        if (isdigit(*format)) {
                            int precision = 0;
                            while (isdigit(*format)) {
                                precision = precision * 10 + (*format - '0');
                                format++;
                            }
                            if (*format == 'f') { // Вывод числа с плавающей запятой (float)
                                double fvalue = va_arg(args, double);
                                ftoa(fvalue, buffer, precision);
                                size_t len = strlen(buffer);
                                for (size_t i = 0; i < len; i++) {
                                    terminal_putchar(buffer[i]);
                                    count++;
                                }
                            } else if (*format == 'l' && *(format + 1) == 'f') { // Вывод числа с плавающей запятой (double)
                                format++;
                                double fvalue = va_arg(args, double);
                                ftoa(fvalue, buffer, precision);
                                size_t len = strlen(buffer);
                                for (size_t i = 0; i < len; i++) {
                                    terminal_putchar(buffer[i]);
                                    count++;
                                }
                            } else if (*format == 'L' && *(format + 1) == 'f') { // Вывод числа с плавающей запятой (long double)
                                format++;
                                long double fvalue = va_arg(args, long double);
                                ftoa(fvalue, buffer, precision);
                                size_t len = strlen(buffer);
                                for (size_t i = 0; i < len; i++) {
                                    terminal_putchar(buffer[i]);
                                    count++;
                                }
                            } else {
                                terminal_putchar('%');
                                terminal_putchar('.');
                                while (isdigit(*format))
                                {
                                    terminal_putchar(*format);
                                    format++;
                                    count++;
                                }
                                terminal_putchar(*format);
                                count++;
                            }
                        } else {
                            terminal_putchar('%');
                            terminal_putchar('.');
                            terminal_putchar(*format);
                            count += 3;
                        }
                    }
                    break;
                    default:
                        terminal_putchar('%');
                        terminal_putchar(*format);
                        count += 2;
                        break;
                }
            }
        } else {
            terminal_putchar(*format);
            count++;
        }
        format++;
    }

    va_end(args);
    return count;
}
