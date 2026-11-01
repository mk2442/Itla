#include <stdio.h>

void main(void)
{
char cad[50];
int res;
FILE *ar;
if((ar = fopen("arc.txt", "w")) != NULL)
{
    printf("\nDesea ingresar una cadena de caracteres? Si-1 No-0: ");
    scanf("%d", &res);
    while(res)
    {
        fflush(stdin);
        printf("Ingrese la cadena: ");
        gets(cad);
        fputs(cad, ar);
        printf("\nDesea ingresar otra cadena de caracteres? Si-1 No-0:");
        scanf("%d", &res);
        if(res)
            fputs("\n", ar);
    }
    fclose(ar);
}
else
    printf("No se puede abrir el archivo");
}
