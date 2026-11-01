#include <stdio.h>
#include <string.h>

void main(void) {
    char cad[50];
    printf("\nIngrese la cadena de caracteres: ");
    gets(cad);
    printf("\nLa longitud de la cadena es: %d", strlen(cad));
}
