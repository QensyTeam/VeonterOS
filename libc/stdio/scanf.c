#include <stdbool.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <kernel/shell.h>
#include <kernel/tty.h>
void scanf_int(int* value);
void scanf_string(char* str);
void scanf_float(float* fvalue);
void scanf_double(double* dvalue);

int scanf(const char* format, ...) {
    va_list args;
    va_start(args, format);

    int i = 0;
    while (format[i] != '\0') {
        if (format[i] == '%') {
            i++;
            switch (format[i]) {
                case 'd': {
                    int* value = va_arg(args, int*);
                    scanf_int(value);
                    break;
                }
                case 's': {
                    char* str = va_arg(args, char*);
                    scanf_string(str);
                    break;
                }
                case 'c': {
                    char* value = va_arg(args, char*);
                    *value = shell_getchar();
                    break;
                }
                case 'f': {
                    float* fvalue = va_arg(args, float*);
                    scanf_float(fvalue);
                    break;
                }
                case 'l': {
                    i++;
                    if (format[i] == 'f') {
                        double* dvalue = va_arg(args, double*);
                        scanf_double(dvalue);
                    }
                    else if (format[i] == 'd') {
                        long* lvalue = va_arg(args, long*);
                        scanf_int((int*)lvalue);
                    }
                    break;
                }
            }
        }
        i++;
    }

    va_end(args);
    return 0;
}

void scanf_int(int* value) {
    char buffer[32];
    int i = 0;
    *value = 0;
    char c = shell_getchar();
    while (c >= '0' && c <= '9') {
        buffer[i++] = c;
        c = shell_getchar();
    }
    buffer[i] = '\0';
    *value = atoi(buffer);
}

void scanf_string(char* str) {
    char c = shell_getchar();
    while (c != '\n' && c != '\0') {
        if (c == '\b') { // если нажата кнопка \b
            terminal_backspace(); // удалить символ с экрана
            str--; // уменьшить указатель на строку
            *str = '\0'; //от Арена
        }
        else {
            *str = c;
            str++;
        }
        c = shell_getchar();
    }
    *str = '\0';
}

void scanf_float(float* fvalue) {
    char buffer[32];
    int i = 0;
    *fvalue = 0.0;
    char c = shell_getchar();
    while (c >= '0' && c <= '9') {
        buffer[i++] = c;
        c = shell_getchar();
    }
    if (c == '.') {
        buffer[i++] = c;
        c = shell_getchar();
        while (c >= '0' && c <= '9') {
            buffer[i++] = c;
            c = shell_getchar();
        }
    }
    buffer[i] = '\0';
    char* fresult = ftoa(strtof(buffer, NULL), buffer, 6);
    *fvalue = strtof(fresult, NULL);
}


void scanf_double(double* dvalue) {
    char buffer[32];
    int i = 0;
    *dvalue = 0.0;
    char c = shell_getchar();
    while (c >= '0' && c <= '9') {
        buffer[i++] = c;
        c = shell_getchar();
    }
    if (c == '.') {
        buffer[i++] = c;
        c = shell_getchar();
        while (c >= '0' && c <= '9') {
            buffer[i++] = c;
            c = shell_getchar();
        }
    }
    buffer[i] = '\0';
    *dvalue = strtof(buffer, NULL);
}