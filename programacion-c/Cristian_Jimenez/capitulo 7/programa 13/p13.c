#include <stdio.h>
#include <string.h>
#include <ctype.h>


int cuenta_vocales(char *); 

int main(void)
{
    char fra[50];
    printf("\nIngrese la cadena de caracteres: ");
    gets(fra);
    printf("\n\nEl número de vocales en la cadena es: %d", cuenta_vocales(fra));
    return 0;
}

int cuenta_vocales(char *cadena)
{
    int i = 0, cuenta = 0;
    while (cadena[i] != '\0')
    {
        if (tolower(cadena[i]) == 'a' || tolower(cadena[i]) == 'e' || tolower(cadena[i]) == 'i' ||
            tolower(cadena[i]) == 'o' || tolower(cadena[i]) == 'u')
            cuenta++;
        i++;
    }
    return (cuenta);
}
