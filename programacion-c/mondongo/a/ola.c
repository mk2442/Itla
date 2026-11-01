#include <stdio.h>

int main() {
    char operator;
    double num1, num2;

    printf("Ingrese un operador (+, -, *, /): ");
    scanf("%c", &operator);

    printf("Ingrese dos números: ");
    scanf("%lf %lf", &num1, &num2);

    switch(operator) {
        case '+':
            printf("%.2lf + %.2lf = %.2lf", num1, num2, num1 + num2);
            break;
        case '-':
            printf("%.2lf - %.2lf = %.2lf", num1, num2, num1 - num2);
            break;
        case '*':
            printf("%.2lf * %.2lf = %.2lf", num1, num2, num1 * num2);
            break;
        case '/':
            if(num2 != 0)
                printf("%.2lf / %.2lf = %.2lf", num1, num2, num1 / num2);
            else
                printf("Error! No se puede dividir por cero.");
            break;
        default:
            printf("Error! Operador no válido.");
    }

    return 0;
}
