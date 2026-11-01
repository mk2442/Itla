#include <stdio.h>
#include <ctype.h>


void minymay(char *);

void main(void)
{
    char FRA[10][20];
    int i, n;
    printf("\nIngrese el número de filas del arreglo: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Ingrese la línea %d de texto: ", i + 1);
        fflush(stdin);
        gets(FRA[i]);
    }
    printf("\n\n");
    for (i = 0; i < n; i++)
        minymay(FRA[i]);
}

void minymay(char *cadena)
{
    int i = 0;
    while (cadena[i] != '\0')
    {
        cadena[i] = toupper(cadena[i]);
        i++;
    }
    printf("\n\n%s", cadena);
}
