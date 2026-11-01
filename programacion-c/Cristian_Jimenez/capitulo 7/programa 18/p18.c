#include <stdio.h>


int palindromo(char *);

int main(void)
{
    char cad[50];
    printf("\nIngrese la cadena de caracteres: ");
    gets(cad);
    if (palindromo(cad))
        printf("\n\nLa cadena es un palíndromo.");
    else
        printf("\n\nLa cadena no es un palíndromo.");
    return 0;
}

int palindromo(char *cadena)
{
    int i = 0, j = strlen(cadena) - 1;
    while (i < j)
    {
        if (cadena[i] != cadena[j])
            return 0;
        i++;
        j--;
    }
    return 1;
}
