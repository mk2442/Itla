#include <stdio.h>
#include <stdlib.h>

void main(void) {
    char cad[10];
    int i = 0;
    float sum = 0.0;
    printf("\nDesea ingresar una cadena de caracteres (S/N): ");
    while (getchar() == 'S') {
        printf("\nIngrese la cadena de caracteres: ");
        fflush(stdin);
        gets(cad);
        sum += atof(cad);
        i++;
        printf("\nDesea ingresar otra cadena de caracteres (S/N): ");
    }
    if (i != 0)
        printf("\n\nEl promedio es: %.2f", sum / i);
}
