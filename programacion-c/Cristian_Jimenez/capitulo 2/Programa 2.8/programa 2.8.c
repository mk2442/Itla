#include <stdio.h>  // Incluye la librería estándar de entrada y salida
#include <math.h>   // Incluye la librería para funciones matemáticas

void main(void)  // Define la función principal del programa
{
    float RES;    // Declara una variable flotante para el resultado
    int R, T, Q;  // Declara variables enteras para R, T y Q

    printf("Ingrese los valores de R, T y Q: ");  // Pide al usuario que ingrese los valores de R, T y Q
    scanf("%d %d %d", &R, &T, &Q);  // Lee los valores ingresados por el usuario y los almacena en las variables R, T y Q

    // Calcula el resultado según la fórmula dada
    RES = pow(R, 4) - pow(T, 3) + 4 * pow(Q, 2);

    // Verifica si el resultado es menor que 820
    if (RES < 820)
    {
        printf("\nR = %d\tT = %d\tQ = %d", R, T, Q);  // Imprime los valores de R, T y Q si el resultado es menor que 820
    }
}
