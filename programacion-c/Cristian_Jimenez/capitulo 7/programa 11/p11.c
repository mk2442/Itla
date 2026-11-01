#include <stdio.h>
#include <stdlib.h>

/* Suma y promedio.
El programa, al recibir como datos varias cadenas de caracteres que
➥contienen reales, los suma y obtiene el promedio de los mismos. */

int main(void)
{
    char cad[10];
    int i = 0;
    float suma = 0.0;
    printf("\nDesea ingresar una cadena de caracteres que contiene un número real (S/N): ");
    while (toupper(getchar()) == 'S')
    {
        printf("\nIngrese la cadena de caracteres: ");
        fflush(stdin);
        gets(cad);
        suma += atof(cad);
        i++;
        printf("\nDesea ingresar otra cadena de caracteres (S/N): ");
    }
    if (i)
        printf("\n\nLa suma es: %.2f", suma);
    else
        printf("\n\nNo se ingresaron cadenas.");
    return 0;
}
