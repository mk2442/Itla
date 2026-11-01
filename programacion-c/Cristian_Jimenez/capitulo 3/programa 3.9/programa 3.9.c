#include <stdio.h>

void main(void)
{
    int I = 2, CAM = 1; // Declaración e inicialización de variables: I para el término de la serie, CAM para controlar la variación de I
    long SSE = 0; // Variable para almacenar la suma de la serie

    while (I <= 2500) // Bucle while que se ejecuta mientras el término de la serie sea menor o igual a 2500
    {
        SSE = SSE + I; // Acumula el término actual en la suma de la serie
        printf("\t %d", I); // Imprime el término actual de la serie

        // Condición para determinar la variación de I
        if (CAM)
        {
            I += 5; // Incrementa I en 5 si CAM es verdadero
            CAM--; // Cambia el valor de CAM para alternar la variación
        }
        else
        {
            I += 3; // Incrementa I en 3 si CAM es falso
            CAM++; // Cambia el valor de CAM para alternar la variación
        }
    }

    printf("\nLa suma de la serie es: %ld", SSE); // Imprime la suma de la serie
}
