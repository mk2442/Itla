#include <stdio.h>


void main(void) {
    char cad[50];
    printf("\nIngrese la cadena de caracteres: ");
    gets(cad);
    printf("\nLa cadena en minúsculas es: %s", strlwr(cad));
    printf("\nLa cadena en mayúsculas es: %s", strupr(cad));
}
