#include <stdio.h>
#include <string.h>

void main(void) {
    char cad1[50], cad2[50];
    printf("\nIngrese la primera cadena de caracteres: ");
    gets(cad1);
    printf("\nIngrese la segunda cadena de caracteres: ");
    gets(cad2);
    strcat(cad1, cad2);
    printf("\nLa cadena concatenada es: %s", cad1);
}
