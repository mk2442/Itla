#include <stdio.h>
#include <math.h>

void main(void)
{
    int I, N, NUM, SPA = 0, SIM = 0, CIM = 0; // Declaración de variables: I para el contador, N para el número de datos, NUM para el número ingresado, SPA para la suma de números pares, SIM para la suma de números impares, CIM para contar números impares

    printf("Ingrese el número de datos que se van a procesar:\t"); // Solicita al usuario que ingrese el número de datos
    scanf("%d", &N); // Lee el número de datos ingresado por el usuario y lo almacena en N

    if (N > 0) // Verifica si el número de datos es positivo
    {
        // Bucle for para procesar los datos ingresados
        for (I = 1; I <= N; I++)
        {
            printf("\nIngrese el número %d: ", I); // Solicita al usuario que ingrese el número actual
            scanf("%d", &NUM); // Lee el número ingresado por el usuario y lo almacena en NUM

            if (NUM) // Verifica si el número ingresado es diferente de cero
            {
                if (pow(-1, NUM) > 0) // Verifica si el número es par
                {
                    SPA = SPA + NUM; // Acumula el número en la suma de números pares
                }
                else // Si el número es impar
                {
                    SIM = SIM + NUM; // Acumula el número en la suma de números impares
                    CIM++; // Incrementa el contador de números impares
                }
            }
        }

        printf("\n La suma de los números pares es: %d", SPA); // Imprime la suma de los números pares
        printf("\n El promedio de números impares es: %5.2f", (float)(SIM / CIM)); // Imprime el promedio de los números impares
    }
    else
    {
        printf("\n El valor de N es incorrecto"); // Si el número de datos es negativo o cero, imprime un mensaje de error
    }
}
