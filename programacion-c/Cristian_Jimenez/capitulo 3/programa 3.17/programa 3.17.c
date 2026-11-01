#include <stdio.h>

void main(void)
{
    int I, J, NUM, SUM, C = 0;

    printf("\nIngrese el número límite: ");
    scanf("%d", &NUM);

    // Bucle externo para iterar a través de los números desde 1 hasta NUM
    for (I = 1; I <= NUM; I++)
    {
        SUM = 0;

        // Bucle interno para encontrar los divisores de I y sumarlos
        for (J = 1; J <= (I / 2); J++)
        {
            if ((I % J) == 0)
            {
                SUM += J;
            }
        }

        // Comprueba si la suma de los divisores es igual al número mismo (es decir, si es un número perfecto)
        if (SUM == I)
        {
            printf("\n%d es un número perfecto", I);
            C++; // Incrementa el contador de números perfectos
        }
    }

    // Imprime la cantidad de números perfectos encontrados en el rango
    printf("\nEntre 1 y %d hay %d números perfectos", NUM, C);
}
