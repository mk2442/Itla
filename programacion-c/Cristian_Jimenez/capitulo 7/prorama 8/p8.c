#include <stdio.h>
#include <string.h>


void main(void) {
    char cad[50], *token;
    int cont = 0;
    printf("\nIngrese la cadena de caracteres: ");
    gets(cad);
    token = strtok(cad, " ");
    while (token != NULL) {
        cont++;
        token = strtok(NULL, " ");
    }
    printf("\nEl número de palabras es: %d", cont);
}
