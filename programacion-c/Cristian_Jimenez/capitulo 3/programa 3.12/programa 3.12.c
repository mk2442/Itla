#include <stdio.h>
#include <math.h>

void main(void)
{
    int NUM; // Variable para almacenar el número ingresado por el usuario

    printf("Ingresa el número para calcular la serie: "); // Solicita al usuario que ingrese el número
    scanf("%d", &NUM); // Lee el número ingresado por el usuario y lo almacena en NUM

    if (NUM > 0) // Verifica si el número ingresado es positivo
    {
        printf("\nSerie de ULAM\n"); // Imprime el encabezado de la serie

        printf("%d \t", NUM); // Imprime el primer término de la serie

        // Bucle while para generar la serie de ULAM
        while (NUM != 1)
        {
            // Determina el siguiente término de la serie según la regla de ULAM
            if (pow(-1, NUM) > 0)
                NUM = NUM / 2;
            else
                NUM = NUM * 3 + 1;

            printf("%d \t", NUM); // Imprime el siguiente término de la serie
        }
    }
    else
    {
        printf("\n NUM debe ser un entero positivo"); // Si el número ingresado es negativo o cero, imprime un mensaje de error
    }
}
