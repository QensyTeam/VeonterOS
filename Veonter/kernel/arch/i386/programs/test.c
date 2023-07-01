#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void test_isalpha(char c) {
    if (isalpha(c)) {
        printf("%c is an alphabet character.\n", c);
    } else {
        printf("%c is not an alphabet character.\n", c);
    }
}

void test_isupper(char c) {
    if (isupper(c)) {
        printf("%c is an uppercase character.\n", c);
    } else {
        printf("%c is not an uppercase character.\n", c);
    }
}

void test_isdigit(char c) {
    if (isdigit(c)) {
        printf("%c is a digit.\n", c);
    } else {
        printf("%c is not a digit.\n", c);
    }
}

void test_tolower(char c) {
    printf("Lowercase of %c is %c.\n", c, tolower(c));
}

void test_strtod(const char* str) {
    char* endptr;
    double value = strtod(str, &endptr);
    if (endptr == str) {
        printf("Invalid input: %s\n", str);
    } else {
        printf("Double value: %f\n", value);
    }
}

void test_strtol(const char* str) {
    char* endptr;
    long value = strtol(str, &endptr, 10);
    if (endptr == str) {
        printf("Invalid input: %s\n", str);
    } else {
        printf("Long value: %ld\n", value);
    }
}

void test_strtof(const char* str) {
    char* endptr;
    float value = strtof(str, &endptr);
    if (endptr == str) {
        printf("Invalid input: %s\n", str);
    } else {
        printf("Float value: %f\n", value);
    }
}

void test() {
    // Test isalpha
    test_isalpha('A');  // Should print: A is an alphabet character.
    test_isalpha('7');  // Should print: 7 is not an alphabet character.

    // Test isupper
    test_isupper('A');  // Should print: A is an uppercase character.
    test_isupper('a');  // Should print: a is not an uppercase character.

    // Test isdigit
    test_isdigit('5');  // Should print: 5 is a digit.
    test_isdigit('x');  // Should print: x is not a digit.

    // Test tolower
    test_tolower('A');  // Should print: Lowercase of A is a.

    // Test strtod
    test_strtod("3.14");  // Should print: Double value: 3.140000

    // Test strtol
    test_strtol("12345");  // Should print: Long value: 12345

    // Test strtof
    test_strtof("2.718");  // Should print: Float value: 2.718000

    int num;
    char str[20];

    // Считываем целое число и строку из входной строки
    scanf("%d %s", &num, str);

    // Выводим результаты
    printf("num: %d\n", num);
    printf("str: %s\n", str);
}
