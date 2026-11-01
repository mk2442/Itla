#include <stdio.h>

void main(void) {
    char cad1[50], cad2[50];
    printf("\nIngrese la cadena de caracteres: ");
    gets(cad1);
    strcpy(cad2, cad1);
    printf("\nLa cadena copiada es: %s", cad2);
}
