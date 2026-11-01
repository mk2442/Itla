#include <stdio.h>


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
        puts(FRA[i]);
}
