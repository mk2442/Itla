#include <stdio.h>


void main(void)
{
    int I, PRI = 0, SEG = 1, SIG; // Declaración e inicialización de variables: I para el contador, PRI y SEG para los primeros dos números de Fibonacci, SIG para el siguiente número de Fibonacci

    printf("\t %d \t %d", PRI, SEG); // Imprime los dos primeros números de Fibonacci

    // Bucle for para calcular e imprimir los siguientes números de Fibonacci
    for (I = 3; I <= 50; I++)
    {
        SIG = PRI + SEG; // Calcula el siguiente número de Fibonacci sumando los dos anteriores
        PRI = SEG; // Actualiza PRI con el valor de SEG
        SEG = SIG; // Actualiza SEG con el valor de SIG
        printf("\t %d", SIG); // Imprime el siguiente número de Fibonacci
    }
}
