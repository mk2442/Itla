#include <stdio.h>

int main() {
    char letra1, letra2;

    printf("Ingrese una letra: ");
    scanf("%c", &letra1);

    if (letra1 >= 'A' && letra1 <= 'Z') {
        letra2 = letra1 + 32;  
        printf("\nLa letra %c en minúscula es: %c\n", letra1, letra2);
    } else if (letra1 >= 'a' && letra1 <= 'z') {
        letra2 = letra1 - 32;  
        printf("\nLa letra %c en mayúscula es: %c\n", letra1, letra2);
    } else {
        printf("\nEl caracter ingresado no es una letra válida.\n");
    }

    return 0;
}
