#include <stdio.h>
#include <string.h>
#include <ctype.h>


void invierte(char *); 

int main(void)
{
    char fra[50];
    printf("\nIngrese la cadena de caracteres: ");
    gets(fra);
    invierte(fra);
    printf("\n\nCadena invertida: %s", fra);
    return 0;
}

void invierte(char *cadena)
{
    int i = 0, j = strlen(cadena) - 1;
    char temp;
    while (i < j)
    {
        temp = cadena[i];
        cadena[i] = cadena[j];
        cadena[j] = temp;
        i++;
        j--;
    }
}
