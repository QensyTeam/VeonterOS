#include <stdio.h>
#include <string.h>
#include <kernel/shell.h>
#include <kernel/drv/tty.h>
/*
int main() {
    printf("Welcome! This is a simple calculator.\n");
    printf("To exit, type 'quit'.\n");
    printf("For help, type 'help'.\n");


    while (1) {
        char operator;
        double operand1, operand2, result;

        printf("Enter an operation: ");
        scanf(" %c", &operator);

        if (operator == 'q' || operator == 'Q') {
            printf("\nGoodbye!\n");
            break;
        }

        if (operator == 'h' || operator == 'H') {
            printf("\nAvailable operations: +, -, *, /\n");
            continue;
        }

        printf("\nEnter the first operand: ");
        scanf("%lf", &operand1);

        printf("\nEnter the second operand: ");
        scanf("%lf", &operand2);

        switch (operator) {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                if (operand2 == 0) {
                    printf("\nError: Division by zero is not allowed!\n");
                    continue;
                }
                result = operand1 / operand2;
                break;
            default:
                printf("\nInvalid operation!\n");
                continue;
        }

        printf("\nResult: %.8lf\n\n", result);
    }

    return 0;
}




void calculator() {
    terminal_clearscreen();
    printf("================================== CALCULATOR ==================================\n");
    main();
}
*/