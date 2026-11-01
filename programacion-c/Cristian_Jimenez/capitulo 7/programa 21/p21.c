#include <stdio.h>
#include <string.h>

void intercambia_filas(char arr[][30], int n);

void main(void)
{
    int i, n;
    char FRA[20][30];
    printf("\nIngrese el número de filas del arreglo: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Ingrese la línea %d de texto: ", i + 1);
        fflush(stdin);
        gets(FRA[i]);
    }
    intercambia_filas(FRA, n);
    printf("\nEl arreglo con las filas intercambiadas es:\n");
    for (i = 0; i < n; i++)
    {
        puts(FRA[i]);
    }
}

void intercambia_filas(char arr[][30], int n)
{
    char temp[30];
    for (int i = 0; i < n / 2; i++)
    {
        strcpy(temp, arr[i]);
        strcpy(arr[i], arr[n - i - 1]);
        strcpy(arr[n - i - 1], temp);
    }
}
